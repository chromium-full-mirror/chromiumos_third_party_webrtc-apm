/* Copyright (c) 2018 The Chromium Authors. All rights reserved.
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

#include <metrics/metrics_library.h>

#include "api/audio/echo_canceller3_factory.h"
#include "api/task_queue/default_task_queue_factory.h"
#include "cras-config/aec_config.h"
#include "cras-config/apm_config.h"
#include "modules/audio_processing/aec_dump/aec_dump_factory.h"
#include "modules/audio_processing/include/aec_dump.h"
#include "modules/audio_processing/include/audio_processing.h"
#include "rtc_base/task_queue.h"
#include "system_wrappers/include/metrics.h"

extern "C" {
#include <errno.h>

#include "webrtc_apm.h"

using webrtc::metrics::SampleInfo;

static std::string hist_name_prefix_;
static std::unique_ptr<MetricsLibraryInterface> metrics_lib_;

void webrtc_apm_init_metrics(const char *prefix)
{
	if (prefix == NULL)
		return;

	webrtc::metrics::Enable();
	hist_name_prefix_ = prefix;
	metrics_lib_ = std::make_unique<MetricsLibrary>();
}

webrtc_apm webrtc_apm_create(
		unsigned int num_channels,
		unsigned int frame_rate,
		dictionary *aec_ini,
		dictionary *apm_ini) {

  return webrtc_apm_create_with_enforced_effects(num_channels, frame_rate,
		aec_ini,apm_ini,0,0,0);
}

webrtc_apm webrtc_apm_create_with_enforced_effects(
		unsigned int num_channels,
		unsigned int frame_rate,
		dictionary *aec_ini,
		dictionary *apm_ini,
		unsigned int enforce_aec_on,
		unsigned int enforce_ns_on,
		unsigned int enforce_agc_on)
{
	int err;
	webrtc::AudioProcessing *apm;
	webrtc::AudioProcessing::ChannelLayout channel_layout;
	webrtc::AudioProcessingBuilder apm_builder;
	webrtc::EchoCanceller3Config aec3_config;
	std::unique_ptr<webrtc::EchoControlFactory> ec3_factory;

	switch (num_channels) {
		case 1:
			channel_layout = webrtc::AudioProcessing::kMono;
			break;
		case 2:
			channel_layout = webrtc::AudioProcessing::kStereo;
			break;
		default:
			return NULL;
	}

	/* Set the AEC-tunings. */
	if (aec_ini) {
		aec_config_get(aec_ini, &aec3_config);
		ec3_factory.reset(
			new webrtc::EchoCanceller3Factory(aec3_config));
	} else {
		ec3_factory.reset(new webrtc::EchoCanceller3Factory());
	}

	apm_builder.SetEchoControlFactory(std::move(ec3_factory));
	apm = apm_builder.Create();

	/* Set the rest of the all settings/tunings. */
	webrtc::AudioProcessing::Config config = apm->GetConfig();
	bool config_changed = false;
	if (aec_ini || enforce_aec_on == 1) {
		config.echo_canceller.enabled = true;
		/* Activate playout stereo processing by default. This can be
		 * turned off in |apm_ini|.
		 */
		if (enforce_aec_on) {
			config.pipeline.multi_channel_render = true;
		}
		config_changed = true;
	}

	if (apm_ini) {
		apm_config_set(apm_ini, &config);
		config_changed = true;
	}

	if (enforce_ns_on == 1) {
		config.noise_suppression.enabled = true;
		config_changed = true;
	}

	if (enforce_agc_on == 1) {
		config.gain_controller1.enabled = true;
		config.gain_controller1.mode =
			webrtc::AudioProcessing::Config::GainController1::Mode::kAdaptiveAnalog;
		config.capture_level_adjustment.enabled = true;
		config.capture_level_adjustment.analog_mic_gain_emulation.enabled = true;
		config_changed = true;
	}

	if (config_changed) {
		apm->ApplyConfig(config);
	}

	err = apm->Initialize(frame_rate, frame_rate, frame_rate,
			      channel_layout, webrtc::AudioProcessing::kMono,
			      channel_layout);
	if (err) {
		delete apm;
		return NULL;
	}

	return reinterpret_cast<webrtc_apm>(apm);
}

WEBRTC_APM_API void webrtc_apm_enable_effects(
		webrtc_apm ptr,
		bool enable_aec,
		bool enable_ns,
		bool enable_agc)
{
	webrtc::AudioProcessing *apm =
		reinterpret_cast<webrtc::AudioProcessing*>(ptr);
	webrtc::AudioProcessing::Config config = apm->GetConfig();
	bool config_changed = false;

	config_changed = config.echo_canceller.enabled != enable_aec;
	config.echo_canceller.enabled = enable_aec;

	config_changed = config_changed ||
			config.noise_suppression.enabled != enable_ns;
	config.noise_suppression.enabled = enable_ns;

	config_changed = config_changed ||
			config.gain_controller1.enabled != enable_agc;
	config.gain_controller1.enabled = enable_agc;

	if (config_changed) {
		apm->ApplyConfig(config);
	}
}

void webrtc_apm_dump_configs(dictionary *apm_ini,
			     dictionary *aec_ini)
{
	if (apm_ini)
		apm_config_dump(apm_ini);
	if (aec_ini)
		aec_config_dump(aec_ini);
}

int webrtc_apm_process_reverse_stream_f(
		webrtc_apm ptr,
		int num_channels, int rate,
		float *const *data)
{
	webrtc::AudioProcessing *apm;
	webrtc::StreamConfig config =
		webrtc::StreamConfig(rate, num_channels);

	apm = reinterpret_cast<webrtc::AudioProcessing *>(ptr);

	return apm->ProcessReverseStream(data, config, config, data);
}

int webrtc_apm_process_stream_f(webrtc_apm ptr,
				int num_channels,
				int rate,
				float *const *data)
{
	webrtc::AudioProcessing *apm;

	webrtc::StreamConfig iconfig =
		webrtc::StreamConfig(rate, num_channels);
	webrtc::StreamConfig oconfig =
		webrtc::StreamConfig(rate, 1);
	apm = reinterpret_cast<webrtc::AudioProcessing *>(ptr);
	return apm->ProcessStream(data, iconfig, oconfig, data);
}

void webrtc_apm_destroy(webrtc_apm ptr)
{
	webrtc::AudioProcessing *apm;
	apm = reinterpret_cast<webrtc::AudioProcessing *>(ptr);
	delete apm;

	std::map<std::string, std::unique_ptr<SampleInfo>> hist;

	if (!metrics_lib_)
		return;

	webrtc::metrics::GetAndReset(&hist);

	for (auto it = hist.begin(); it != hist.end(); it++) {
		SampleInfo *info = it->second.get();
		std::string name = info->name;
		name.insert(0, hist_name_prefix_);
		/* info->samples stores <value, # of events> */
		for (auto sample = info->samples.begin();
		     sample != info->samples.end(); sample++) {
			for (int i = 0; i < sample->second; i++)
				metrics_lib_->SendToUMA(name, sample->first,
							info->min, info->max,
							info->bucket_count);
		}
	}
}

int webrtc_apm_set_stream_delay(webrtc_apm ptr, int delay_ms)
{
	webrtc::AudioProcessing *apm;

	apm = reinterpret_cast<webrtc::AudioProcessing *>(ptr);
	return apm->set_stream_delay_ms(delay_ms);
}

int webrtc_apm_aec_dump(webrtc_apm ptr, void** wq_ptr, int start, FILE *handle)
{
	webrtc::AudioProcessing *apm;
	rtc::TaskQueue *work_queue;

	apm = reinterpret_cast<webrtc::AudioProcessing *>(ptr);

	if (start) {
		work_queue = new rtc::TaskQueue(webrtc::CreateDefaultTaskQueueFactory()->CreateTaskQueue("aecdump-worker-queue",
						rtc::TaskQueue::Priority::LOW));
		auto aec_dump = webrtc::AecDumpFactory::Create(handle, -1, work_queue);
		if (!aec_dump)
			return -ENOMEM;
		apm->AttachAecDump(std::move(aec_dump));
		*wq_ptr = reinterpret_cast<void *>(work_queue);
	} else {
		apm->DetachAecDump();
		work_queue = reinterpret_cast<rtc::TaskQueue *>(*wq_ptr);
		if (work_queue) {
			delete work_queue;
			work_queue = NULL;
		}
	}
	return 0;
}

} // extern "C"

/* Copyright 2018 The Chromium OS Authors. All rights reserved.
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

#ifndef APM_CONFIG_H_
#define APM_CONFIG_H_

#include <iniparser.h>

#include "modules/audio_processing/include/audio_processing.h"

/* Keys for AudioProcessing::Pipeline */
#define PIPELINE_MAXIMUM_INTERNAL_PROCESSING_RATE "apm:pipeline_maximum_internal_processing_rate"
#define PIPELINE_MAXIMUM_INTERNAL_PROCESSING_RATE_VALUE 48000
#define PIPELINE_MULTI_CHANNEL_RENDER "apm:pipeline_multi_channel_render"
#define PIPELINE_MULTI_CHANNEL_RENDER_VALUE 0
#define PIPELINE_MULTI_CHANNEL_CAPTURE "apm:pipeline_multi_channel_capture"
#define PIPELINE_MULTI_CHANNEL_CAPTURE_VALUE 0

/* Keys for AudioProcessing::PreAmplifier */
#define APM_PRE_AMPLIFIER_ENABLED "apm:pre_amplifier_enabled"
#define APM_PRE_AMPLIFIER_ENABLED_VALUE 0
#define APM_PRE_AMPLIFIER_FIXED_GAIN_FACTOR "apm:pre_amplifier_fixed_gain_factor"
#define APM_PRE_AMPLIFIER_FIXED_GAIN_FACTOR_VALUE 1.f

/* Keys for AudioProcessing::CaptureLevelAdjustment */
#define CAPTURE_LEVEL_ADJUSTMENT_ENABLED "apm:capture_level_adjustment_enabled"
#define CAPTURE_LEVEL_ADJUSTMENT_ENABLED_VALUE 0
#define CAPTURE_LEVEL_ADJUSTMENT_PRE_GAIN_FACTOR "apm:capture_level_adjustment_pre_gain_factor"
#define CAPTURE_LEVEL_ADJUSTMENT_PRE_GAIN_FACTOR_VALUE 1.f
#define CAPTURE_LEVEL_ADJUSTMENT_POST_GAIN_FACTOR "apm:capture_level_adjustment_post_gain_factor"
#define CAPTURE_LEVEL_ADJUSTMENT_POST_GAIN_FACTOR_VALUE 1.f

/* Keys for AudioProcessing::CaptureLevelAdjustment::AnalogMicGainEmulation */
#define CAPTURE_LEVEL_ADJUSTMENT_ANALOG_MIC_GAIN_EMULATION_ENABLED "apm:capture_level_adjustment_analog_mic_gain_emulation_enabled"
#define CAPTURE_LEVEL_ADJUSTMENT_ANALOG_MIC_GAIN_EMULATION_ENABLED_VALUE 0
#define CAPTURE_LEVEL_ADJUSTMENT_ANALOG_MIC_GAIN_EMULATION_INITIAL_LEVEL "apm:capture_level_adjustment_analog_mic_gain_emulation_initial_level"
#define CAPTURE_LEVEL_ADJUSTMENT_ANALOG_MIC_GAIN_EMULATION_INITIAL_LEVEL_VALUE 255

/* Keys for AudioProcessing::HighPassFilter */
#define APM_HIGH_PASS_FILTER_ENABLED "apm:high_pass_filter_enabled"
#define APM_HIGH_PASS_FILTER_ENABLED_VALUE 0
#define APM_HIGH_PASS_FILTER_APPLY_IN_FULL_BAND "apm:high_pass_filter_apply_in_full_band"
#define APM_HIGH_PASS_FILTER_APPLY_IN_FULL_BAND_VALUE 1

/* Keys for AudioProcessing::EchoCanceller */
#define APM_ECHO_CANCELLER_ENABLED "apm:echo_canceller_enabled"
#define APM_ECHO_CANCELLER_ENABLED_VALUE 0
#define APM_ECHO_CANCELLER_MOBILE_MODE "apm:echo_canceller_mobile_mode"
#define APM_ECHO_CANCELLER_MOBILE_MODE_VALUE 0
#define APM_ECHO_CANCELLER_EXPORT_LINEAR_AEC_OUTPUT \
	"apm:echo_canceller_export_linear_aec_output"
#define APM_ECHO_CANCELLER_EXPORT_LINEAR_AEC_OUTPUT_VALUE 0
#define APM_ECHO_CANCELLER_ENFORCE_HIGH_PASS_FILTERING \
	"apm:echo_canceller_enforce_high_pass_filtering"
#define APM_ECHO_CANCELLER_ENFORCE_HIGH_PASS_FILTERING_VALUE 1

/* Keys for AudioProcessing::NoiseSuppression */
#define APM_NOISE_SUPPRESSION_ENABLED "apm:noise_suppression_enabled"
#define APM_NOISE_SUPPRESSION_ENABLED_VALUE 0
/* 0: low, 1: moderate, 2: high, 3: very high*/
#define APM_NOISE_SUPPRESSION_LEVEL "apm:noise_suppression_level"
#define APM_NOISE_SUPPRESSION_LEVEL_VALUE 2
#define APM_NOISE_SUPPRESSION_ANALYZE_LINEAR_AEC_OUTPUT_WHEN_AVAILABLE \
	"apm:noise_suppression_analyze_linear_aec_output_when_available"
#define APM_NOISE_SUPPRESSION_ANALYZE_LINEAR_AEC_OUTPUT_WHEN_AVAILABLE_VALUE 0

/* Keys for AudioProcessing::TransientSuppression */
#define APM_TRANSIENT_SUPPRESSION_ENABLED "apm:transient_suppression_enabled"
#define APM_TRANSIENT_SUPPRESSION_ENABLED_VALUE 0

/* Keys for AudioProcessing::VoiceDetection */
#define APM_VOICE_DETECTION_ENABLED "apm:voice_detection_enabled"
#define APM_VOICE_DETECTION_ENABLED_VALUE 0


/* Keys for AudioProcessing::GainController1 */
/* 0: adaptive analog, 1: adaptive digital, 2: fixed digital */
#define APM_GAIN_CONTROL_ENABLED "apm:gain_control_enabled"
#define APM_GAIN_CONTROL_ENABLED_VALUE 0
/* 0: kAdaptiveAnalog, 1: kAdaptiveDigital, 2: kFixedDigital */
#define APM_GAIN_CONTROL_MODE "apm:gain_control_mode"
#define APM_GAIN_CONTROL_MODE_VALUE 0
#define APM_GAIN_CONTROL_TARGET_LEVEL_DBFS "apm:gain_control_target_level_dbfs"
#define APM_GAIN_CONTROL_TARGET_LEVEL_DBFS_VALUE 3
#define APM_GAIN_CONTROL_COMPRESSION_GAIN_DB \
	 "apm:gain_control_compression_gain_db"
#define APM_GAIN_CONTROL_COMPRESSION_GAIN_DB_VALUE 9
#define APM_GAIN_CONTROL_ENABLE_LIMITER "apm:gain_control_enable_limiter"
#define APM_GAIN_CONTROL_ENABLE_LIMITER_VALUE 1
#define APM_GAIN_CONTROL_ANALOG_LEVEL_MINIMUM \
	 "apm:gain_control_analog_level_minimum"
#define APM_GAIN_CONTROL_ANALOG_LEVEL_MINIMUM_VALUE 0
#define APM_GAIN_CONTROL_ANALOG_LEVEL_MAXIMUM \
	 "apm:gain_control_analog_level_maximum"
#define APM_GAIN_CONTROL_ANALOG_LEVEL_MAXIMUM_VALUE 255

/* Keys for AudioProcessing::GainController1::AnalogGainController */
#define APM_ANALOG_GAIN_CONTROLLER_ENABLED "apm:analog_gain_controller_enabled"
#define APM_ANALOG_GAIN_CONTROLLER_ENABLED_VALUE 1
#define APM_ANALOG_GAIN_CONTROLLER_STARTUP_MIN_VOLUME \
	"apm:analog_gain_controller_startup_min_volume"
#define APM_ANALOG_GAIN_CONTROLLER_STARTUP_MIN_VOLUME_VALUE 85
#define APM_ANALOG_GAIN_CONTROLLER_CLIPPED_LEVEL_MIN \
	"apm:analog_gain_controller_clipped_level_min"
#define APM_ANALOG_GAIN_CONTROLLER_CLIPPED_LEVEL_MIN_VALUE 70
#define APM_ANALOG_GAIN_CONTROLLER_ENABLE_DIGITAL_ADAPTIVE \
	"apm:analog_gain_controller_enable_digital_adaptive"
#define APM_ANALOG_GAIN_CONTROLLER_ENABLE_DIGITAL_ADAPTIVE_VALUE 1

/* Keys for AudioProcessing::GainController2 */
#define APM_GAIN_CONTROLLER2_ENABLED "apm:gain_controller2_enabled"
#define APM_GAIN_CONTROLLER2_ENABLED_VALUE 0

/* Keys for AudioProcessing::GainController2::FixedDigital */
#define APM_GAIN_CONTROLLER2_FIXED_DIGITAL_GAIN_DB \
	"apm:gain_controller2_fixed_digital_gain_db"
#define APM_GAIN_CONTROLLER2_FIXED_DIGITAL_GAIN_DB_VALUE 0.f

/* Keys for AudioProcessing::GainController2::AdaptiveDigital */
#define ADAPTIVE_DIGITAL_ENABLED "apm:adaptive_digital_enabled"
#define ADAPTIVE_DIGITAL_ENABLED_VALUE 0
#define ADAPTIVE_DIGITAL_VAD_PROBABILITY_ATTACK \
	"apm:adaptive_digital_vad_probability_attack"
#define ADAPTIVE_DIGITAL_VAD_PROBABILITY_ATTACK_VALUE 0.3f
/* 0: kRms, 1: kPeak */
#define ADAPTIVE_DIGITAL_LEVEL_ESTIMATOR \
	"apm:adaptive_digital_level_estimator"
#define ADAPTIVE_DIGITAL_LEVEL_ESTIMATOR_VALUE 0
#define ADAPTIVE_DIGITAL_LEVEL_ESTIMATOR_ADJACENT_SPEECH_FRAMES_THRESHOLD \
	"apm:adaptive_digital_level_estimator_adjacent_speech_frames_threshold"
#define ADAPTIVE_DIGITAL_LEVEL_ESTIMATOR_ADJACENT_SPEECH_FRAMES_THRESHOLD_VALUE 6
#define ADAPTIVE_DIGITAL_USE_SATURATION_PROTECTOR \
	"apm:adaptive_digital_use_saturation_protector"
#define ADAPTIVE_DIGITAL_USE_SATURATION_PROTECTOR_VALUE 1
#define ADAPTIVE_DIGITAL_INITIAL_SATURATION_MARGIN_DB \
	"apm:adaptive_digital_initial_saturation_margin_db"
#define ADAPTIVE_DIGITAL_INITIAL_SATURATION_MARGIN_DB_VALUE 20.f
#define ADAPTIVE_DIGITAL_EXTRA_SATURATION_MARGIN_DB \
	"apm:adaptive_digital_extra_saturation_margin_db"
#define ADAPTIVE_DIGITAL_EXTRA_SATURATION_MARGIN_DB_VALUE 5.f
#define ADAPTIVE_DIGITAL_GAIN_APPLIER_ADJACENT_SPEECH_FRAMES_THRESHOLD \
	"apm:adaptive_digital_gain_applier_adjacent_speech_frames_threshold"
#define ADAPTIVE_DIGITAL_GAIN_APPLIER_ADJACENT_SPEECH_FRAMES_THRESHOLD_VALUE 6
#define ADAPTIVE_DIGITAL_MAX_GAIN_CHANGE_DB_PER_SECOND \
	"apm:adaptive_digital_max_gain_change_db_per_second"
#define ADAPTIVE_DIGITAL_MAX_GAIN_CHANGE_DB_PER_SECOND_VALUE 3.f
#define ADAPTIVE_DIGITAL_MAX_OUTPUT_NOISE_LEVEL_DBFS \
	"apm:adaptive_digital_max_output_noise_level_dbfs"
#define ADAPTIVE_DIGITAL_MAX_OUTPUT_NOISE_LEVEL_DBFS_VALUE -55.f
#define ADAPTIVE_DIGITAL_SSE2_ALLOWED \
	"apm:adaptive_digital_sse2_allowed"
#define ADAPTIVE_DIGITAL_SSE2_ALLOWED_VALUE 1
#define ADAPTIVE_DIGITAL_AVX2_ALLOWED \
	"apm:adaptive_digital_avx2_allowed"
#define ADAPTIVE_DIGITAL_AVX2_ALLOWED_VALUE 1
#define ADAPTIVE_DIGITAL_NEON_ALLOWED \
	"apm:adaptive_digital_neon_allowed"
#define ADAPTIVE_DIGITAL_NEON_ALLOWED_VALUE 1

/* Keys for AudioProcessing::ResidualEchoDetector */
#define APM_RESIDUAL_ECHO_DETECTOR_ENABLED "apm:residual_echo_detector_enabled"
#define APM_RESIDUAL_ECHO_DETECTOR_ENABLED_VALUE 1

/* Keys for AudioProcessing::LevelEstimation */
#define APM_LEVEL_ESTIMATION_ENABLED "apm:level_estimation_enabled"
#define APM_LEVEL_ESTIMATION_ENABLED_VALUE 0

/* Sets the default agc config values when no ini file is present. */
void agc_set_default_config(dictionary *ini,
	webrtc::EchoCanceller3Config *config);

/* Sets the default ns config values when no ini file is present. */
void ns_set_default_config(dictionary *ini,
	webrtc::EchoCanceller3Config *config);

/* Sets the config fields from a config. */
void apm_config_set(dictionary *ini, webrtc::AudioProcessing::Config *config);

/* Prints config content to syslog. */
void apm_config_dump(dictionary *ini);

#endif /* APM_CONFIG_H_ */

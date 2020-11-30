/* Copyright 2018 The Chromium OS Authors. All rights reserved.
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

#include <syslog.h>

#include "apm_config.h"

#define APM_CONFIG_NAME "apm.ini"

#define APM_GET_INT(ini, key)	\
	iniparser_getint(	\
		ini, key,	\
		key ## _VALUE)
#define APM_GET_FLOAT(ini, key)	\
	iniparser_getdouble(	\
		ini, key,	\
		key ## _VALUE)

typedef webrtc::AudioProcessing::Config ApConfig;

void apm_config_apply(dictionary *ini, webrtc::AudioProcessing *apm)
{
	ApConfig config;
	int level_estimator;

	if (ini == NULL)
		return;

	config.residual_echo_detector.enabled =
			APM_GET_INT(ini, APM_RESIDUAL_ECHO_DETECTOR_ENABLED);
	config.high_pass_filter.enabled =
			APM_GET_INT(ini, APM_HIGH_PASS_FILTER_ENABLED);
	config.high_pass_filter.apply_in_full_band =
			APM_GET_INT(ini, APM_HIGH_PASS_FILTER_APPLY_IN_FULL_BAND);
	config.pre_amplifier.enabled =
			APM_GET_INT(ini, APM_PRE_AMPLIFIER_ENABLED);
	config.pre_amplifier.fixed_gain_factor =
			APM_GET_FLOAT(ini, APM_PRE_AMPLIFIER_FIXED_GAIN_FACTOR);

	config.echo_canceller.enabled =
		APM_GET_INT(ini, APM_ECHO_CANCELLER_ENABLED);
	config.echo_canceller.mobile_mode =
		APM_GET_INT(ini, APM_ECHO_CANCELLER_MOBILE_MODE);
	config.echo_canceller.export_linear_aec_output =
		APM_GET_INT(ini, APM_ECHO_CANCELLER_EXPORT_LINEAR_AEC_OUTPUT);
	config.echo_canceller.enforce_high_pass_filtering =
		APM_GET_INT(ini, APM_ECHO_CANCELLER_ENFORCE_HIGH_PASS_FILTERING);

	config.transient_suppression.enabled =
		APM_GET_INT(ini, APM_TRANSIENT_SUPPRESSION_ENABLED);

	config.voice_detection.enabled =
		APM_GET_INT(ini, APM_VOICE_DETECTION_ENABLED);

	config.gain_controller1.enabled =
		APM_GET_INT(ini, APM_GAIN_CONTROL_ENABLED);
	config.gain_controller1.mode = static_cast<ApConfig::GainController1::Mode>(
		APM_GET_INT(ini, APM_GAIN_CONTROL_MODE));
	config.gain_controller1.compression_gain_db =
		APM_GET_INT(ini, APM_GAIN_CONTROL_COMPRESSION_GAIN_DB);
	config.gain_controller1.target_level_dbfs =
		APM_GET_INT(ini, APM_GAIN_CONTROL_TARGET_LEVEL_DBFS);
	config.gain_controller1.enable_limiter =
		APM_GET_INT(ini, APM_GAIN_CONTROL_ENABLE_LIMITER);
	config.gain_controller1.analog_level_minimum =
		APM_GET_INT(ini, APM_GAIN_CONTROL_ANALOG_LEVEL_MINIMUM);
	config.gain_controller1.analog_level_maximum =
		APM_GET_INT(ini, APM_GAIN_CONTROL_ANALOG_LEVEL_MAXIMUM);

	/* GainController1::AnalogGainController */
	config.gain_controller1.analog_gain_controller.enabled =
		APM_GET_INT(ini, APM_ANALOG_GAIN_CONTROLLER_ENABLED);
	config.gain_controller1.analog_gain_controller.startup_min_volume =
		APM_GET_INT(ini, APM_ANALOG_GAIN_CONTROLLER_STARTUP_MIN_VOLUME);
	config.gain_controller1.analog_gain_controller.clipped_level_min =
		APM_GET_INT(ini, APM_ANALOG_GAIN_CONTROLLER_CLIPPED_LEVEL_MIN);
	config.gain_controller1.analog_gain_controller.enable_agc2_level_estimator =
		APM_GET_INT(ini, APM_ANALOG_GAIN_CONTROLLER_ENABLE_AGC2_LEVEL_ESTIMATOR);
	config.gain_controller1.analog_gain_controller.enable_digital_adaptive =
		APM_GET_INT(ini, APM_ANALOG_GAIN_CONTROLLER_ENABLE_DIGITAL_ADAPTIVE);

	config.gain_controller2.enabled =
			APM_GET_INT(ini, APM_GAIN_CONTROLLER2_ENABLED);
	config.gain_controller2.adaptive_digital.enabled =
		APM_GET_INT(ini, ADAPTIVE_DIGITAL_ENABLED);
	config.gain_controller2.adaptive_digital.vad_probability_attack =
		APM_GET_FLOAT(ini, ADAPTIVE_DIGITAL_VAD_PROBABILITY_ATTACK);
	config.gain_controller2.adaptive_digital.level_estimator_adjacent_speech_frames_threshold =
		APM_GET_INT(ini, ADAPTIVE_DIGITAL_LEVEL_ESTIMATOR_ADJACENT_SPEECH_FRAMES_THRESHOLD);
	config.gain_controller2.adaptive_digital.initial_saturation_margin_db =
		APM_GET_FLOAT(ini, ADAPTIVE_DIGITAL_INITIAL_SATURATION_MARGIN_DB);
	config.gain_controller2.adaptive_digital.gain_applier_adjacent_speech_frames_threshold =
		APM_GET_INT(ini, ADAPTIVE_DIGITAL_GAIN_APPLIER_ADJACENT_SPEECH_FRAMES_THRESHOLD);
	config.gain_controller2.adaptive_digital.max_gain_change_db_per_second =
		APM_GET_FLOAT(ini, ADAPTIVE_DIGITAL_MAX_GAIN_CHANGE_DB_PER_SECOND);
	config.gain_controller2.adaptive_digital.max_output_noise_level_dbfs =
		APM_GET_FLOAT(ini, ADAPTIVE_DIGITAL_MAX_OUTPUT_NOISE_LEVEL_DBFS);
	config.gain_controller2.adaptive_digital.extra_saturation_margin_db =
		APM_GET_FLOAT(ini, ADAPTIVE_DIGITAL_EXTRA_SATURATION_MARGIN_DB);
	level_estimator = APM_GET_INT(
		ini, ADAPTIVE_DIGITAL_LEVEL_ESTIMATOR);
	config.gain_controller2.adaptive_digital.level_estimator =
		static_cast<ApConfig::GainController2::LevelEstimator>(
			level_estimator);
	config.gain_controller2.adaptive_digital.use_saturation_protector =
		APM_GET_INT(ini, ADAPTIVE_DIGITAL_USE_SATURATION_PROTECTOR);
	config.gain_controller2.fixed_digital.gain_db =
		APM_GET_FLOAT(ini, APM_GAIN_CONTROLLER2_FIXED_DIGITAL_GAIN_DB);

	config.level_estimation.enabled =
		APM_GET_INT(ini, APM_LEVEL_ESTIMATION_ENABLED);

	config.noise_suppression.enabled =
		APM_GET_INT(ini, APM_NOISE_SUPPRESSION_ENABLED);
	config.noise_suppression.level = static_cast<ApConfig::NoiseSuppression::Level>(
		APM_GET_INT(ini, APM_NOISE_SUPPRESSION_LEVEL));
	config.noise_suppression.analyze_linear_aec_output_when_available =
		APM_GET_INT(ini, APM_NOISE_SUPPRESSION_ANALYZE_LINEAR_AEC_OUTPUT_WHEN_AVAILABLE);

	apm->ApplyConfig(config);
}

void apm_config_dump(dictionary *ini)
{
	syslog(LOG_ERR, "---- apm config dump ----");
	syslog(LOG_ERR, "residual_echo_detector_enabled %u",
		APM_GET_INT(ini, APM_RESIDUAL_ECHO_DETECTOR_ENABLED));
	syslog(LOG_ERR, "high_pass_filter_enabled %u",
		APM_GET_INT(ini, APM_HIGH_PASS_FILTER_ENABLED));
	syslog(LOG_ERR, "high_pass_filter_apply_in_full_band %d",
		APM_GET_INT(ini, APM_HIGH_PASS_FILTER_APPLY_IN_FULL_BAND));
	syslog(LOG_ERR, "pre_amplifier_enabled %u",
		APM_GET_INT(ini, APM_PRE_AMPLIFIER_ENABLED));
	syslog(LOG_ERR, "pre_amplifier_fixed_gain_factor %f",
		APM_GET_FLOAT(ini, APM_PRE_AMPLIFIER_FIXED_GAIN_FACTOR));

	syslog(LOG_ERR, "echo_canceller_enabled %d",
		APM_GET_INT(ini, APM_ECHO_CANCELLER_ENABLED));
	syslog(LOG_ERR, "echo_canceller_mobile_mode %d",
		APM_GET_INT(ini, APM_ECHO_CANCELLER_MOBILE_MODE));
	syslog(LOG_ERR, "echo_canceller_export_linear_aec_output %d",
		APM_GET_INT(ini, APM_ECHO_CANCELLER_EXPORT_LINEAR_AEC_OUTPUT));
	syslog(LOG_ERR, "echo_canceller_enforce_high_pass_filtering %d",
		APM_GET_INT(ini, APM_ECHO_CANCELLER_ENFORCE_HIGH_PASS_FILTERING));

	syslog(LOG_ERR, "transient_suppression_enabled %d",
		APM_GET_INT(ini, APM_TRANSIENT_SUPPRESSION_ENABLED));

	syslog(LOG_ERR, "voice_detection_enabled %d",
		APM_GET_INT(ini, APM_VOICE_DETECTION_ENABLED));

	syslog(LOG_ERR, "gain_controller2_enabled %u",
		APM_GET_INT(ini, APM_GAIN_CONTROLLER2_ENABLED));
	syslog(LOG_ERR, "adaptive_digital_enabled %d",
		APM_GET_INT(ini, ADAPTIVE_DIGITAL_ENABLED));
	syslog(LOG_ERR, "adaptive_digital_vad_probability_attack %f",
		APM_GET_FLOAT(ini, ADAPTIVE_DIGITAL_VAD_PROBABILITY_ATTACK));
	syslog(LOG_ERR, "adaptive_digital_level_estimator_adjacent_speech_frames_threshold %d",
		APM_GET_INT(ini, ADAPTIVE_DIGITAL_LEVEL_ESTIMATOR_ADJACENT_SPEECH_FRAMES_THRESHOLD));
	syslog(LOG_ERR, "adaptive_digital_initial_saturation_margin_db %f",
		APM_GET_FLOAT(ini, ADAPTIVE_DIGITAL_INITIAL_SATURATION_MARGIN_DB));
	syslog(LOG_ERR, "adaptive_digital_gain_applier_adjacent_speech_frames_threshold %d",
		APM_GET_INT(ini, ADAPTIVE_DIGITAL_GAIN_APPLIER_ADJACENT_SPEECH_FRAMES_THRESHOLD));
	syslog(LOG_ERR, "adaptive_digital_max_gain_change_db_per_second %f",
		APM_GET_FLOAT(ini, ADAPTIVE_DIGITAL_MAX_GAIN_CHANGE_DB_PER_SECOND));
	syslog(LOG_ERR, "adaptive_digital_max_output_noise_level_dbfs %f",
		APM_GET_FLOAT(ini, ADAPTIVE_DIGITAL_MAX_OUTPUT_NOISE_LEVEL_DBFS));
	syslog(LOG_ERR, "adaptive_digital_extra_saturation_margin_db %f",
		APM_GET_FLOAT(ini,
			ADAPTIVE_DIGITAL_EXTRA_SATURATION_MARGIN_DB));
	syslog(LOG_ERR, "adaptive_digital_level_estimator %d",
		APM_GET_INT(ini, ADAPTIVE_DIGITAL_LEVEL_ESTIMATOR));
	syslog(LOG_ERR, "adaptive_digital_use_saturation_protector %d",
		APM_GET_INT(ini, ADAPTIVE_DIGITAL_USE_SATURATION_PROTECTOR));
	syslog(LOG_ERR, "gain_controller2_fixed_digital_gain_db %f",
		APM_GET_FLOAT(ini, APM_GAIN_CONTROLLER2_FIXED_DIGITAL_GAIN_DB));

	syslog(LOG_ERR, "level_estimation_enabled %d",
		APM_GET_INT(ini, APM_LEVEL_ESTIMATION_ENABLED));

	syslog(LOG_ERR, "gain_control_compression_gain_db %u",
		APM_GET_INT(ini, APM_GAIN_CONTROL_COMPRESSION_GAIN_DB));
	syslog(LOG_ERR, "gain_control_target_level_dbfs %d",
		APM_GET_INT(ini, APM_GAIN_CONTROL_TARGET_LEVEL_DBFS));
	syslog(LOG_ERR, "gain_control_enable_limiter %d",
		APM_GET_INT(ini, APM_GAIN_CONTROL_ENABLE_LIMITER));
	syslog(LOG_ERR, "gain_control_analog_level_minimum %d",
		APM_GET_INT(ini, APM_GAIN_CONTROL_ANALOG_LEVEL_MINIMUM));
	syslog(LOG_ERR, "gain_control_analog_level_maximumc %d",
		APM_GET_INT(ini, APM_GAIN_CONTROL_ANALOG_LEVEL_MAXIMUM));
	syslog(LOG_ERR, "gain_control_mode %u",
		APM_GET_INT(ini, APM_GAIN_CONTROL_MODE));
	syslog(LOG_ERR, "gain_control_enabled %u",
		APM_GET_INT(ini, APM_GAIN_CONTROL_ENABLED));

	syslog(LOG_ERR, "analog_gain_controller_enabled %d",
		APM_GET_INT(ini, APM_ANALOG_GAIN_CONTROLLER_ENABLED));
	syslog(LOG_ERR, "analog_gain_controller_startup_min_volume %d",
		APM_GET_INT(ini, APM_ANALOG_GAIN_CONTROLLER_STARTUP_MIN_VOLUME));
	syslog(LOG_ERR, "analog_gain_controller_clipped_level_min %d",
		APM_GET_INT(ini, APM_ANALOG_GAIN_CONTROLLER_CLIPPED_LEVEL_MIN));
	syslog(LOG_ERR, "analog_gain_controller_enable_agc2_level_estimator %d",
		APM_GET_INT(ini, APM_ANALOG_GAIN_CONTROLLER_ENABLE_AGC2_LEVEL_ESTIMATOR));
	syslog(LOG_ERR, "analog_gain_controller_enable_digital_adaptive %d",
		APM_GET_INT(ini, APM_ANALOG_GAIN_CONTROLLER_ENABLE_DIGITAL_ADAPTIVE));

	syslog(LOG_ERR, "noise_suppression_level %u",
		APM_GET_INT(ini, APM_NOISE_SUPPRESSION_LEVEL));
	syslog(LOG_ERR, "noise_suppression_enabled %u",
		APM_GET_INT(ini, APM_NOISE_SUPPRESSION_ENABLED));
}

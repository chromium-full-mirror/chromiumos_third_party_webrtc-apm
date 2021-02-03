/* Copyright 2018 The Chromium OS Authors. All rights reserved.
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

#ifndef APM_CONFIG_H_
#define APM_CONFIG_H_

#include <iniparser.h>

#include "modules/audio_processing/include/audio_processing.h"

#define APM_RESIDUAL_ECHO_DETECTOR_ENABLED "apm:residual_echo_detector_enabled"
#define APM_RESIDUAL_ECHO_DETECTOR_ENABLED_VALUE 1
#define APM_HIGH_PASS_FILTER_ENABLED "apm:high_pass_filter_enabled"
#define APM_HIGH_PASS_FILTER_ENABLED_VALUE 0
#define APM_HIGH_PASS_FILTER_APPLY_IN_FULL_BAND "apm:high_pass_filter_apply_in_full_band"
#define APM_HIGH_PASS_FILTER_APPLY_IN_FULL_BAND_VALUE 1
#define APM_PRE_AMPLIFIER_ENABLED "apm:pre_amplifier_enabled"
#define APM_PRE_AMPLIFIER_ENABLED_VALUE 0
#define APM_PRE_AMPLIFIER_FIXED_GAIN_FACTOR "apm:pre_amplifier_fixed_gain_factor"
#define APM_PRE_AMPLIFIER_FIXED_GAIN_FACTOR_VALUE 1.f

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

#define APM_TRANSIENT_SUPPRESSION_ENABLED "apm:transient_suppression_enabled"
#define APM_TRANSIENT_SUPPRESSION_ENABLED_VALUE 0
#define APM_VOICE_DETECTION_ENABLED "apm:voice_detection_enabled"
#define APM_VOICE_DETECTION_ENABLED_VALUE 0

#define APM_GAIN_CONTROLLER2_ENABLED "apm:gain_controller2_enabled"
#define APM_GAIN_CONTROLLER2_ENABLED_VALUE 0
#define APM_GAIN_CONTROLLER2_FIXED_DIGITAL_GAIN_DB \
	"apm:gain_controller2_fixed_digital_gain_db"
#define APM_GAIN_CONTROLLER2_FIXED_DIGITAL_GAIN_DB_VALUE 0.f

#define APM_LEVEL_ESTIMATION_ENABLED "apm:level_estimation_enabled"
#define APM_LEVEL_ESTIMATION_ENABLED_VALUE 0

/* Keys for AudioProcessing::GainController2 */
#define ADAPTIVE_DIGITAL_ENABLED "apm:adaptive_digital_enabled"
#define ADAPTIVE_DIGITAL_ENABLED_VALUE 0
#define ADAPTIVE_DIGITAL_VAD_PROBABILITY_ATTACK \
	"apm:adaptive_digital_vad_probability_attack"
#define ADAPTIVE_DIGITAL_VAD_PROBABILITY_ATTACK_VALUE  1.f
#define ADAPTIVE_DIGITAL_LEVEL_ESTIMATOR \
	"apm:adaptive_digital_level_estimator"
#define ADAPTIVE_DIGITAL_LEVEL_ESTIMATOR_VALUE 0
#define ADAPTIVE_DIGITAL_EXTRA_SATURATION_MARGIN_DB \
	"apm:adaptive_digital_extra_saturation_margin_db"
#define ADAPTIVE_DIGITAL_EXTRA_SATURATION_MARGIN_DB_VALUE 2.f
#define ADAPTIVE_DIGITAL_LEVEL_ESTIMATOR_ADJACENT_SPEECH_FRAMES_THRESHOLD \
	"apm:adaptive_digital_level_estimator_adjacent_speech_frames_threshold"
#define ADAPTIVE_DIGITAL_LEVEL_ESTIMATOR_ADJACENT_SPEECH_FRAMES_THRESHOLD_VALUE 1
#define ADAPTIVE_DIGITAL_USE_SATURATION_PROTECTOR \
	"apm:adaptive_digital_use_saturation_protector"
#define ADAPTIVE_DIGITAL_USE_SATURATION_PROTECTOR_VALUE 1
#define ADAPTIVE_DIGITAL_INITIAL_SATURATION_MARGIN_DB \
	"apm:adaptive_digital_initial_saturation_margin_db"
#define ADAPTIVE_DIGITAL_INITIAL_SATURATION_MARGIN_DB_VALUE 20.f
#define ADAPTIVE_DIGITAL_GAIN_APPLIER_ADJACENT_SPEECH_FRAMES_THRESHOLD \
	"apm:adaptive_digital_gain_applier_adjacent_speech_frames_threshold"
#define ADAPTIVE_DIGITAL_GAIN_APPLIER_ADJACENT_SPEECH_FRAMES_THRESHOLD_VALUE 1
#define ADAPTIVE_DIGITAL_MAX_GAIN_CHANGE_DB_PER_SECOND \
	"apm:adaptive_digital_max_gain_change_db_per_second"
#define ADAPTIVE_DIGITAL_MAX_GAIN_CHANGE_DB_PER_SECOND_VALUE 3.f
#define ADAPTIVE_DIGITAL_MAX_OUTPUT_NOISE_LEVEL_DBFS \
	"apm:adaptive_digital_max_output_noise_level_dbfs"
#define ADAPTIVE_DIGITAL_MAX_OUTPUT_NOISE_LEVEL_DBFS_VALUE -50.f
#define ADAPTIVE_DIGITAL_SSE2_ALLOWED \
	"apm:adaptive_digital_sse2_allowed"
#define ADAPTIVE_DIGITAL_SSE2_ALLOWED_VALUE 1
#define ADAPTIVE_DIGITAL_AVX2_ALLOWED \
	"apm:adaptive_digital_avx2_allowed"
#define ADAPTIVE_DIGITAL_AVX2_ALLOWED_VALUE 1
#define ADAPTIVE_DIGITAL_NEON_ALLOWED \
	"apm:adaptive_digital_neon_allowed"
#define ADAPTIVE_DIGITAL_NEON_ALLOWED_VALUE 1

#define APM_GAIN_CONTROL_COMPRESSION_GAIN_DB "apm:gain_control_compression_gain_db"
#define APM_GAIN_CONTROL_COMPRESSION_GAIN_DB_VALUE 9
/* 0: adaptive analog, 1: adaptive digital, 2: fixed digital */
#define APM_GAIN_CONTROL_MODE "apm:gain_control_mode"
#define APM_GAIN_CONTROL_MODE_VALUE 0
#define APM_GAIN_CONTROL_ENABLED "apm:gain_control_enabled"
#define APM_GAIN_CONTROL_ENABLED_VALUE 0
#define APM_GAIN_CONTROL_TARGET_LEVEL_DBFS "apm:gain_control_target_level_dbfs"
#define APM_GAIN_CONTROL_TARGET_LEVEL_DBFS_VALUE 3
#define APM_GAIN_CONTROL_ENABLE_LIMITER "apm:gain_control_enable_limiter"
#define APM_GAIN_CONTROL_ENABLE_LIMITER_VALUE 1
#define APM_GAIN_CONTROL_ANALOG_LEVEL_MINIMUM "apm:gain_control_analog_level_minimum"
#define APM_GAIN_CONTROL_ANALOG_LEVEL_MINIMUM_VALUE 0
#define APM_GAIN_CONTROL_ANALOG_LEVEL_MAXIMUM "apm:gain_control_analog_level_maximum"
#define APM_GAIN_CONTROL_ANALOG_LEVEL_MAXIMUM_VALUE 255

#define APM_ANALOG_GAIN_CONTROLLER_ENABLED "apm:analog_gain_controller_enabled"
#define APM_ANALOG_GAIN_CONTROLLER_ENABLED_VALUE 1
#define APM_ANALOG_GAIN_CONTROLLER_STARTUP_MIN_VOLUME \
	"apm:analog_gain_controller_startup_min_volume"
#define APM_ANALOG_GAIN_CONTROLLER_STARTUP_MIN_VOLUME_VALUE 0
#define APM_ANALOG_GAIN_CONTROLLER_CLIPPED_LEVEL_MIN \
	"apm:analog_gain_controller_clipped_level_min"
#define APM_ANALOG_GAIN_CONTROLLER_CLIPPED_LEVEL_MIN_VALUE 70
#define APM_ANALOG_GAIN_CONTROLLER_ENABLE_AGC2_LEVEL_ESTIMATOR \
	"apm:analog_gain_controller_enable_agc2_level_estimator"
#define APM_ANALOG_GAIN_CONTROLLER_ENABLE_AGC2_LEVEL_ESTIMATOR_VALUE 0
#define APM_ANALOG_GAIN_CONTROLLER_ENABLE_DIGITAL_ADAPTIVE \
	"apm:analog_gain_controller_enable_digital_adaptive"
#define APM_ANALOG_GAIN_CONTROLLER_ENABLE_DIGITAL_ADAPTIVE_VALUE 1

/* 0: low, 1: moderate, 2: high, 3: very high*/
#define APM_NOISE_SUPPRESSION_LEVEL "apm:noise_suppression_level"
#define APM_NOISE_SUPPRESSION_LEVEL_VALUE 1
#define APM_NOISE_SUPPRESSION_ENABLED "apm:noise_suppression_enabled"
#define APM_NOISE_SUPPRESSION_ENABLED_VALUE 0
#define APM_NOISE_SUPPRESSION_ANALYZE_LINEAR_AEC_OUTPUT_WHEN_AVAILABLE \
	"apm:noise_suppression_analyze_linear_aec_output_when_available"
#define APM_NOISE_SUPPRESSION_ANALYZE_LINEAR_AEC_OUTPUT_WHEN_AVAILABLE_VALUE 0

/* Gets apm config from given config directory. */
void apm_config_apply(dictionary *ini, webrtc::AudioProcessing *apm);

/* Prints config content to syslog. */
void apm_config_dump(dictionary *ini);

#endif /* APM_CONFIG_H_ */

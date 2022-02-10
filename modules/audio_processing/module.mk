# Copyright 2018 The Chromium OS Authors. All rights reserved.
# Use of this source code is governed by a BSD-style license that can be
# found in the LICENSE file.

include common.mk

module_audio_processing_CXX_OBJECTS = \
	modules/audio_processing/agc/agc.o \
	modules/audio_processing/agc/agc_manager_direct.o \
	modules/audio_processing/agc/analog_gain_stats_reporter.o \
	modules/audio_processing/agc/clipping_predictor.o \
	modules/audio_processing/agc/clipping_predictor_evaluator.o \
	modules/audio_processing/agc/clipping_predictor_level_buffer.o \
	modules/audio_processing/agc/loudness_histogram.o \
	modules/audio_processing/agc/utility.o \
	modules/audio_processing/audio_buffer.o \
	modules/audio_processing/audio_processing_builder_impl.o \
	modules/audio_processing/audio_processing_impl.o \
	modules/audio_processing/echo_control_mobile_impl.o \
	modules/audio_processing/echo_detector/circular_buffer.o \
	modules/audio_processing/echo_detector/mean_variance_estimator.o \
	modules/audio_processing/echo_detector/moving_max.o \
	modules/audio_processing/echo_detector/normalized_covariance_estimator.o \
	modules/audio_processing/gain_control_impl.o \
	modules/audio_processing/gain_controller2.o \
	modules/audio_processing/high_pass_filter.o \
	modules/audio_processing/include/audio_processing.o \
	modules/audio_processing/optionally_built_submodule_creators.o \
	modules/audio_processing/residual_echo_detector.o \
	modules/audio_processing/rms_level.o \
	modules/audio_processing/splitting_filter.o \
	modules/audio_processing/three_band_filter_bank.o \
	modules/audio_processing/transient/moving_moments.o \
	modules/audio_processing/transient/transient_detector.o \
	modules/audio_processing/transient/transient_suppressor_impl.o \
	modules/audio_processing/transient/wpd_node.o \
	modules/audio_processing/transient/wpd_tree.o \
	modules/audio_processing/typing_detection.o \
	modules/audio_processing/voice_detection.o \
	modules/audio_processing/utility/cascaded_biquad_filter.o

audio_processing_statistics_CXX_OBJECTS = \
	modules/audio_processing/include/audio_processing_statistics.o

aec_dump_interface_CXX_OBJECTS = \
	modules/audio_processing/include/aec_dump.o

aec_dump_impl_CXX_OBJECTS = \
	modules/audio_processing/aec_dump/aec_dump_impl.o \
	modules/audio_processing/aec_dump/capture_stream_info.o \
	modules/audio_processing/aec_dump/write_to_file_task.o

apm_logging_CXX_OBJECTS = \
	modules/audio_processing/logging/apm_data_dumper.o

audio_processing_c_C_OBJECTS = \
	modules/audio_processing/agc/legacy/analog_agc.o \
	modules/audio_processing/agc/legacy/digital_agc.o

aec_core_CXX_OBJECTS = \
	common_audio/third_party/ooura/fft_size_128/ooura_fft.o \
	modules/audio_processing/aecm/aecm_core.o \
	modules/audio_processing/aecm/echo_control_mobile.o \
	modules/audio_processing/utility/delay_estimator.o \
	modules/audio_processing/utility/delay_estimator_wrapper.o \
	modules/audio_processing/aecm/aecm_core_c.o

ifeq (${USE_NEON},1)
aec_core_CXX_OBJECTS += \
	common_audio/third_party/ooura/fft_size_128/ooura_fft_neon.o \
	modules/audio_processing/aecm/aecm_core_neon.o
endif

ifeq (${USE_SSE2},1)
aec_core_CXX_OBJECTS += \
	common_audio/third_party/ooura/fft_size_128/ooura_fft_sse2.o
endif

audio_frame_api_CXX_OBJECTS = \
	api/audio/audio_frame.o

aec3_factory_CXX_OBJECTS = \
	api/audio/echo_canceller3_factory.o

aec3_config_CXX_OBJECTS = \
	api/audio/echo_canceller3_config.o

agc2_CXX_OBJECTS = \
	modules/audio_processing/agc2/adaptive_digital_gain_applier.o \
	modules/audio_processing/agc2/adaptive_digital_gain_controller.o \
	modules/audio_processing/agc2/adaptive_mode_level_estimator.o \
	modules/audio_processing/agc2/agc2_testing_common.o \
	modules/audio_processing/agc2/biquad_filter.o \
	modules/audio_processing/agc2/compute_interpolated_gain_curve.o \
	modules/audio_processing/agc2/cpu_features.o \
	modules/audio_processing/agc2/fixed_digital_level_estimator.o \
	modules/audio_processing/agc2/gain_applier.o \
	modules/audio_processing/agc2/interpolated_gain_curve.o \
	modules/audio_processing/agc2/limiter.o \
	modules/audio_processing/agc2/limiter_db_gain_curve.o \
	modules/audio_processing/agc2/noise_level_estimator.o \
	modules/audio_processing/agc2/saturation_protector_buffer.o \
	modules/audio_processing/agc2/saturation_protector.o \
	modules/audio_processing/agc2/vad_wrapper.o \
	modules/audio_processing/agc2/vector_float_frame.o \
	modules/audio_processing/utility/pffft_wrapper.o \
	third_party/pffft/src/pffft.o \
	third_party/rnnoise/src/rnn_vad_weights.o

# Dependency of agc/agc.o
vad_CXX_OBJECTS = \
	modules/audio_processing/vad/gmm.o \
	modules/audio_processing/vad/pitch_based_vad.o \
	modules/audio_processing/vad/pitch_internal.o \
	modules/audio_processing/vad/pole_zero_filter.o \
	modules/audio_processing/vad/standalone_vad.o \
	modules/audio_processing/vad/vad_audio_proc.o \
	modules/audio_processing/vad/vad_circular_buffer.o \
	modules/audio_processing/vad/voice_activity_detector.o

# Dependency of vad objects
audio_frame_operations_CXX_OBJECTS = \
	audio/utility/audio_frame_operations.o

ns_CXX_OBJECTS = \
	modules/audio_processing/ns/fast_math.o \
	modules/audio_processing/ns/histograms.o \
	modules/audio_processing/ns/noise_estimator.o \
	modules/audio_processing/ns/noise_suppressor.o \
	modules/audio_processing/ns/ns_fft.o \
	modules/audio_processing/ns/prior_signal_model.o \
	modules/audio_processing/ns/prior_signal_model_estimator.o \
	modules/audio_processing/ns/quantile_noise_estimator.o \
	modules/audio_processing/ns/signal_model.o \
	modules/audio_processing/ns/signal_model_estimator.o \
	modules/audio_processing/ns/speech_probability_estimator.o \
	modules/audio_processing/ns/suppression_params.o \
	modules/audio_processing/ns/wiener_filter.o

capture_levels_adjuster_CXX_OBJECTS = \
	modules/audio_processing/capture_levels_adjuster/audio_samples_scaler.o \
	modules/audio_processing/capture_levels_adjuster/capture_levels_adjuster.o

# TODO(hychao): WEBRTC_NS_FLOAT=0 for cases prefer fixed point operation
CXX_STATIC_LIBRARY(libaudio_processing.pic.a): \
	CPPFLAGS += -I. -DWEBRTC_POSIX \
		-DWEBRTC_APM_DEBUG_DUMP=0 \
		-DWEBRTC_INTELLIGIBILITY_ENHANCER=0 \
		-DWEBRTC_NS_FLOAT=1

CXX_STATIC_LIBRARY(libaudio_processing.pic.a): \
	$(module_audio_processing_CXX_OBJECTS) \
	$(audio_processing_statistics_CXX_OBJECTS) \
	$(aec_dump_interface_CXX_OBJECTS) \
	$(aec_dump_impl_CXX_OBJECTS) \
	$(apm_logging_CXX_OBJECTS) \
	$(audio_processing_c_C_OBJECTS) \
	$(aec_core_CXX_OBJECTS) \
	$(audio_frame_api_CXX_OBJECTS) \
	$(agc2_CXX_OBJECTS) \
	$(vad_CXX_OBJECTS) \
	$(audio_frame_api_CXX_OBJECTS) \
	$(aec3_factory_CXX_OBJECTS) \
	$(aec3_config_CXX_OBJECTS) \
	$(ns_CXX_OBJECTS) \
	$(capture_levels_adjuster_CXX_OBJECTS)

module/libaudio_processing: CXX_STATIC_LIBRARY(libaudio_processing.pic.a)

clean: CLEAN(libaudio_processing.pic.a)

.PHONY: module/libaudio_processing

PROTO_DIR = "modules/audio_processing"

$(PROTO_DIR)/debug.pb.cc \
$(PROTO_DIR)/debug.pb.h:
	protoc -I $(PROTO_DIR) --cpp_out=$(PROTO_DIR) $(PROTO_DIR)/debug.proto
clean: CLEAN($(PROTO_DIR)/debug.pb.h $(PROTO_DIR)/debug.pb.cc)
$(eval $(call add_object_rules,$(PROTO_DIR)/debug.pb.o,CXX,cc,CXXFLAGS))

modules/audio_processing/aec_dump/aec_dump_impl.o.depends \
modules/audio_processing/aec_dump/capture_stream_info.o.depends \
modules/audio_processing/aec_dump/write_to_file_task.o.depends: \
	$(PROTO_DIR)/debug.pb.h

audioproc_debug_proto_CXX_OBJECTS = \
	$(PROTO_DIR)/debug.pb.o

CXX_STATIC_LIBRARY(libaudioproc_debug_proto.pic.a): \
	$(audioproc_debug_proto_CXX_OBJECTS)

modules/audio_processing/libaudioproc_debug_proto: \
	CXX_STATIC_LIBRARY(libaudioproc_debug_proto.pic.a)

clean: CLEAN(libaudioproc_debug_proto.pic.a)

.PHONY: modules/audio_processing/libaudioproc_debug_proto

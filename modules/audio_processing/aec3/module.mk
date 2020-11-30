# Copyright 2018 The Chromium OS Authors. All rights reserved.
# Use of this source code is governed by a BSD-style license that can be
# found in the LICENSE file.

include common.mk

aec3_avx2: CXX_STATIC_LIBRARY(aec3_avx2.pic.a)

aec3_avx2_CXX_OBJECTS = \
	modules/audio_processing/aec3/adaptive_fir_filter_avx2.o \
	modules/audio_processing/aec3/adaptive_fir_filter_erl_avx2.o \
	modules/audio_processing/aec3/fft_data_avx2.o \
	modules/audio_processing/aec3/matched_filter_avx2.o \
	modules/audio_processing/aec3/vector_math_avx2.o

CXX_STATIC_LIBRARY(aec3_avx2.pic.a): \
	CPPFLAGS += -I. -DWEBRTC_POSIX \
		-DWEBRTC_APM_DEBUG_DUMP=0 \
		-DWEBRTC_INTELLIGIBILITY_ENHANCER=0 \
		-DWEBRTC_NS_FLOAT=1 \
		-mavx2 -mfma

CXX_STATIC_LIBRARY(aec3_avx2.pic.a): \
	$(aec3_avx2_CXX_OBJECTS)

aec3_CXX_OBJECTS = \
	modules/audio_processing/aec3/adaptive_fir_filter.o \
	modules/audio_processing/aec3/adaptive_fir_filter_erl.o \
	modules/audio_processing/aec3/aec3_common.o \
	modules/audio_processing/aec3/aec3_fft.o \
	modules/audio_processing/aec3/aec_state.o \
	modules/audio_processing/aec3/alignment_mixer.o \
	modules/audio_processing/aec3/api_call_jitter_metrics.o\
	modules/audio_processing/aec3/block_delay_buffer.o \
	modules/audio_processing/aec3/block_framer.o \
	modules/audio_processing/aec3/block_processor.o \
	modules/audio_processing/aec3/block_processor_metrics.o \
	modules/audio_processing/aec3/clockdrift_detector.o \
	modules/audio_processing/aec3/comfort_noise_generator.o \
	modules/audio_processing/aec3/decimator.o \
	modules/audio_processing/aec3/dominant_nearend_detector.o \
	modules/audio_processing/aec3/downsampled_render_buffer.o \
	modules/audio_processing/aec3/echo_audibility.o \
	modules/audio_processing/aec3/echo_canceller3.o \
	modules/audio_processing/aec3/echo_path_delay_estimator.o \
	modules/audio_processing/aec3/echo_path_variability.o \
	modules/audio_processing/aec3/echo_remover.o \
	modules/audio_processing/aec3/echo_remover_metrics.o \
	modules/audio_processing/aec3/erl_estimator.o \
	modules/audio_processing/aec3/erle_estimator.o \
	modules/audio_processing/aec3/fft_buffer.o \
	modules/audio_processing/aec3/filter_analyzer.o \
	modules/audio_processing/aec3/frame_blocker.o \
	modules/audio_processing/aec3/fullband_erle_estimator.o \
	modules/audio_processing/aec3/refined_filter_update_gain.o \
	modules/audio_processing/aec3/matched_filter.o \
	modules/audio_processing/aec3/matched_filter_lag_aggregator.o \
	modules/audio_processing/aec3/block_buffer.o \
	modules/audio_processing/aec3/matched_filter.o \
	modules/audio_processing/aec3/moving_average.o \
	modules/audio_processing/aec3/render_buffer.o \
	modules/audio_processing/aec3/render_delay_buffer.o \
	modules/audio_processing/aec3/render_delay_controller.o \
	modules/audio_processing/aec3/render_delay_controller_metrics.o \
	modules/audio_processing/aec3/render_signal_analyzer.o \
	modules/audio_processing/aec3/residual_echo_estimator.o \
	modules/audio_processing/aec3/reverb_decay_estimator.o \
	modules/audio_processing/aec3/reverb_frequency_response.o \
	modules/audio_processing/aec3/reverb_model.o \
	modules/audio_processing/aec3/reverb_model_estimator.o \
	modules/audio_processing/aec3/coarse_filter_update_gain.o \
	modules/audio_processing/aec3/signal_dependent_erle_estimator.o \
	modules/audio_processing/aec3/stationarity_estimator.o \
	modules/audio_processing/aec3/subband_erle_estimator.o \
	modules/audio_processing/aec3/subband_nearend_detector.o \
	modules/audio_processing/aec3/subtractor.o \
	modules/audio_processing/aec3/subtractor_output.o \
	modules/audio_processing/aec3/subtractor_output_analyzer.o \
	modules/audio_processing/aec3/suppression_filter.o \
	modules/audio_processing/aec3/suppression_gain.o \
	modules/audio_processing/aec3/spectrum_buffer.o \
	modules/audio_processing/aec3/transparent_mode.o \
	modules/audio_processing/utility/cascaded_biquad_filter.o

aec3: CXX_STATIC_LIBRARY(aec3.pic.a)

CXX_STATIC_LIBRARY(aec3.pic.a): \
	CPPFLAGS += -I. -DWEBRTC_POSIX \
		-DWEBRTC_APM_DEBUG_DUMP=0 \
		-DWEBRTC_INTELLIGIBILITY_ENHANCER=0 \
		-DWEBRTC_NS_FLOAT=1

CXX_STATIC_LIBRARY(aec3.pic.a): \
	$(aec3_CXX_OBJECTS)

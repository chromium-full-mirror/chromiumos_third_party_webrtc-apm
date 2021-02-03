# Copyright 2018 The Chromium OS Authors. All rights reserved.
# Use of this source code is governed by a BSD-style license that can be
# found in the LICENSE file.

include common.mk

rnn_vad_avx2_CXX_OBJECTS = \
	modules/audio_processing/agc2/rnn_vad/vector_math_avx2.o

CXX_STATIC_LIBRARY(rnn_vad_avx2.pic.a): \
	CPPFLAGS += -I. -mavx2 -mfma

CXX_STATIC_LIBRARY(rnn_vad_avx2.pic.a): \
	$(rnn_vad_avx2_CXX_OBJECTS)

rnn_vad_avx2: CXX_STATIC_LIBRARY(rnn_vad_avx2.pic.a)

rnn_vad_CXX_OBJECTS = \
	modules/audio_processing/agc2/rnn_vad/auto_correlation.o \
	modules/audio_processing/agc2/rnn_vad/features_extraction.o \
	modules/audio_processing/agc2/rnn_vad/lp_residual.o \
	modules/audio_processing/agc2/rnn_vad/pitch_search.o \
	modules/audio_processing/agc2/rnn_vad/pitch_search_internal.o \
	modules/audio_processing/agc2/rnn_vad/rnn.o \
	modules/audio_processing/agc2/rnn_vad/rnn_fc.o \
	modules/audio_processing/agc2/rnn_vad/rnn_gru.o \
	modules/audio_processing/agc2/rnn_vad/spectral_features.o \
	modules/audio_processing/agc2/rnn_vad/spectral_features_internal.o \
	modules/audio_processing/agc2/cpu_features.o

CXX_STATIC_LIBRARY(rnn_vad.pic.a): \
	CPPFLAGS += -I.

CXX_STATIC_LIBRARY(rnn_vad.pic.a): \
	$(rnn_vad_CXX_OBJECTS)

rnn_vad: CXX_STATIC_LIBRARY(rnn_vad.pic.a)

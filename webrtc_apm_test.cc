// Copyright 2023 The ChromiumOS Authors
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "webrtc_apm.h"

#include "gtest/gtest.h"

extern "C" {
#include "iniparser.h"
}

TEST(WebRTCAPM, Smoke) {
  dictionary* aec_ini = dictionary_new(0);
  dictionary* apm_ini = dictionary_new(0);
  webrtc_apm apm = webrtc_apm_create_with_enforced_effects(1, 48000, aec_ini,
                                                           apm_ini, 0, 0, 0);
  dictionary_del(aec_ini);
  dictionary_del(apm_ini);
  webrtc_apm_destroy(apm);
}

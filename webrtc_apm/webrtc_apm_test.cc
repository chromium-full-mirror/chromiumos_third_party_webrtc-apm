// Copyright 2023 The ChromiumOS Authors
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "webrtc_apm/webrtc_apm.h"

#include <numeric>
#include <vector>

#include "common_audio/wav_file.h"
#include "gmock/gmock.h"
#include "gtest/gtest.h"

namespace {

TEST(WebRTCAPM, Smoke) {
  webrtc_apm apm = webrtc_apm_create_with_enforced_effects(1, 48000, nullptr,
                                                           nullptr, 1, 0, 0);
  EXPECT_TRUE(webrtc_apm_get_active_effects(apm).echo_cancellation);
  EXPECT_FALSE(webrtc_apm_get_active_effects(apm).noise_suppression);
  EXPECT_FALSE(webrtc_apm_get_active_effects(apm).voice_activity_detection);

  webrtc_apm_enable_effects(apm, false, true, false);
  EXPECT_FALSE(webrtc_apm_get_active_effects(apm).echo_cancellation);
  EXPECT_TRUE(webrtc_apm_get_active_effects(apm).noise_suppression);
  EXPECT_FALSE(webrtc_apm_get_active_effects(apm).voice_activity_detection);

  webrtc_apm_enable_vad(apm, true);
  EXPECT_FALSE(webrtc_apm_get_active_effects(apm).echo_cancellation);
  EXPECT_TRUE(webrtc_apm_get_active_effects(apm).noise_suppression);
  EXPECT_TRUE(webrtc_apm_get_active_effects(apm).voice_activity_detection);

  webrtc_apm_destroy(apm);
}

TEST(WebRTCAPM, Stats) {
  webrtc_apm apm = webrtc_apm_create_with_enforced_effects(1, 48000, nullptr,
                                                           nullptr, 1, 0, 0);

  EXPECT_EQ(webrtc_apm_get_stats(apm).forward_blocks_processed, 0);
  EXPECT_EQ(webrtc_apm_get_stats(apm).reverse_blocks_processed, 0);

  std::vector<float> buffer(480);

  float* ptr = buffer.data();
  webrtc_apm_process_stream_f(apm, 1, 48000, &ptr);

  EXPECT_EQ(webrtc_apm_get_stats(apm).forward_blocks_processed, 1);
  EXPECT_EQ(webrtc_apm_get_stats(apm).reverse_blocks_processed, 0);

  webrtc_apm_process_reverse_stream_f(apm, 1, 48000, &ptr);

  EXPECT_EQ(webrtc_apm_get_stats(apm).forward_blocks_processed, 1);
  EXPECT_EQ(webrtc_apm_get_stats(apm).reverse_blocks_processed, 1);

  webrtc_apm_destroy(apm);
}

struct VADParam {
  bool enable_aec = false;
};

class VADTest : public ::testing::TestWithParam<VADParam> {
 protected:
  void SetUp() override {
    aec_ini_ = dictionary_new(0);
    apm_ini_ = dictionary_new(0);
    apm_ = webrtc_apm_create_with_enforced_effects(1, 48000, aec_ini_, apm_ini_,
                                                   GetParam().enable_aec, 0, 0);
    webrtc_apm_enable_vad(apm_, true);
    EXPECT_TRUE(webrtc_apm_get_active_effects(apm_).voice_activity_detection);
  }

  void TearDown() override {
    webrtc_apm_destroy(apm_);
    dictionary_del(aec_ini_);
    dictionary_del(apm_ini_);
  }

 protected:
  dictionary* aec_ini_;
  dictionary* apm_ini_;
  webrtc_apm apm_;
};

MATCHER_P(SumGreaterThan, n, "") {
  return std::accumulate(arg.begin(), arg.end(), 0) > n;
}

TEST_P(VADTest, Speech) {
  webrtc::WavReader wav("external/the_quick_brown_fox_wav/file/downloaded");

  // For documentation purposes.
  ASSERT_EQ(wav.num_channels(), 1);
  ASSERT_EQ(wav.num_samples(), 81792);

  std::vector<float> buffer(480);

  std::vector<int> detected;
  for (int i = 0; i < 60; i++) {
    ASSERT_EQ(wav.ReadSamples(buffer.size(), buffer.data()), buffer.size());
    float* ptr = buffer.data();
    webrtc_apm_process_stream_f(apm_, 1, 48000, &ptr);
    detected.push_back(webrtc_apm_get_voice_detected(apm_));
  }
  EXPECT_THAT(detected, SumGreaterThan(35));
}

TEST_P(VADTest, Silence) {
  for (int i = 0; i < 40; i++) {
    std::vector<float> buffer(480);

    float* ptr = buffer.data();
    webrtc_apm_process_stream_f(apm_, 1, 48000, &ptr);
    EXPECT_FALSE(webrtc_apm_get_voice_detected(apm_)) << "i = " << i;
  }
}

INSTANTIATE_TEST_SUITE_P(VADTestSuite, VADTest,
                         testing::Values(VADParam{.enable_aec = true},
                                         VADParam{.enable_aec = false}));

}  // namespace

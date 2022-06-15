/* Copyright 2018 The Chromium OS Authors. All rights reserved.
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

#ifndef WEBRTC_APM_H_
#define WEBRTC_APM_H_

#include <iniparser.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

#define WEBRTC_APM_API __attribute__((visibility("default")))

/* Pointer to a webrtc::AudioProcessing instance. */
typedef void *webrtc_apm;

/* Enables UMA metrics in webrtc APM.
 * Args:
 *    prefix - String to append to existing histogram name.
 */
WEBRTC_APM_API void webrtc_apm_init_metrics(const char *prefix);

/* Creates a webrtc_apm for forward stream properties using optional enforcement
 * of the effects that are specified in the config files. In CRAS use case it
 * is usually created for input stream.
 * Args:
 *    num_channels   - Number of channels of the forward stream.
 *    frame_rate     - Frame rate used by forward stream.
 *    aec_config     - Pointer to aec config.
 *    apm_config     - Pointer to apm config.
 *    enforce_aec_on - When set to 1, enforces the aec to be activated
 *                     regardless of settings in apm.ini.
 *    enforce_ns_on  - When set to 1, enforces the ns to be activated
 *                     regardless of settings in apm.ini.
 *    enforce_agc_on - When set to 1, enforces the agc to be activated
 *                     regardless of settings in apm.ini.
 */
WEBRTC_APM_API webrtc_apm webrtc_apm_create_with_enforced_effects(
    unsigned int num_channels,
    unsigned int frame_rate,
    dictionary *aec_ini,
    dictionary *apm_ini,
    unsigned int enforce_aec_on,
    unsigned int enforce_ns_on,
    unsigned int enforce_agc_on);

/* Collection of flags indicating which APM features are enabled. */
typedef struct {
  /* When set to true and AGC is active in APM, indicates to use the AGC2
   * implementation instead of the AGC1 one.
   * TODO(crbug.com/1318461): When analog AGC2 added, remove next 2 lines.
   * Note that at the moment AGC2 lacks an analog controller and offers only
   * fixed digital and adaptive digital controllers and a limiter. */
  bool agc2_enabled;
} WebRtcApmFeatures;

/* Creates a webrtc_apm for forward stream properties using optional enforcement
 * of the effects that are specified in the config files. In CRAS use case it
 * is usually created for input stream.
 * Only used for testing.
 *
 * Args:
 *    num_channels   - Number of channels of the forward stream.
 *    frame_rate     - Frame rate used by forward stream.
 *    aec_config     - Pointer to aec config.
 *    apm_config     - Pointer to apm config.
 *    enforce_aec_on - When set to 1, enforces the aec to be activated
 *                     regardless of settings in apm.ini.
 *    enforce_ns_on  - When set to 1, enforces the ns to be activated
 *                     regardless of settings in apm.ini.
 *    enforce_agc_on - When set to 1, enforces the agc to be activated
 *                     regardless of settings in apm.ini.
 *    features       - Indicates which APM features are enabled, overrides the
 *                     values obtained
 */
WEBRTC_APM_API webrtc_apm webrtc_apm_create_for_testing(
    unsigned int num_channels,
    unsigned int frame_rate,
    dictionary *aec_ini,
    dictionary *apm_ini,
    unsigned int enforce_aec_on,
    unsigned int enforce_ns_on,
    unsigned int enforce_agc_on,
    WebRtcApmFeatures features);

/* Enables/disables effects in a webrtc_apm.
 * This call is fully thread-safe and safe to use concurrently with
 * any of the processing methods, e.g.
 * webrtc_apm_process_reverse_stream_f, webrtc_apm_process_stream_f
 * webrtc_apm_aec_dump, webrtc_apm_set_stream_delay.
 * However, the call currently has a temporary impact on the real-time
 * performance and should be used with care and and as little as possible.
 *
 * Args:
 *    ptr        - Pointer to the webrtc_apm instance.
 *    enable_aec - When set to 1, enables the AEC.
 *    enable_ns  - When set to 1, enables the NS.
 *    enable_agc - When set to 1, enables the AGC.
 */
WEBRTC_APM_API void webrtc_apm_enable_effects(webrtc_apm ptr,
                                              bool enable_aec,
                                              bool enable_ns,
                                              bool enable_agc);

/* Dumps configs content.
 * Args:
 *    apm_ini - APM config file in ini format.
 *    aec_ini - AEC3 config file in ini format.
 */
WEBRTC_APM_API void webrtc_apm_dump_configs(dictionary *apm_ini,
                                            dictionary *aec_ini);

/* Destroys a webrtc_apm instance. */
WEBRTC_APM_API void webrtc_apm_destroy(webrtc_apm apm);

/* Processes deinterleaved float data in reverse stream. Expecting data
 * size be 10 ms equivalent of frames. */
WEBRTC_APM_API int webrtc_apm_process_reverse_stream_f(webrtc_apm ptr,
                                                       int num_channels,
                                                       int rate,
                                                       float *const *data);

/* Processes deinterleaved float data in forward stream. Expecting data
 * size be 10 ms equivalent of frames. */
WEBRTC_APM_API int webrtc_apm_process_stream_f(webrtc_apm ptr,
                                               int num_channels,
                                               int rate,
                                               float *const *data);

/* Sets the delay in ms between apm analyzes a frame in reverse stream
 * (playback) and this frame received as echo in forward stream (record)
 * This is required for echo cancellation enabled apm.
 * Args:
 *    ptr - Pointer to the webrtc_apm instance.
 *    delay_ms - The delay in ms.
 */
WEBRTC_APM_API int webrtc_apm_set_stream_delay(webrtc_apm ptr, int delay_ms);

/* Dump aec debug info to a file.
 * Args:
 *    ptr - Pointer to the webrtc_apm instance.
 *    work_queue - Pointer holding or to hold the allocated task queue for
 *        aec dump. Will be deleted when aec dump stops.
 *    start - True to start dumping, false to stop.
 *    handle - Pointer of the file storing aec dump.
 */
WEBRTC_APM_API int webrtc_apm_aec_dump(webrtc_apm ptr,
                                       void **work_queue,
                                       int start,
                                       FILE *handle);

#endif /* WEBRTC_APM_H_ */

/*
 * Copyright 2023 The ChromiumOS Authors
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

#ifndef METRICS_METRICS_LIBRARY_H_
#define METRICS_METRICS_LIBRARY_H_

#if defined(__cplusplus)
extern "C" {
#endif

typedef void* CMetricsLibrary;

static inline CMetricsLibrary CMetricsLibraryNew() { return nullptr; }

static inline void CMetricsLibraryDelete(CMetricsLibrary handle) {}

static inline int CMetricsLibrarySendToUMA(CMetricsLibrary handle,
                                           const char* name, int sample,
                                           int min, int max, int nbuckets) {
  return 0;
}

#if defined(__cplusplus)
}
#endif

#endif

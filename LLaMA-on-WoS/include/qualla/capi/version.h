// Copyright 2023 Qualcomm Technologies, Inc. All rights reserved.
// Confidential & Proprietary - Qualcomm Technologies, Inc. ("QTI")

#ifndef QUALLA_CAPI_VERSION_H
#define QUALLA_CAPI_VERSION_H

#include <qualla/detail/exports.h>

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

QUALLA_API int32_t qualla_version_major();
QUALLA_API int32_t qualla_version_minor();
QUALLA_API int32_t qualla_version_patch();

#ifdef __cplusplus
} // extern "C"
#endif

#endif // QUALLA_CAPI_ENV_H

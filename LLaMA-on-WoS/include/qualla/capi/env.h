// Copyright 2023 Qualcomm Technologies, Inc. All rights reserved.
// Confidential & Proprietary - Qualcomm Technologies, Inc. ("QTI")

#ifndef QUALLA_CAPI_ENV_H
#define QUALLA_CAPI_ENV_H

#include <qualla/detail/exports.h>

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

// Basic JSON config template for setting up the environment.
#define QUALLA_ENV_CONF_TEMPLATE_BASIC                                                             \
    "{                              \
	    \"path\": {                \
                \"models\": \"%s\",    \
                \"cache\":  \"%s\"     \
	    },                         \
	    \"log\": {                 \
                \"output\": \"%s\",    \
                \"mask\":   \"%s\",    \
                \"path\":   \"%s\"     \
	    }                          \
        }"

QUALLA_API void* qualla_env_create(const char* json_str);
QUALLA_API void  qualla_env_release(void* env);

#ifdef __cplusplus
} // extern "C"
#endif

#endif // QUALLA_CAPI_ENV_H

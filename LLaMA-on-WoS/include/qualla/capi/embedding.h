// Copyright 2023 Qualcomm Technologies, Inc. All rights reserved.
// Confidential & Proprietary - Qualcomm Technologies, Inc. ("QTI")

#ifndef QUALLA_CAPI_EMBEDDING_H
#define QUALLA_CAPI_EMBEDDING_H

#include <qualla/detail/exports.h>
#include <qualla/capi/sentence.h>

#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

QUALLA_API void* qualla_embedding_create(void* env, const char* name, const char* json_str);
QUALLA_API void  qualla_embedding_release(void* embd);

typedef void (*qualla_embedding_cb)(const float* data, size_t size, void* priv);
QUALLA_API bool qualla_embedding_query(
        void*               embd,
        const char*         str,
        qualla_embedding_cb func,
        void*               priv
);

#ifdef __cplusplus
} // extern "C"
#endif

#endif // QUALLA_CAPI_EMBEDDING_H

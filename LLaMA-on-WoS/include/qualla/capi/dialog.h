// Copyright 2023 Qualcomm Technologies, Inc. All rights reserved.
// Confidential & Proprietary - Qualcomm Technologies, Inc. ("QTI")

#ifndef QUALLA_CAPI_DIALOG_H
#define QUALLA_CAPI_DIALOG_H

#include <qualla/detail/exports.h>
#include <qualla/capi/sentence.h>

#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

QUALLA_API void* qualla_dialog_create(void* env, const char* name, const char* json_str);
QUALLA_API void  qualla_dialog_release(void* d);

typedef bool (*qualla_dialog_cb)(const char* rsp, enum qualla_sentence_code sc, void* priv);

QUALLA_API bool qualla_dialog_prime(void* d, const char* str);
QUALLA_API bool qualla_dialog_query(
        void*                     d,
        const char*               str,
        enum qualla_sentence_code c,
        qualla_dialog_cb          func,
        void*                     priv
);
QUALLA_API bool qualla_dialog_ask(void* d, const char* str, qualla_dialog_cb func, void* priv);

// Save the dialog state/history
QUALLA_API bool qualla_dialog_save(void* d, const char* name);

// Restore the dialog state/history
QUALLA_API bool qualla_dialog_restore(void* d, const char* name);

// Reset dialog state/history
QUALLA_API void qualla_dialog_reset(void* d);

#ifdef __cplusplus
} // extern "C"
#endif

#endif // QUALLA_CAPI_DIALOG_H

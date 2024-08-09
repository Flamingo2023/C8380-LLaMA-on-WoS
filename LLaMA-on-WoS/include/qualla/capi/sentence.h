// Copyright 2023 Qualcomm Technologies, Inc. All rights reserved.
// Confidential & Proprietary - Qualcomm Technologies, Inc. ("QTI")

#ifndef QUALLA_CAPI_SENTENCE_H
#define QUALLA_CAPI_SENTENCE_H

#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif

// Must match the enum in detail/sentence.hpp
enum qualla_sentence_code {
    QUALLA_SENTENCE_COMPLETE, // Complete sentence
    QUALLA_SENTENCE_BEGIN,    // First part of the sentence
    QUALLA_SENTENCE_CONTINUE, // Continuation of the sentense
    QUALLA_SENTENCE_END,      // Last part of the sentence
    QUALLA_SENTENCE_ABORT     // Sentence aborted
};

static inline const char* qualla_sentence_code_to_str(enum qualla_sentence_code c) {
    static const char* s[] = {"COMPLETE", "BEGIN", "CONTINUE", "END", "ABORT"};
    return s[c];
}

#ifdef __cplusplus
} // extern "C"
#endif

#endif // QUALLA_CAPI_SENTENCE_H

// Copyright 2023 Qualcomm Technologies, Inc. All rights reserved.
// Confidential & Proprietary - Qualcomm Technologies, Inc. ("QTI")

#ifndef QUALLA_DETAIL_SENTENCE_HPP
#define QUALLA_DETAIL_SENTENCE_HPP

#include <string>

namespace qualla {

struct Sentence {
    enum Code {
        COMPLETE, // Complete sentence
        BEGIN,    // First part of the sentence
        CONTINUE, // Continuation of the sentense
        END,      // Last part of the sentence
        ABORT     // Sentence aborted
    };

    static inline std::string str(Code c) {
        static const char* s[]{"COMPLETE", "BEGIN", "CONTINUE", "END", "ABORT"};
        return std::string(s[c]);
    }
};

} // namespace qualla

#endif // QUALLA_DETAIL_SENTENCE_HPP

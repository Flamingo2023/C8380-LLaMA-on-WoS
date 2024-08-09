//  Copyright 2023 Qualcomm Technologies, Inc. All rights reserved.
//  Confidential & Proprietary - Qualcomm Technologies, Inc. ("QTI")

#ifndef QUALLA_DETAIL_PREPROC_HPP
#define QUALLA_DETAIL_PREPROC_HPP

#include <stdio.h>
#define QUALLA_ASSERT(x)                                                                           \
    do {                                                                                           \
        if (!(x)) {                                                                                \
            fprintf(stderr, "QUALLA_ASSERT: %s:%d: %s\n", __FILE__, __LINE__, #x);                 \
            abort();                                                                               \
        }                                                                                          \
    } while (0)

#endif // QUALLA_DETAIL_PREPROC_HPP

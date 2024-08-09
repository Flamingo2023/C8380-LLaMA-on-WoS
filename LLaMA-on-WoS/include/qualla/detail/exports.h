//  Copyright 2023 Qualcomm Technologies, Inc. All rights reserved.
//  Confidential & Proprietary - Qualcomm Technologies, Inc. ("QTI")

#ifndef QUALLA_DETAIL_EXPORTS_HPP
#define QUALLA_DETAIL_EXPORTS_HPP

#ifdef _WIN32
    #ifdef qualla_EXPORTS
        #define QUALLA_API __declspec(dllexport)
    #else
        #define QUALLA_API __declspec(dllimport)
    #endif
#else // _WIN32
    #define QUALLA_API
    #define __stdcall
#endif

#endif // QUALLA_DETAIL_EXPORTS_HPP

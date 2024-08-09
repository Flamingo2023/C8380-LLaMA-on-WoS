// Copyright 2023 Qualcomm Technologies, Inc. All rights reserved.
// Confidential & Proprietary - Qualcomm Technologies, Inc. ("QTI")

#ifndef QUALLA_DETAIL_CONFIG_HPP
#define QUALLA_DETAIL_CONFIG_HPP

#include <qualla/detail/json.hpp>
#include <sstream>

namespace qualla {

struct Config {
    const qualla::json& json;
    const std::string   pref;

    Config(const qualla::json& j, const std::string& p = "qualla:") : json(j), pref(p) {}

    // Optional value, returns the default if the key is not found.
    template <typename T>
    T optional(const std::string& k, T d) {
        if (json.contains(k))
            return json[k].get<T>();
        else
            return d;
    }

    // Mandatory value, throws runtime_error if the key is not found.
    template <typename T>
    T mandatory(const std::string& k) {
        if (json.contains(k)) return json[k].get<T>();
        std::stringstream ss;
        ss << pref << " mandatory config key : (" << k << ") not found in : " << json << std::endl;
        throw std::runtime_error(ss.str());
    }

    // Optional value, returns the default if the key is not found.
    template <typename T>
    static inline T optional(const qualla::json& j, const std::string& k, T d) {
        if (j.contains(k))
            return j[k].get<T>();
        else
            return d;
    }

    // Mandatory value, throws runtime_error if the key is not found.
    template <typename T>
    static inline T mandatory(const qualla::json& j, const std::string& k) {
        if (j.contains(k)) return j[k].get<T>();
        std::stringstream ss;
        ss << "qualla: mandatory config key : (" << k << ") not found in : " << j << std::endl;
        throw std::runtime_error(ss.str());
    }
};

} // namespace qualla

#endif // QUALLA_DETAIL_CONFIG_HPP

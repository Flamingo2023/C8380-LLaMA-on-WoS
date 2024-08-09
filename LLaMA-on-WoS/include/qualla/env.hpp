// Copyright 2023 Qualcomm Technologies, Inc. All rights reserved.
// Confidential & Proprietary - Qualcomm Technologies, Inc. ("QTI")

#ifndef QUALLA_ENV_HPP
#define QUALLA_ENV_HPP

#include <qualla/detail/exports.h>
#include <qualla/detail/state.hpp>
#include <qualla/detail/json.hpp>
#include <qualla/detail/config.hpp>
#include <qualla/logger.hpp>

#include <filesystem>
#include <memory>

namespace qualla {

class Env : public State {
  public:
    QUALLA_API Env(const json& conf);
    QUALLA_API ~Env();

    struct Path {
        std::filesystem::path models;
        std::filesystem::path cache;
    };

    const Path& path() const { return _path; }

    Logger& logger() { return *_logger; }

    QUALLA_API static std::shared_ptr<Env> create(const qualla::json& conf = {});
    QUALLA_API static std::shared_ptr<Env> create(std::istream& json_stream);
    QUALLA_API static std::shared_ptr<Env> create(const std::string& json_str);

  private:
    Path                    _path;
    std::unique_ptr<Logger> _logger;
};

} // namespace qualla

#endif // QUALLA_ENV_HPP

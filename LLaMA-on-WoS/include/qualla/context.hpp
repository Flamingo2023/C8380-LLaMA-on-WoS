// Copyright 2023 Qualcomm Technologies, Inc. All rights reserved.
// Confidential & Proprietary - Qualcomm Technologies, Inc. ("QTI")

#ifndef QUALLA_CONTEXT_HPP
#define QUALLA_CONTEXT_HPP

#include <qualla/env.hpp>

#include <qualla/detail/state.hpp>
#include <qualla/detail/json.hpp>

#include <memory>
#include <stdint.h>

namespace qualla {

class Context : public State {
  public:
    QUALLA_API Context(Env& env, const std::string& name, const json& conf);

    Env& env() { return _env; }

    const std::string& name() const { return _name; }
    size_t             size() const { return _size; }
    size_t             n_ctx() const { return _size; }
    size_t             n_vocab() const { return _n_vocab; }

    int32_t bos_tok() const { return _bos_tok; }
    int32_t bos() const { return _bos_tok; }
    int32_t eos_tok() const { return _eos_tok; }
    int32_t eos() const { return _eos_tok; }

    const json& conf() const { return _conf; }

    QUALLA_API static std::unique_ptr<Context> create(
            Env&                env,
            const std::string&  name,
            const qualla::json& conf = {}
    );
    QUALLA_API static std::unique_ptr<Context> create(
            Env&               env,
            const std::string& name,
            std::istream&      json_stream
    );
    QUALLA_API static std::unique_ptr<Context> create(
            Env&               env,
            const std::string& name,
            const std::string& json_str
    );

  private:
    const std::string _name; // Contex name
    Env&              _env;  // Reference to global env
    json              _conf; // Complete context config

    size_t  _size{1024};     // Context size
    size_t  _n_vocab{32000}; // Vocab size
    int32_t _bos_tok{1};     // BOS token id
    int32_t _eos_tok{2};     // EOS token id
};

} // namespace qualla

#endif // QUALLA_CONTEXT_HPP

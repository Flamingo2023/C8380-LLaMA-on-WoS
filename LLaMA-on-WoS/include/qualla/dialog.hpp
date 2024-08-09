// Copyright 2023 Qualcomm Technologies, Inc. All rights reserved.
// Confidential & Proprietary - Qualcomm Technologies, Inc. ("QTI")

#ifndef QUALLA_DIALOG_HPP
#define QUALLA_DIALOG_HPP

#include <qualla/detail/exports.h>
#include <qualla/detail/sentence.hpp>

#include <qualla/env.hpp>
#include <qualla/context.hpp>
#include <qualla/tokenizer.hpp>
#include <qualla/sampler.hpp>
#include <qualla/engine.hpp>

#include <memory>
#include <string>
#include <string_view>
#include <vector>
#include <functional>
#include <iostream>
#include <atomic>
#include <unordered_map>

namespace qualla {

class Dialog : public State {
  public:
    Dialog(std::shared_ptr<Env> env, const std::string& name, const qualla::json& conf);
    virtual ~Dialog();

    // Response callback
    // Called for each decodable token.
    using Callback = std::function<bool(const std::string&, Sentence::Code)>;

    // Prime LLM for a specific context.
    QUALLA_API virtual bool prime(const std::string& str);

    // Query LLM.
    // Responce is provided via Callback
    QUALLA_API virtual bool query(const std::string& str, Sentence::Code, Callback rsp);

    // Ask a complete question
    bool ask(const std::string& str, Callback func) { return query(str, Sentence::COMPLETE, func); }

    // Reset the dialog state/history
    QUALLA_API virtual void reset();

    // Save the dialog state/history
    QUALLA_API virtual bool save(const std::string& name = "");

    // Restore the dialog state/history
    QUALLA_API virtual bool restore(const std::string& name = "");

    // Dialog KPIs
    struct KPIs {
        struct Tps {
            size_t n_prompt;
            size_t n_generate;
            float  prompt;
            float  generate;
        };

        Kpi init;     // init (model load, mem allocs, etc) stats
        Kpi prompt;   // prompt processor stats
        Kpi generate; // generator stats
        Kpi save;     // save stats
        Kpi restore;  // restore stats
        Tps tps;      // TPS for prompt, generate, etc

        KPIs() { reset(); }

        QUALLA_API void reset(); // reset to initial state

        QUALLA_API std::string dump(std::string_view sep = " ")
                const; // dump KPIs as a formated string
    };

    // Get refs to various layers
    Context&   context() { return *_ctx; }
    Tokenizer& tokenizer() { return *_tokenizer; }
    Sampler&   sampler(const std::string& role = "primary") { return *_sampler[role]; }
    Engine&    engine(const std::string& role = "primary") { return *_engine[role]; }

    // Get latest KPIs.
    // Updates TPS, etc as needed.
    QUALLA_API KPIs& kpis();

    // List available dialog types
    QUALLA_API static std::vector<std::string> list();

    // Dialog registration
    using Creator =
            std::function<Dialog*(std::shared_ptr<Env>, const std::string&, const qualla::json&)>;
    QUALLA_API static void __register(const std::string& type, Creator func);

    // Create Dialog instance
    QUALLA_API static std::unique_ptr<Dialog> create(
            std::shared_ptr<Env> env,
            const std::string&   name,
            const qualla::json&  conf = {}
    );
    QUALLA_API static std::unique_ptr<Dialog> create(
            std::shared_ptr<Env> env,
            const std::string&   name,
            std::istream&        json_stream
    );
    QUALLA_API static std::unique_ptr<Dialog> create(
            std::shared_ptr<Env>         env,
            const std::string&           name,
            const std::filesystem::path& json_path
    );

  protected:
    const std::string _type;

    std::shared_ptr<Env>       _env; // Shared between multipl dialogs
    std::unique_ptr<Context>   _ctx;
    std::unique_ptr<Tokenizer> _tokenizer;

    std::unordered_map<std::string, std::unique_ptr<Sampler>>
                                                             _sampler; // samplers (indexed by role)
    std::unordered_map<std::string, std::unique_ptr<Engine>> _engine;  // engines  (indexed by role)

    std::vector<std::string> _inst_tags;
    std::vector<std::string> _sys_tags;
    std::string              _sys_prompt;

    KPIs     _kpis;
    uint32_t _n_queries{0};   // number of queries
    uint32_t _n_past{0};      // number of tokens cached
    uint32_t _n_prompt{0};    // number of prompt tokens    (last query)
    uint32_t _n_generated{0}; // number of generated tokens (last query)
    int32_t  _last_tok{-1};   // last generated token

    // Process dialog input tokens
    virtual bool process(std::vector<int32_t>& tokens, Callback callback) = 0;

    // Set error/failed state, and dispatch the callback
    bool abort(const std::string& err, Callback& callback) {
        State::error(err);
        callback("", Sentence::ABORT);
        return false;
    }
};

} // namespace qualla

#endif // QUALLA_DIALOG_HPP

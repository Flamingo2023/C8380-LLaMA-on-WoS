// Copyright 2023 Qualcomm Technologies, Inc. All rights reserved.
// Confidential & Proprietary - Qualcomm Technologies, Inc. ("QTI")

#ifndef QUALLA_ENGINE_HPP
#define QUALLA_ENGINE_HPP

#include <qualla/detail/exports.h>
#include <qualla/detail/kpi.hpp>
#include <qualla/context.hpp>

#include <memory>
#include <string>
#include <vector>
#include <functional>
#include <iostream>

namespace qualla {

class Engine : public State {
  public:
    QUALLA_API Engine(Context& ctx, const std::string& type, const qualla::json& conf = {});
    QUALLA_API virtual ~Engine();

    // Engine features
    struct Feature {
        enum Flags {
            OUTPUT_LOGITS     = (1UL << 0), // Output of this engine is Logits
            OUTPUT_EMBEDDINGS = (1UL << 1), // Output of this engine is Embeddings
            SAVE_RESTORE      = (1UL << 2), // Save and restore support
            DYNAMIC_LOAD      = (1UL << 3)  // Dynamic loading / unloading support
        };
    };

    // Get engine feature mask
    uint32_t features() const { return _features; }
    bool     supports(uint32_t flag) const { return _features & flag; }

    // Get engine type
    const std::string& type() const { return _type; }

    // Get engine role
    const std::string& role() const { return _role; }

    // Process input tokens and generate output.
    // The output is Logits for LLM and Embeddings for Sentence Transformers.
    // Returns the number of tokens in the output.
    QUALLA_API virtual size_t process(
            const std::vector<int32_t>& tokens,
            std::vector<float>&         output,
            bool                        output_all = false
    ) = 0;

    // Process input tokens without returning the output.
    // Returns the number of tokens in the output.
    QUALLA_API virtual size_t process(const std::vector<int32_t>& tokens);

    // Synchronize the state of the context & engine.
    // n_past is the number of tokens in the KV Cache.
    QUALLA_API virtual bool updateKV(size_t n_past);

    QUALLA_API virtual bool   save(const std::string& name);
    QUALLA_API virtual size_t restore(const std::string& name);
    QUALLA_API virtual void   reset();

    // Load/unload all model/state data
    QUALLA_API virtual bool load();
    QUALLA_API virtual bool unload();

    // Engine KPIs
    struct KPIs {
        Kpi load;
        Kpi process;
        Kpi update_kv;
        Kpi unload;

        KPIs() { reset(); }

        QUALLA_API void reset(); // reset to initial state
        QUALLA_API std::string dump(std::string_view sep = " ")
                const; // dump KPIs as formated string
    };

    // Get Engine KPIs
    KPIs& kpis() { return _kpis; }

    // Get Engine context
    Context& context() { return _ctx; }

    // List available engines
    QUALLA_API static std::vector<std::string> list();

    // Create Engine instance
    QUALLA_API static std::unique_ptr<Engine> create(Context& ctx, std::istream& json_stream);
    QUALLA_API static std::unique_ptr<Engine> create(Context& ctx, const std::string& json_str);
    QUALLA_API static std::unique_ptr<Engine> create(Context& ctx, const qualla::json& conf = {});

    // Engine registration
    using Creator = std::function<Engine*(Context&, const qualla::json&)>;
    QUALLA_API static void __register(const std::string& type, Creator func);

  protected:
    std::string _type;        // engine type
    std::string _role;        // engine role
    Context&    _ctx;         // reference to the context
    Env&        _env;         // reference to the env
    KPIs        _kpis;        // our KPIs
    uint32_t    _features{0}; // engine feature mask
};

} // namespace qualla

#endif // QUALLA_ENGINE_HPP

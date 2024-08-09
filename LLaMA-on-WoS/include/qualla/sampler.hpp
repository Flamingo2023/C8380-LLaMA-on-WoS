// Copyright 2023 Qualcomm Technologies, Inc. All rights reserved.
// Confidential & Proprietary - Qualcomm Technologies, Inc. ("QTI")

#ifndef QUALLA_SAMPLER_HPP
#define QUALLA_SAMPLER_HPP

#include <qualla/detail/exports.h>
#include <qualla/context.hpp>

#include <memory>
#include <string>
#include <vector>
#include <random>

#if __cplusplus >= 202002L
    #include <span>
#endif

namespace qualla {

class Sampler : public State {
  public:
    QUALLA_API Sampler(Context& ctx, const std::string& type, const qualla::json& conf);
    QUALLA_API virtual ~Sampler();

#if __cplusplus >= 202002L
    // Sample a single token from logits
    QUALLA_API virtual int32_t process(std::span<const float> logits) = 0;

    // Sample a single token and output probabilities
    // Probs are appended to the existing vector
    QUALLA_API virtual int32_t process(
            std::span<const float> logits,
            std::vector<float>&    probs,
            bool                   out_tok = true
    );
#endif

    // Sample a single token from logits
    QUALLA_API int32_t process(const std::vector<float>& logits);

    // Sample a single token and output probabilities
    // Probs are appended to the existing vector
    QUALLA_API int32_t
    process(const std::vector<float>& logits, std::vector<float>& probs, bool out_tok = true);

    QUALLA_API virtual bool save(const std::string& name);
    QUALLA_API virtual bool restore(const std::string& name);
    QUALLA_API virtual void reset();

    // Get sampler type
    const std::string& type() const { return _type; }

    // Get sampler role
    const std::string& role() const { return _role; }

    // Get reference to the random number generator
    std::mt19937& rng() { return _rng; }

    // Get sampler params
    int32_t seed() const { return _seed; }
    float   temp() const { return _temp; }
    size_t  top_k() const { return _top_k; }
    float   top_p() const { return _top_p; }
    bool    greedy() const { return _greedy; }
    bool    gumbel() const { return _gumbel; }

    // Set sampler params
    void temp(float t) { _temp = t; }
    void top_k(size_t k) { _top_k = k; }
    void top_p(float p) { _top_p = p; }

    // List available samplers
    QUALLA_API static std::vector<std::string> list();

    // Create Sampler instance
    QUALLA_API static std::unique_ptr<Sampler> create(Context& ctx, std::istream& json_stream);
    QUALLA_API static std::unique_ptr<Sampler> create(Context& ctx, const std::string& json_str);
    QUALLA_API static std::unique_ptr<Sampler> create(Context& ctx, const qualla::json& conf = {});

    // Sampler registration
    using Creator = std::function<Sampler*(Context&, const qualla::json&)>;
    QUALLA_API static void __register(const std::string& type, Creator func);

  protected:
    std::string  _type; // sampler type
    std::string  _role; // sampler role (primary, secondary, ...)
    Context&     _ctx;  // reference to the context
    Env&         _env;  // reference to the environment
    std::mt19937 _rng;

    int32_t _seed{-1};
    float   _temp{0.1};
    size_t  _top_k{0};
    float   _top_p{0.8};
    bool    _greedy{false};
    bool    _gumbel{false};
};

} // namespace qualla

#endif // QUALLA_SAMPLER_HPP

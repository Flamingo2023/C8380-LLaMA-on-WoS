// Copyright 2023 Qualcomm Technologies, Inc. All rights reserved.
// Confidential & Proprietary - Qualcomm Technologies, Inc. ("QTI")
//
// Based on Tokenizer.cpp from MLC-LLM project.
// Copyright (c) 2023 by Contributors

#ifndef QUALLA_TOKENIZER_HPP
#define QUALLA_TOKENIZER_HPP

#include <qualla/detail/exports.h>
#include <qualla/context.hpp>

#include <memory>
#include <string>
#include <sstream>
#include <vector>
#include <filesystem>

namespace qualla {

/*!
 * \brief a universal tokenizer that loads
 *  either HF's tokenizer or sentence piece,
 *  depending on the constructor
 */
class Tokenizer : public State {
  public:
    /*! \brief virtual destructor */
    virtual ~Tokenizer() {}

    /*!
     * \brief Encode text into ids.
     * \param text The input text.
     * \returns The encoded token ids.
     */
    QUALLA_API virtual std::vector<int32_t> encode(const std::string& text) = 0;

    // Encode text directly into token vector appending to existing tokens.
    // Return number of appended tokens.
    QUALLA_API virtual size_t encode(const std::string& text, std::vector<int32_t>& tokens) = 0;

    /*!
     * \brief Decode token ids into text.
     * \param text The token ids.
     * \returns The decoded text.
     */
    QUALLA_API virtual std::string decode(const std::vector<int32_t>& ids) = 0;

    //---------------------------------------------------
    // Factory functions from byte-blobs
    // These factory function takes in in-memory blobs
    // so the library can be independent from filesystem
    //---------------------------------------------------
    /*!
     * \brief Create HF tokenizer from a single in-memory json blob.
     *
     * \param json_blob The json blob.
     * \return The created tokenzier.
     */
    QUALLA_API static std::unique_ptr<Tokenizer> create(Context& ctx, std::istream& json_stream);
    QUALLA_API static std::unique_ptr<Tokenizer> create(
            Context&                     ctx,
            const std::filesystem::path& json_path
    );
};

} // namespace qualla
#endif // QUALLA_TOKENIZER_HPP

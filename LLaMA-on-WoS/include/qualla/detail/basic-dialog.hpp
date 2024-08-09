//  Copyright 2023 Qualcomm Technologies, Inc. All rights reserved.
//  Confidential & Proprietary - Qualcomm Technologies, Inc. ("QTI")

#ifndef QUALLA_DETAIL_BASIC_DIALOG_HPP
#define QUALLA_DETAIL_BASIC_DIALOG_HPP

#include <memory>
#include <string>
#include <vector>
#include <span>
#include <stdint.h>

#include <qualla/detail/json.hpp>
#include <qualla/env.hpp>
#include <qualla/dialog.hpp>

namespace qualla {

class BasicDialog : public Dialog {
  public:
    BasicDialog(std::shared_ptr<Env> env, const std::string& name, const json& conf)
        : Dialog(env, name, conf) {}

    virtual bool process(std::vector<int32_t>& tokens, Dialog::Callback callback) override;
};

} // namespace qualla

#endif // QUALLA_DETAIL_BASIC_DIALOG_HPP

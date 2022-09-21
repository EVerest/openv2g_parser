// SPDX-License-Identifier: Apache-2.0
// Copyright 2022 - 2022 Pionix GmbH and Contributors to EVerest
#include "messages.hpp"

#include <fmt/core.h>

#include "helpers.hpp"

std::string parse_session_setup_req(const iso1SessionSetupReqType& msg){
    return fmt::format("EVCCID: {}", bytes_to_hex(msg.EVCCID.bytes, msg.EVCCID.bytesLen));
}

std::string parse_session_setup_res(const iso1SessionSetupResType& msg) {
    std::string text = fmt::format("EVSEID: {}", std::string(msg.EVSEID.characters, msg.EVSEID.charactersLen));
    if (msg.EVSETimeStamp_isUsed) {
        text += fmt::format("\nTimestamp: {}", msg.EVSETimeStamp);
    }
    text += fmt::format("\nResponse code: {}", evse_status_code_to_string(msg.ResponseCode));
    return text;
}
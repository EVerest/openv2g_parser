// SPDX-License-Identifier: Apache-2.0
// Copyright 2022 - 2022 Pionix GmbH and Contributors to EVerest
#ifndef OPENV2G_PARSER_V2G_HPP
#define OPENV2G_PARSER_V2G_HPP

#include <string>
#include <vector>

struct v2g_message {
    std::string session_id;
    std::string notification;
    std::string signature;
    std::string type;
    std::string content;
};

v2g_message parse_v2g_message(const uint8_t* buffer, size_t len);

#endif // OPENV2G_PARSER_V2G_HPP
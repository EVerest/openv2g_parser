// SPDX-License-Identifier: Apache-2.0
// Copyright 2022 - 2022 Pionix GmbH and Contributors to EVerest
#ifndef OPENV2G_PARSER_HELPERS_HPP
#define OPENV2G_PARSER_HELPERS_HPP

#include <string>

std::string bytes_to_hex(const uint8_t* data, size_t data_len);

const char* fault_code_to_string(int code);
const char* evse_status_code_to_string(int code);

#endif // OPENV2G_PARSER_HELPERS_HPP
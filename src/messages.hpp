// SPDX-License-Identifier: Apache-2.0
// Copyright 2022 - 2022 Pionix GmbH and Contributors to EVerest
#ifndef OPENV2G_PARSER_MESSAGES_HPP
#define OPENV2G_PARSER_MESSAGES_HPP

#include <string>

#include <iso1EXIDatatypes.h>

std::string parse_session_setup_req(const iso1SessionSetupReqType& msg);

std::string parse_session_setup_res(const iso1SessionSetupResType& msg);

#endif // OPENV2G_PARSER_MESSAGES_HPP
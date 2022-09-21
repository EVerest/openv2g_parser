// SPDX-License-Identifier: Apache-2.0
// Copyright 2022 - 2022 Pionix GmbH and Contributors to EVerest
#include "helpers.hpp"

#include <fmt/format.h>

#include <iso1EXIDatatypes.h>

std::string bytes_to_hex(const uint8_t* data, size_t data_len) {
    std::string text;
    text.reserve(data_len * 2);
    for (int i = 0; i < data_len; ++i) {
        fmt::format_to(std::back_inserter(text), "{:02X}", data[i]);
    }

    return text;
}

const char* fault_code_to_string(int code) {
    switch (code) {
    case 0:
        return "ParsingError";
    case 1:
        return "NoTLSRootCertificatAvailable";
    case 2:
        return "UnknownError";
    default:
        return "Invalid fault code (bug?)";
    }
}

const char* evse_status_code_to_string(int code) {
    switch (code) {
    case 0:
        return "EVSE_NotReady";
    case 1:
        return "EVSE_Ready";
    case 2:
        return "EVSE_Shutdown";
    case 3:
        return "EVSE_UtilityInterruptEvent";
    case 4:
        return "EVSE_IsolationMonitoringActive";
    case 5:
        return "EVSE_EmergencyShutdown";
    case 6:
        return "EVSE_Malfunction";
    case 7:
        return "Reserved_8";
    case 8:
        return "Reserved_9";
    case 9:
        return "Reserved_A";
    case 10:
        return "Reserved_B";
    case 11:
        return "Reserved_C";
    default:
        return "Invalid EVSE status code (bug?)";
    }
}
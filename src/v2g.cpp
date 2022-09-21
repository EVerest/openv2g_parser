// SPDX-License-Identifier: Apache-2.0
// Copyright 2022 - 2022 Pionix GmbH and Contributors to EVerest
#include "v2g.hpp"

#include <fmt/format.h>

#include <iso1EXIDatatypes.h>
#include <iso1EXIDatatypesDecoder.h>
#include <v2gtp.h>

#include "helpers.hpp"
#include "messages.hpp"

static void decode_exi_buffer(const uint8_t* buffer, size_t len, struct iso1EXIDocument& exi) {
    bitstream_t input_stream;
    size_t stream_pos = 0;
    uint32_t payload_length;
    input_stream.data = const_cast<uint8_t*>(buffer);
    input_stream.pos = &stream_pos;
    input_stream.size = len;

    if (read_v2gtpHeader(input_stream.data, &payload_length)) {
        throw std::runtime_error("Invalid header");
    }
    *input_stream.pos += V2GTP_HEADER_LENGTH;

    auto errn = decode_iso1ExiDocument(&input_stream, &exi);
    if (errn) {
        throw std::runtime_error(fmt::format("Could not decode exi document (error code: {})", errn));
    }
}

static std::string parse_v2g_header_notification(const iso1NotificationType& ntf) {
    std::string text = fault_code_to_string(ntf.FaultCode);

    if (ntf.FaultMsg_isUsed) {
        // FIXME: how to convert exi_string_character_t to char?
        // lua_pushlstring(L, ntf->FaultMsg.characters, ntf->FaultMsg.charactersLen);
        text.append(fmt::format("\nFault message: {}", "FIXME - Fault message parsing not implemented"));
    }

    return text;
}

static void parse_v2g_header(v2g_message& msg, const struct iso1MessageHeaderType& hdr) {
    if (hdr.Notification_isUsed) {
        msg.notification = parse_v2g_header_notification(hdr.Notification);
    }

    if (hdr.Signature_isUsed) {
        msg.signature = "FIXME - Signature parsing not implemented";
    }

    msg.session_id = bytes_to_hex(hdr.SessionID.bytes, hdr.SessionID.bytesLen);
}

void parse_v2g_body(v2g_message& msg, const struct iso1BodyType& body) {
    if (body.AuthorizationReq_isUsed) {
        msg.type = "AuthorizationReq";
        msg.content = "Decoding for this message_type not yet implemented";
    } else if (body.AuthorizationRes_isUsed) {
        msg.type = "AuthorizationRes";
        msg.content = "Decoding for this message_type not yet implemented";
    } else if (body.CableCheckReq_isUsed) {
        msg.type = "CableCheckReq";
        msg.content = "Decoding for this message_type not yet implemented";
    } else if (body.CableCheckRes_isUsed) {
        msg.type = "CableCheckRes";
        msg.content = "Decoding for this message_type not yet implemented";
    } else if (body.CertificateInstallationReq_isUsed) {
        msg.type = "CertificateInstallationReq";
        msg.content = "Decoding for this message_type not yet implemented";
    } else if (body.CertificateInstallationRes_isUsed) {
        msg.type = "CertificateInstallationRes";
        msg.content = "Decoding for this message_type not yet implemented";
    } else if (body.CertificateUpdateReq_isUsed) {
        msg.type = "CertificateUpdateReq";
        msg.content = "Decoding for this message_type not yet implemented";
    } else if (body.CertificateUpdateRes_isUsed) {
        msg.type = "CertificateUpdateRes";
        msg.content = "Decoding for this message_type not yet implemented";
    } else if (body.ChargeParameterDiscoveryReq_isUsed) {
        msg.type = "ChargeParameterDiscoveryReq";
        msg.content = "Decoding for this message_type not yet implemented";
    } else if (body.ChargeParameterDiscoveryRes_isUsed) {
        msg.type = "ChargeParameterDiscoveryRes";
        msg.content = "Decoding for this message_type not yet implemented";
    } else if (body.ChargingStatusReq_isUsed) {
        msg.type = "ChargingStatusReq";
        msg.content = "Decoding for this message_type not yet implemented";
    } else if (body.ChargingStatusRes_isUsed) {
        msg.type = "ChargingStatusRes";
        msg.content = "Decoding for this message_type not yet implemented";
    } else if (body.CurrentDemandReq_isUsed) {
        msg.type = "CurrentDemandReq";
        msg.content = "Decoding for this message_type not yet implemented";
    } else if (body.CurrentDemandRes_isUsed) {
        msg.type = "CurrentDemandRes";
        msg.content = "Decoding for this message_type not yet implemented";
    } else if (body.MeteringReceiptReq_isUsed) {
        msg.type = "MeteringReceiptReq";
        msg.content = "Decoding for this message_type not yet implemented";
    } else if (body.MeteringReceiptRes_isUsed) {
        msg.type = "MeteringReceiptRes";
        msg.content = "Decoding for this message_type not yet implemented";
    } else if (body.PaymentDetailsReq_isUsed) {
        msg.type = "PaymentDetailsReq";
        msg.content = "Decoding for this message_type not yet implemented";
    } else if (body.PaymentDetailsRes_isUsed) {
        msg.type = "PaymentDetailsRes";
        msg.content = "Decoding for this message_type not yet implemented";
    } else if (body.PaymentServiceSelectionReq_isUsed) {
        msg.type = "PaymentServiceSelectionReq";
        msg.content = "Decoding for this message_type not yet implemented";
    } else if (body.PaymentServiceSelectionRes_isUsed) {
        msg.type = "PaymentServiceSelectionRes";
        msg.content = "Decoding for this message_type not yet implemented";
    } else if (body.PowerDeliveryReq_isUsed) {
        msg.type = "PowerDeliveryReq";
        msg.content = "Decoding for this message_type not yet implemented";
    } else if (body.PowerDeliveryRes_isUsed) {
        msg.type = "PowerDeliveryRes";
        msg.content = "Decoding for this message_type not yet implemented";
    } else if (body.PreChargeReq_isUsed) {
        msg.type = "PreChargeReq";
        msg.content = "Decoding for this message_type not yet implemented";
    } else if (body.PreChargeRes_isUsed) {
        msg.type = "PreChargeRes";
        msg.content = "Decoding for this message_type not yet implemented";
    } else if (body.ServiceDetailReq_isUsed) {
        msg.type = "ServiceDetailReq";
        msg.content = "Decoding for this message_type not yet implemented";
    } else if (body.ServiceDetailRes_isUsed) {
        msg.type = "ServiceDetailRes";
        msg.content = "Decoding for this message_type not yet implemented";
    } else if (body.ServiceDiscoveryReq_isUsed) {
        msg.type = "ServiceDiscoveryReq";
        msg.content = "Decoding for this message_type not yet implemented";
    } else if (body.ServiceDiscoveryRes_isUsed) {
        msg.type = "ServiceDiscoveryRes";
        msg.content = "Decoding for this message_type not yet implemented";
    } else if (body.SessionSetupReq_isUsed) {
        msg.type = "SessionSetupReq";
        msg.content = parse_session_setup_req(body.SessionSetupReq);
    } else if (body.SessionSetupRes_isUsed) {
        msg.type = "SessionSetupRes";
        msg.content = parse_session_setup_res(body.SessionSetupRes);
    } else if (body.SessionStopReq_isUsed) {
        msg.type = "SessionStopReq";
        msg.content = "Decoding for this message_type not yet implemented";
    } else if (body.SessionStopRes_isUsed) {
        msg.type = "SessionStopRes";
        msg.content = "Decoding for this message_type not yet implemented";
    } else if (body.WeldingDetectionReq_isUsed) {
        msg.type = "WeldingDetectionReq";
        msg.content = "Decoding for this message_type not yet implemented";
    } else if (body.WeldingDetectionRes_isUsed) {
        msg.type = "WeldingDetectionRes";
        msg.content = "Decoding for this message_type not yet implemented";
    } else if (body.BodyElement_isUsed) {
        msg.type = "BodyElement";
        msg.content = "Decoding for this message_type not yet implemented";
    } else {
        msg.type = "Invalid message type (bug?)";
        msg.content = "n/a";
    }
}

v2g_message parse_v2g_message(const uint8_t* buffer, size_t len) {
    iso1EXIDocument exi;

    decode_exi_buffer(buffer, len, exi);

    if (!exi.V2G_Message_isUsed) {
        throw std::runtime_error("Unexpected EXI content, did expect a V2G_Message");
    }

    v2g_message msg;
    parse_v2g_header(msg, exi.V2G_Message.Header);
    parse_v2g_body(msg, exi.V2G_Message.Body);

    return msg;
}

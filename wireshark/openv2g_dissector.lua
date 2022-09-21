-- SPDX-License-Identifier: GPL-2.0
-- Copyright 2020 - 2022 Pionix GmbH and Contributors to EVerest
local v2g_native = require("openv2g_parser_lua")

local v2g = Proto("v2g","OpenV2G protocol")

local ef_len_mismatch = ProtoExpert.new("v2g.len_mismatch.expert", "V2G message length mismatch",
    expert.group.MALFORMED, expert.severity.ERROR)

local ef_parse_error = ProtoExpert.new("v2g.parse_error.expert", "V2G message parse error",
    expert.group.RESPONSE_CODE, expert.severity.ERROR)

v2g.experts = { ef_len_mismatch, ef_parse_error }

local pf_msg_type = ProtoField.new("MessageType", "v2g.msg_type", ftypes.STRING)
local pf_session_id = ProtoField.new("SessionID", "v2g.session_id", ftypes.STRING)
local pf_msg_content = ProtoField.new("Decoded", "v2g.msg_content", ftypes.STRING)

v2g.fields = { pf_msg_type, pf_session_id, pf_msg_content }

local V2G_HEADER_LEN = 8

function v2g.dissector(tvbuf,pktinfo,root)
    pktinfo.cols.protocol:set("OpenV2G")

    -- header has been checked already
    local pktlen = tvbuf:reported_length_remaining()

    local tree = root:add(v2g, tvbuf:range(0,pktlen))

    local v2g_payload_len = tvbuf:range(4, 4)
    if V2G_HEADER_LEN + v2g_payload_len:uint() ~= pktlen then
        tree:add_proto_expert_info(ef_len_mismatch)
        return
    end

    local parsed_exi = v2g_native.parse_exi(tvbuf:raw())

    if parsed_exi.error then
        tree:add_proto_expert_info(ef_parse_error, parsed_exi.error)
        return;
    end

    if parsed_exi.header then
        tree:add(pf_session_id, parsed_exi.header.session_id)
    end

    if parsed_exi.body then
        pktinfo.cols.info:set(parsed_exi.body.type)
        local msg_tree = tree:add(pf_msg_type, parsed_exi.body.type)
        msg_tree:add(pf_msg_content, parsed_exi.body.content):set_text(parsed_exi.body.content)
    end

    return
end

local function v2g_heuristic_check(tvbuf,pktinfo,root)

    if tvbuf:len() < V2G_HEADER_LEN then
        print("v2g_header too smaller than ",V2G_HEADER_LEN)
        return false
    end

    local v2g_version = tvbuf:range(0, 2)
    if v2g_version:uint() ~= 0x1fe then
        print("v2g_version wrong")
        return false
    end

    local v2g_exi_type = tvbuf:range(2, 2)
    if v2g_exi_type:uint() ~= 0x8001 then
        print("v2g_exi_type wrong")
        return false
    end

    -- make our dissector sticky for this packet
    pktinfo.conversation = v2g

    return true
end

v2g:register_heuristic("tcp", v2g_heuristic_check)
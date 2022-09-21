// SPDX-License-Identifier: Apache-2.0
// Copyright 2022 - 2022 Pionix GmbH and Contributors to EVerest
#include <lauxlib.h>
#include <lua.h>

#include <exception>

#include <v2g.hpp>

static int parse_exi(lua_State* L) {
    size_t data_len;
    auto data = reinterpret_cast<const uint8_t*>(luaL_checklstring(L, 1, &data_len));

    // re-turntable
    lua_newtable(L);

    try {
        const v2g_message msg = parse_v2g_message(data, data_len);

        // add header table
        lua_newtable(L);

        // add session_id field
        lua_pushstring(L, msg.session_id.c_str());
        lua_setfield(L, -2, "session_id");

        // add notification field if available
        if (!msg.notification.empty()) {
            lua_pushstring(L, msg.notification.c_str());
            lua_setfield(L, -2, "notification");
        }

        // add signature field if available
        if (!msg.signature.empty()) {
            lua_pushstring(L, msg.signature.c_str());
            lua_setfield(L, -2, "signature");
        }

        // finish header table
        lua_setfield(L, -2, "header");

        // add body table
        lua_newtable(L);

        // set message_type field
        lua_pushstring(L, msg.type.c_str());
        lua_setfield(L, -2, "type");

        // set message_content field if available
        if (!msg.content.empty()) {
            lua_pushstring(L, msg.content.c_str());
            lua_setfield(L, -2, "content");
        }

        // finish body table
        lua_setfield(L, -2, "body");

    } catch (const std::exception& e) {
        lua_pushstring(L, e.what());
        lua_setfield(L, -2, "error");
    }

    return 1;
}

static const struct luaL_Reg parser_lib[] = {{"parse_exi", parse_exi}, {0, 0}};

extern "C" {
int luaopen_openv2g_parser_lua(lua_State* L) {
    luaL_newlib(L, parser_lib);
    return 1;
}
}

openv2g_parser
==============

This repository includes an unfinished wrapper library called *openv2g_parser*,
that is build around the Siemens openv2g library.  This wrapper library in turn
is used by the wireshark plugin to decode V2G messages.

setup
-----

In order to build this project, you need to have the lua-dev packages installed
(only tested against Lua 5.2)::

    # cmake -S . -B build
    # cd build
    # make
    # wireshark -X lua_script:../wireshark/openv2g_dissector.lua /path/to/pcap_file



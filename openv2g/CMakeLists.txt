find_package(Patch REQUIRED)

FetchContent_Declare(openv2g
  GIT_REPOSITORY https://github.com/chargebyte/openv2g.git
  GIT_TAG 87591ab3b7172d9661c118a318c60a0ce2be240e
)
FetchContent_MakeAvailable(openv2g)

# FIXME (aw): this is still quite dirty
execute_process(
    COMMAND
        ${Patch_EXECUTABLE} -p1 -s -i "${CMAKE_CURRENT_SOURCE_DIR}/string_repr.patch"
    WORKING_DIRECTORY
        ${openv2g_SOURCE_DIR}
    OUTPUT_QUIET
)

add_library(openv2g_codec)

set(OPENV2G_SRC "${openv2g_SOURCE_DIR}/src")

# appHandshake
target_include_directories(openv2g_codec
    PUBLIC
        "${OPENV2G_SRC}/appHandshake"
)

target_sources(openv2g_codec
    PRIVATE
        ${OPENV2G_SRC}/appHandshake/appHandEXIDatatypes.c
        ${OPENV2G_SRC}/appHandshake/appHandEXIDatatypesDecoder.c
        ${OPENV2G_SRC}/appHandshake/appHandEXIDatatypesEncoder.c
)

# codec
target_include_directories(openv2g_codec
    PUBLIC
        "${OPENV2G_SRC}/codec"
)

target_sources(openv2g_codec
    PRIVATE
        ${OPENV2G_SRC}/codec/BitInputStream.c
        ${OPENV2G_SRC}/codec/BitOutputStream.c
        ${OPENV2G_SRC}/codec/ByteStream.c
        ${OPENV2G_SRC}/codec/DecoderChannel.c
        ${OPENV2G_SRC}/codec/EncoderChannel.c
        ${OPENV2G_SRC}/codec/EXIHeaderDecoder.c
        ${OPENV2G_SRC}/codec/EXIHeaderEncoder.c
        ${OPENV2G_SRC}/codec/MethodsBag.c
)

# din
target_include_directories(openv2g_codec
    PUBLIC
        "${OPENV2G_SRC}/din"
)

target_sources(openv2g_codec
    PRIVATE
        ${OPENV2G_SRC}/din/dinEXIDatatypes.c
        ${OPENV2G_SRC}/din/dinEXIDatatypesDecoder.c
        ${OPENV2G_SRC}/din/dinEXIDatatypesEncoder.c
)

# xmldsig
target_include_directories(openv2g_codec
    PUBLIC
        "${OPENV2G_SRC}/xmldsig"
)

target_sources(openv2g_codec
    PRIVATE
        ${OPENV2G_SRC}/xmldsig/xmldsigEXIDatatypes.c
        ${OPENV2G_SRC}/xmldsig/xmldsigEXIDatatypesDecoder.c
        ${OPENV2G_SRC}/xmldsig/xmldsigEXIDatatypesEncoder.c
)

# iso1
target_include_directories(openv2g_codec
    PUBLIC
        "${OPENV2G_SRC}/iso1"
)

target_sources(openv2g_codec
    PRIVATE
        ${OPENV2G_SRC}/iso1/iso1EXIDatatypes.c
        ${OPENV2G_SRC}/iso1/iso1EXIDatatypesDecoder.c
        ${OPENV2G_SRC}/iso1/iso1EXIDatatypesEncoder.c
)

# iso2
target_include_directories(openv2g_codec
    PUBLIC
        "${OPENV2G_SRC}/iso2"
)

target_sources(openv2g_codec
    PRIVATE
        ${OPENV2G_SRC}/iso2/iso2EXIDatatypes.c
        ${OPENV2G_SRC}/iso2/iso2EXIDatatypesDecoder.c
        ${OPENV2G_SRC}/iso2/iso2EXIDatatypesEncoder.c
)

# transport
target_include_directories(openv2g_codec
    PUBLIC
        "${OPENV2G_SRC}/transport"
)

target_sources(openv2g_codec
    PRIVATE
        ${OPENV2G_SRC}/transport/v2gtp.c
)

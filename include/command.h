#pragma once

#include <cstdint>

enum class Command : uint8_t {
    BRIGHTNESS = 0x00,
    PATTERN = 0x01,
    BOOTLOADER = 0x02,
    SLEEP = 0x03,
    GET_SLEEP = 0x03,
    ANIMATE = 0x04,
    GET_ANIMATE = 0x04,
    PANIC = 0x05,
    DRAW_BW = 0x06,
    STAGE_COL = 0x07,
    FLUSH_COLS = 0x08,
    SET_TEXT = 0x09,
    // start_game = 0x10,
    // game_ctrl = 0x11,
    // game_status = 0x12,
    SET_COLOR = 0x13,
    DISPLAY_ON = 0x14,
    INVERT_SCREEN = 0x15,
    SET_PX_COL = 0x16,
    FLUSH_FB = 0x17,
    VERSION = 0x20
};
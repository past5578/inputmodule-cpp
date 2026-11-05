#pragma once

#include "inputmodule.h"

#include <cstdint>
#include <span>

enum class PatternId : uint8_t {
    PERCENTAGE,
    GRADIENT,
    DOUBLE_GRADIENT,
    DISPLAY_LOTUS_HORIZONTAL,
    ZIG_ZAG,
    FULL_BRIGHTNESS,
    DISPLAY_PANIC,
    DISPLAY_LOTUS_VERTICAL
};

class LedMatrix : public InputModule {
  public:
    explicit LedMatrix(int fd) : InputModule(fd) {};
    explicit LedMatrix(const char *path = "/dev/ttyACM0") : InputModule(path) {};

    void pattern(PatternId pattern_id);
    void animate(bool state);                 // todo
    bool get_animate();                       // todo
    void draw_bw(std::span<uint8_t> bytes);   // todo
    void stage_col(std::span<uint8_t> bytes); // todo
    void flush_cols();
};
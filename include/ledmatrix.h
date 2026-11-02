#pragma once

#include "inputmodule.h"

enum PatternId {
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
    explicit LedMatrix(const char *path = "/dev/ttyACM0") : InputModule(path) {};

    void pattern(PatternId pattern_id);
};

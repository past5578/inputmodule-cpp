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

/*
 Remaining function wrappers:
 * Brightness
 * Bootloader
 * Sleep
 * GetSleep
 * Animate
 * GetAnimate
 * Panic
 * DrawBW
 * StageCol
 * FlushCols
 * StartGame
 * GameCtrl
 * GameStatus
 * Version
 */

class LedMatrix : public InputModule {
  public:
    explicit LedMatrix(const char *path = "/dev/ttyACM0") : InputModule(path) {};

    void pattern(PatternId pattern_id);
    void animate(bool state);          // todo
    bool get_animate();                // todo
    void draw_bw(uint8_t bytes[39]);   // todo
    void stage_col(uint8_t bytes[35]); // todo
    void flush_cols();
    /*
    * Likely won't implement:
    void start_game(uint8_t game_id);
    void game_control(uint8_t game_control_id);
    */
};

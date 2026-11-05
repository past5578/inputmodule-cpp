#include "ledmatrix.h"

#include <span>

void LedMatrix::pattern(PatternId pattern_id) {
    send_command(Command::PATTERN, static_cast<uint8_t>(pattern_id));
}

void LedMatrix::animate(bool state) {
    send_command(Command::ANIMATE, static_cast<uint8_t>(state));
}

bool LedMatrix::get_animate() {
    return send_query(Command::GET_ANIMATE)[0] != 0U;
}

void LedMatrix::draw_bw(std::span<uint8_t> bytes) {
    send_command(Command::DRAW_BW, bytes);
}

void LedMatrix::stage_col(std::span<uint8_t> bytes) {
    send_command(Command::STAGE_COL, bytes);
}

void LedMatrix::flush_cols() {
    send_command(Command::FLUSH_COLS);
}
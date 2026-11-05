#include "ledmatrix.h"

#include <span>
#include <vector>

void LedMatrix::pattern(PatternId pattern_id) {
    std::vector<uint8_t> parameters = {static_cast<uint8_t>(pattern_id)};

    send_command(Command::PATTERN, parameters);
}

void LedMatrix::animate(bool state) {
    std::array<uint8_t, 1> parameters = {static_cast<uint8_t>(state)};

    send_command(Command::ANIMATE, parameters);
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
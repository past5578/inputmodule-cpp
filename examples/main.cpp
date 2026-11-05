#include <array>

#include "ledmatrix.h"

int main() {
    LedMatrix led;

    constexpr int MAX_BRIGHTNESS = 256;
    constexpr int MAX_COLUMNS = 9;

    for (int b = 0; b < MAX_BRIGHTNESS; b++) {
        for (int col = 0; col < MAX_COLUMNS; col++) {
            std::array<uint8_t, 35> bytes{};
            bytes.fill(b);
            bytes[0] = col;

            led.stage_col(bytes);
        }
        led.flush_cols();
    }
    return 0;
}
#include "ledmatrix.h"

#include <array>

#include <pty.h>

int main() {
    int amaster = -1;
    int aslave = -1;

    openpty(&amaster, &aslave, nullptr, nullptr, nullptr);

    LedMatrix led(aslave);

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
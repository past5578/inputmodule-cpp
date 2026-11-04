#include <format>
#include <iostream>

#include "ledmatrix.h"

int main() {
    LedMatrix led;
    led.pattern(PatternId::GRADIENT);
    led.sleep(true);

    std::array<uint8_t, 3> version = led.version();
    std::cout << std::format("{:08b} {:08b} {:08b}\n", version[0], version[1], version[2]);

    return 0;
}

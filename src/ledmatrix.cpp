#include "ledmatrix.h"

#include <vector>

void LedMatrix::pattern(PatternId pattern_id) {
    std::vector<uint8_t> parameters = {static_cast<uint8_t>(pattern_id)};

    send_command(0x01, parameters);
}

#include "inputmodule.h"

#include <cstdint>
#include <cstring>
#include <format>
#include <stdexcept>

#include <errno.h>
#include <fcntl.h>
#include <termios.h>
#include <unistd.h>

InputModule::InputModule(const char *path) {
    fd = open(path, O_RDWR);

    if (fd == -1)
        throw std::runtime_error(std::format("failed to open {}: {}", path, std::strerror(errno)));

    termios tty;
    if (tcgetattr(fd, &tty) == -1)
        throw std::runtime_error(std::format("failed to get tty attrs: {}", std::strerror(errno)));

    cfmakeraw(&tty);
    cfsetispeed(&tty, B115200);
    cfsetospeed(&tty, B115200);

    if (tcsetattr(fd, 0, &tty) == -1)
        throw std::runtime_error(std::format("failed to set tty attrs: {}", std::strerror(errno)));
}

InputModule::~InputModule() {
    if (fd == -1) {
        return;
    }

    close(fd);
}

constexpr uint8_t MAGIC_BYTES[2] = {0x32, 0xAC};

void InputModule::send_command(uint8_t command_id, std::vector<uint8_t> parameters) {
    std::vector<uint8_t> message = {MAGIC_BYTES[0], MAGIC_BYTES[1], command_id};
    message.insert(message.end(), parameters.begin(), parameters.end());

    if (write(fd, message.data(), message.size()) != (ssize_t)message.size()) {
        throw std::runtime_error(std::format("failed to set tty attrs: {}", std::strerror(errno)));
    }
}

#include "inputmodule.h"

#include <array>
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

std::array<uint8_t, 32> InputModule::send_query(uint8_t command_id,
                                                std::vector<uint8_t> parameters) {
    tcflush(fd, TCIFLUSH);
    send_command(command_id, parameters);

    std::array<uint8_t, 32> buffer{};

    int status = read(fd, buffer.data(), 32);

    if (status == -1) {
        throw std::runtime_error(std::format("failed to read response: {}", std::strerror(errno)));
    } else if (status == 0) {
        throw std::runtime_error("read timed out");
    }

    return buffer;
}

void InputModule::bootloader() { send_command(0x02); };

void InputModule::sleep(bool state) { send_command(0x03, {state}); };

bool InputModule::get_sleep() { return send_query(0x03)[0]; };

void InputModule::panic() { send_command(0x05); };

std::array<uint8_t, 3> InputModule::version() {
    std::array<uint8_t, 3> buffer{};

    std::array<uint8_t, 32> response = send_query(0x20);

    std::copy_n(response.begin(), buffer.size(), buffer.begin());

    return buffer;
};

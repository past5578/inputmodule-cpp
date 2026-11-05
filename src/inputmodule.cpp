#include "inputmodule.h"
#include "command.h"

#include <array>
#include <cerrno>
#include <cstdint>
#include <cstring>
#include <format>
#include <stdexcept>
#include <vector>

#include <fcntl.h>
#include <sys/types.h>
#include <termios.h>
#include <unistd.h>

InputModule::InputModule(const char *path) : fd(open(path, O_RDWR)) {
    if (fd == -1) {
        throw std::runtime_error(std::format("failed to open {}: {}", path, std::strerror(errno)));
    }

    termios tty{};
    if (tcgetattr(fd, &tty) == -1) {
        throw std::runtime_error(std::format("failed to get tty attrs: {}", std::strerror(errno)));
    }

    cfmakeraw(&tty);
    cfsetispeed(&tty, B115200);
    cfsetospeed(&tty, B115200);

    if (tcsetattr(fd, 0, &tty) == -1) {
        throw std::runtime_error(std::format("failed to set tty attrs: {}", std::strerror(errno)));
    }
}

InputModule::~InputModule() {
    if (fd == -1) {
        return;
    }

    close(fd);
}

void InputModule::send_command(Command command, std::span<uint8_t> parameters) {
    std::vector<uint8_t> message{MAGIC_BYTES[0], MAGIC_BYTES[1], static_cast<uint8_t>(command)};
    message.insert(message.end(), parameters.begin(), parameters.end());

    if (write(fd, message.data(), message.size()) != (ssize_t)message.size()) {
        throw std::runtime_error(std::format("failed to set tty attrs: {}", std::strerror(errno)));
    }
}

void InputModule::send_command(Command command, uint8_t parameter) {
    std::vector<uint8_t> message{MAGIC_BYTES[0], MAGIC_BYTES[1], static_cast<uint8_t>(command)};
    message.insert(message.end(), parameter);

    if (write(fd, message.data(), message.size()) != (ssize_t)message.size()) {
        throw std::runtime_error(std::format("failed to set tty attrs: {}", std::strerror(errno)));
    }
}

query_response InputModule::send_query(Command command, std::span<uint8_t> parameters) {
    tcflush(fd, TCIFLUSH);
    send_command(command, parameters);

    query_response buffer{};

    ssize_t status = read(fd, buffer.data(), RETURN_SIZE);

    if (status == -1) {
        throw std::runtime_error(std::format("failed to read response: {}", std::strerror(errno)));
    }
    if (status == 0) {
        throw std::runtime_error("read timed out");
    }

    return buffer;
}

void InputModule::bootloader() {
    send_command(Command::BOOTLOADER);
};

void InputModule::sleep(bool state) {
    send_command(Command::SLEEP, static_cast<uint8_t>(state));
}

bool InputModule::get_sleep() {
    return send_query(Command::GET_SLEEP)[0] != 0U;
};

void InputModule::panic() {
    send_command(Command::PANIC);
};

/*
++-- Major version
|        +-- Minor version
|        |   +-- Patch version
|        |   |           +-- 1 if is pre-release,
|        |   |           |   0 otherwise
MMMMMMMM mmmmPPPP 0000000p-- Major version
*/

Version InputModule::version() {
    query_response response = send_query(Command::VERSION);

    auto major_version = response[0];
    auto minor_version = static_cast<uint8_t>(response[1] >> 4);
    auto patch_version =
        static_cast<uint8_t>(response[1] & 0x0F); // NOLINT(cppcoreguidelines-avoid-magic-numbers)
    bool is_prerelease = response[2] == 1;

    return Version{.major_version = major_version,
                   .minor_version = minor_version,
                   .patch_version = patch_version,
                   .is_prerelease = is_prerelease};
}
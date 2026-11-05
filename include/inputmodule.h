#pragma once

#include "command.h"

#include <array>
#include <cstddef>
#include <cstdint>
#include <span>

inline constexpr std::array<uint8_t, 2> MAGIC_BYTES{0x32, 0xAC};

inline constexpr size_t RETURN_SIZE = 32;
using query_response = std::array<uint8_t, RETURN_SIZE>;

struct Version {
    int major_version;
    int minor_version;
    int patch_version;
    bool is_prerelease;
};

class InputModule {
  public:
    explicit InputModule(const char *path);
    ~InputModule();

    void send_command(Command command, std::span<uint8_t> parameters = {}) const;
    [[nodiscard]] query_response send_query(Command command,
                                            std::span<uint8_t> parameters = {}) const;

    void bootloader() const;
    void sleep(bool state) const;
    [[nodiscard]] bool get_sleep() const;
    void panic() const;
    [[nodiscard]] Version version() const;

  private:
    int fd = -1;
};
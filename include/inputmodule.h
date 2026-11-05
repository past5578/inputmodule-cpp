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

    // TODO: implement these maybe?
    InputModule(const InputModule &other) = delete;
    InputModule &operator=(const InputModule &other) = delete;
    InputModule(InputModule &&other) noexcept = delete;
    InputModule &operator=(InputModule &&other) noexcept = delete;

    void send_command(Command command, std::span<uint8_t> parameters = {});
    [[nodiscard]] query_response send_query(Command command, std::span<uint8_t> parameters = {});

    void bootloader();
    void sleep(bool state);
    [[nodiscard]] bool get_sleep();
    void panic();
    [[nodiscard]] Version version();

  private:
    int fd = -1;
};
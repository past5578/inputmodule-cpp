#pragma once

#include <array>
#include <cstdint>
#include <vector>

class InputModule {
  public:
    explicit InputModule(const char *path);
    ~InputModule();

    void send_command(uint8_t command_id, std::vector<uint8_t> parameters = {});
    std::array<uint8_t, 32> send_query(uint8_t command_id, std::vector<uint8_t> parameters = {});

    void bootloader();
    void sleep(bool state);
    bool get_sleep();
    void panic();
    std::array<uint8_t, 3> version();

  private:
    int fd = -1;
};

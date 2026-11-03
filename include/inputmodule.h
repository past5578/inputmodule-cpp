#pragma once

#include <cstdint>
#include <vector>

class InputModule {
  public:
    explicit InputModule(const char *path);
    ~InputModule();

    void send_command(uint8_t command_id, std::vector<uint8_t> parameters = {});

    void bootloader();
    void sleep(bool state);
    bool get_sleep();
    void panic();
    uint8_t version();

  private:
    int fd = -1;
};

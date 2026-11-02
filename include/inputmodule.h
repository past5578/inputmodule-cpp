#pragma once

#include <cstdint>
#include <vector>

class InputModule {
  public:
    explicit InputModule(const char *path);
    ~InputModule();

    void send_command(uint8_t command_id, std::vector<uint8_t> parameters = {});

  private:
    int fd = -1;
};

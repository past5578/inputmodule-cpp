#include <cerrno>
#include <cstdint>
#include <cstring>
#include <iostream>
#include <vector>

#include <fcntl.h>
#include <termios.h>
#include <unistd.h>

constexpr uint8_t MAGIC_BYTES[2] = {0x32, 0xAC};

class LedMatrix {
  public:
    int fd;

    LedMatrix(const char *tty_path) {
        fd = get_tty_fd(tty_path);

        if (fd == -1) {
            std::cerr << "get_tty_fd() failed\n";
        }

        initialize_tty(fd);
    }

    ~LedMatrix() {
        if (fd >= 0)
            close(fd);
    }

    void send_command(uint8_t command_id, std::vector<uint8_t> parameters = {},
                      bool does_respond = false) {
        std::vector<uint8_t> msg = {MAGIC_BYTES[0], MAGIC_BYTES[1], command_id};
        msg.insert(msg.end(), parameters.begin(), parameters.end());

        if (write(fd, msg.data(), msg.size()) != (ssize_t)msg.size()) {
            std::cerr << "write() failed: " << std::strerror(errno) << "\n";
        }

        if (does_respond) {
            // todooo
        }
    }

  private:
    int get_tty_fd(const char *path) { return open(path, O_RDWR | O_NOCTTY | O_CLOEXEC); }

    bool initialize_tty(int fd) {
        termios tty{};

        if (tcgetattr(fd, &tty) == -1) {
            std::cerr << "tcgetattr() failed: " << std::strerror(errno) << "\n";

            return false;
        }

        cfmakeraw(&tty);
        cfsetispeed(&tty, B115200);
        cfsetospeed(&tty, B115200);

        if (tcsetattr(fd, TCSANOW, &tty) == -1) {
            std::cerr << "tcsetattr() failed: " << std::strerror(errno) << "\n";

            return false;
        }

        return true;
    }
};

int main() {
    LedMatrix led_matrix("/dev/ttyACM0");
    led_matrix.send_command(0x01, {0x01});

    return 0;
}

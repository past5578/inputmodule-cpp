# inputmodule-cpp

A C++ library for controlling the Framework Laptop input modules.

## Linux permissions

You will normally not be able to access the serial port of the input module(s).
The fix for this is to install Framework's udev rule:

```sh
curl -LO https://raw.githubusercontent.com/FrameworkComputer/inputmodule-rs/main/release/50-framework-inputmodule.rules
sudo cp 50-framework-inputmodule.rules /etc/udev/rules.d/
sudo udevadm control --reload-rules
sudo udevadm trigger
```

If this doesn't work, try to unplug and reinsert the module.

If this still doesn't work, then you can add your user to the dialout group.

```sh
sudo usermod -aG dialout $USER
```

Then, log out and log back in and retry.

## References

[inputmodule-rs Commands](https://github.com/FrameworkComputer/inputmodule-rs/blob/main/commands.md)

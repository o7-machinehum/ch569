# 32-bit High Performance High-speed interface MCU CH569
Firmware for Ovrdrive v2 - the worlds only self-destructing USB drive.

### Getting Started
``` bash
git submodule update --init --recursive --checkout --force
cd wch-ch56x-isp # Build the ISP tool
make
cd ..
make                              # builds src/ (USB mass storage)
make APP=examples/uart_test       # builds UART test
make APP=examples/uart_test flash # build + flash an example
```

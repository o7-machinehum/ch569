# 32-bit High Performance High-speed interface MCU CH569
EN | [中文](README_zh.md)

### Overview
CH569 and CH565 are based on RISC-V3A core, and support the IMAC subset of RISC-V instructions. The chip integrates super-high-speed USB3.0 host and device controller (built-in PHY), Gigabit Ethernet controller, dedicated high-speed SerDes controller (built-in PHY, can drive optical fiber directly), high-speed parallel interface (HSPI), digital video port (DVP), SD/EMMC interface controller and encryption/decryption module. The DMA with width of 128 bits can ensure high-speed transfer of large amounts of data. CH569/CH565 can be widely used in streaming media, instant storage, super-high-speed USB3.0 FIFO, communication extension, security monitor and other applications.

### System Block Diagram
<img src="image/frame.jpg" alt="frame" style="zoom:50%;" />
 
### Features
- RISC-V core, 120MHz system clock frequency. Single-cycle multiplication and hardware division. Programmable interrupt controller. Low-power two-stage pipeline;
- 448KB Code Flash, 32KB DataFlash, 16KB SRAM with width of 32 bits, 32/64/96KB configurable SRAM with width of 128 bits;
- Built-in super-high-speed USB3.0 controller and transceiver (built-in PHY). USB3.0 Host/Device mode. OTG capability. Support USB3.0 HUB;
- Built-in high-speed USB2.0 controller and transceiver (built-in PHY). USB2.0 Host/Device mode. Control/bulk/interrupt/synchronous transfer;
- Built-in gigabit Ethernet controller (Ethernet). Provide RGMII and RMII PHY interface. 10/100/1000Mbps transfer rate;
- Built-in digital video port (DVP). Data width can be configured as 8/10/12 bits. Support YUV, RGB, JPEG compressed data;
- Built-in high-speed parallel interface (HSPI). Data width can be configured as 8/16/32 bits. Built-in FIFO. DMA capability. The maximum transfer speed can reach around 3.8Gbps;
- Built-in SerDes controller and transceiver (built-in PHY, can drive optical fiber directly). Support network cable transfer distance of 90 meters (only use one set of differential line). Support 1.25Gbps high-speed differential signal communication;
- Built-in EMMC controller. Support single-wire/4-wire/8-wire data communication mode. Comply to EMMC Specification Rev. 4.4 and Rev. 4.5.1, compatible with Specification Rev. 5.0;
- Support AES/SM4 algorithm. 8 types of combinations for encryption/decryption modes. Support encryption/decryption of SRAM/EMMC/HSPI data;
- 4 UARTs. Baud rate can be up to 6Mbps. Compatible with 16C550. Built-in FIFO. Multiple trigger levels;
- 2 SPIs. Master/Slave mode. Built-in FIFO. DMA capability;
- Active parallel port: 8-bit data, 15-bit address bus;
- 3 x 26-bit timers. Support timing, count, signal capture, PWM output, 4 expanded PWM outputs. Adjustable duty cycle;
- 49 general-purpose IOs. 8 settable level/edge interrupts. Some pins have alternate and map functions;
- Built-in watchdog, which integrates 2-wire debug interface and supports emulate online;
- Low-power mode. Support wake up some GPIOs, USB and Ethernet signal;
- Chip ID: unique 64-bit ID;
- Package: QFN68, QFN40.

### Building

Requires a RISC-V GCC toolchain (`riscv64-elf-gcc`). The default Makefile builds
the CH372 USB device example.

```bash
make            # build (output in build/)
make clean      # remove build artifacts
```

To override the toolchain prefix:

```bash
make CROSS=riscv64-unknown-elf-
```

The build produces `build/usbdev.elf`, `build/usbdev.bin`, and `build/usbdev.hex`.

To build a different example, edit the `APP`, `USB20DIR`, and `USB30DIR` paths in
the Makefile to point at the desired example under `evt/exam/`.

### Examples

All examples live under `evt/exam/`. Each has its own `user/` directory with a
`main.c` entry point. The shared SDK (peripheral drivers, startup, linker script)
is in `evt/exam/src/`.

| Category | Example | Description |
|----------|---------|-------------|
| **Peripherals** | | |
| | `bus8` | 8-bit parallel bus interface |
| | `dvp` | Digital video port (OV2640 camera) |
| | `ecdc` | AES/SM4 encryption/decryption |
| | `emmc` | eMMC controller |
| | `flash` | Internal flash read/write |
| | `gpio` | GPIO input/output and interrupts |
| | `pwmx` | PWM output |
| | `sd` | SD card interface |
| | `tmr` | Timer: timing, capture, PWM |
| | `uart` | UART serial communication |
| | `useroptionbytes` | User option bytes configuration |
| **SPI** | | |
| | `spi/spi0_flash` | SPI0 flash memory access |
| | `spi/spi0_host` | SPI0 master mode |
| | `spi/spi0_slave` | SPI0 slave mode |
| | `spi/spi1_host` | SPI1 master mode |
| | `spi/spi1_slave` | SPI1 slave mode |
| | `spi/spix_dma` | SPI DMA transfer |
| **HSPI** | | |
| | `hspi/hspi_normalmode` | HSPI normal mode |
| | `hspi/hspi_burstmode` | HSPI burst mode |
| | `hspi/hspi_burstmode_updown_switch` | HSPI burst with up/down switch |
| | `hspi/hspi_doubledmamode` | HSPI double-DMA mode |
| | `hspi/hspi_ecdc` | HSPI with encryption |
| **Ethernet** | | |
| | `eth/mac_raw` | Raw MAC frame send/receive |
| | `eth/dhcp` | DHCP client |
| | `eth/dns` | DNS resolver |
| | `eth/ipraw_ping` | ICMP ping |
| | `eth/tcpclient` | TCP client |
| | `eth/tcpserver` | TCP server |
| | `eth/udpclient` | UDP client |
| | `eth/udpserver` | UDP server |
| **USB Device** | | |
| | `usbss/usbd/ch372device` | CH372 vendor-class device (default build target) |
| | `usbss/usbd/ch372-hspidatatransdemo` | CH372 with HSPI data transfer |
| | `usbss/usbd/compatibilityhid` | HID device |
| | `usbss/usbd/msc_u-disk` | **Mass Storage Class (USB flash drive)** |
| | `usbss/usbd/simulatecdc` | CDC virtual serial port |
| | `usbss/usbd/uvc/uvc-dvp` | USB Video Class (DVP camera) |
| | `usbss/usbd/uvc/uvc-ram` | USB Video Class (RAM source) |
| **USB Host** | | |
| | `usbss/usbh/host_ss` | USB3.0 SuperSpeed host |
| | `usbss/usbh/host_ss_hub` | USB3.0 host with hub support |
| | `usbss/usbh/host_ss_udisk` | USB3.0 host U-disk file access |


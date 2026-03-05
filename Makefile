# ========= CH569 USB device demo (lowercase tree) =========

# ---- demo paths ----
# APP      := evt/exam/usbss/usbd/ch372device/user
APP 	 := evt/exam/usbss/usbd/msc_u-disk/user
USB20DIR := $(APP)/usb20
USB30DIR := $(APP)/usb30

# ---- SDK paths ----
PERIPH_INC := evt/exam/src/peripheral/inc
PERIPH_SRC := evt/exam/src/peripheral/src
RVMSIS_DIR := evt/exam/src/rvmsis
STARTUP_S  := evt/exam/src/startup/startup_ch56x.s
LDSCRIPT   := evt/exam/src/ld/link.ld

# ---- toolchain ----
CROSS ?= riscv64-elf-
CC      := $(CROSS)gcc
AS      := $(CROSS)gcc
LD      := $(CROSS)gcc
OBJCOPY := $(CROSS)objcopy
SIZE    := $(CROSS)size

# ---- output ----
BUILD := build
ELF   := $(BUILD)/usbdev.elf
BIN   := $(BUILD)/usbdev.bin
HEX   := $(BUILD)/usbdev.hex
MAP   := $(BUILD)/usbdev.map

# ---- arch/defines/includes ----
ARCH   := -march=rv32imac_zicsr -mabi=ilp32
DEFS   := -DCH56x=1 -DCH569=1

INCS := \
  -I$(APP) \
  -I$(USB20DIR) \
  -I$(USB30DIR) \
  -I$(PERIPH_INC) \
  -I$(RVMSIS_DIR)

# ---- flags ----
CFLAGS  := $(ARCH) -O2 -g3 -ffunction-sections -fdata-sections -fno-common \
           -Wall -Wextra -Wno-attributes
ASFLAGS := $(ARCH) -x assembler-with-cpp -g3
LDFLAGS := $(ARCH) -T$(LDSCRIPT) -nostartfiles \
           -Wl,--gc-sections -Wl,-Map,$(MAP)

# Vendor USB30 library (exists in your tree)
USB30_LIB := $(USB30DIR)/libch56x_usb30_device_lib.a

# ---- sources ----
SRCS_C := \
  $(APP)/main.c \
  $(APP)/sw_udisk.c \
  $(USB20DIR)/ch56x_usb20.c \
  $(USB30DIR)/ch56x_usb30.c \
  $(RVMSIS_DIR)/core_riscv.c \
  $(wildcard $(PERIPH_SRC)/*.c)

SRCS_S := $(STARTUP_S)

OBJS := \
  $(patsubst %.c,$(BUILD)/%.o,$(SRCS_C)) \
  $(patsubst %.s,$(BUILD)/%.o,$(SRCS_S))

# ---- rules ----
.PHONY: all clean print

all: $(ELF) $(BIN) $(HEX)
	@$(SIZE) $(ELF)

$(BUILD)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(DEFS) $(INCS) -c $< -o $@

$(BUILD)/%.o: %.s
	@mkdir -p $(dir $@)
	$(AS) $(ASFLAGS) $(DEFS) $(INCS) -c $< -o $@

$(ELF): $(OBJS)
	@mkdir -p $(BUILD)
	$(LD) $(OBJS) $(LDFLAGS) -o $@ $(USB30_LIB)

$(BIN): $(ELF)
	$(OBJCOPY) -O binary -R .DMADATA $< $@

$(HEX): $(ELF)
	$(OBJCOPY) -O ihex -R .DMADATA $< $@

clean:
	rm -rf $(BUILD)

flash: all
	sudo ./wch-ch56x-isp/wch-ch56x-isp -f $(BIN)

print:
	@echo "APP=$(APP)"
	@echo "STARTUP_S=$(STARTUP_S)"
	@echo "LDSCRIPT=$(LDSCRIPT)"
	@echo "USB30_LIB=$(USB30_LIB)"

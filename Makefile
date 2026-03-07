# ========= CH569 build system =========
#
# Usage:
#   make                     - build src/ (default, USB mass storage app)
#   make APP=examples/uart_test  - build the UART test example
#   make flash               - build and flash
#   make APP=examples/uart_test flash

# ---- app selection (override on command line) ----
APP ?= src

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
ELF   := $(BUILD)/firmware.elf
BIN   := $(BUILD)/firmware.bin
HEX   := $(BUILD)/firmware.hex
MAP   := $(BUILD)/firmware.map

# ---- arch/defines ----
ARCH := -march=rv32imac_zicsr -mabi=ilp32
DEFS := -DCH56x=1 -DCH569=1 -DDEBUG=1

# ---- includes (always include app dir + SDK) ----
INCS := \
  -I$(APP) \
  -I$(PERIPH_INC) \
  -I$(RVMSIS_DIR)

# ---- flags ----
CFLAGS  := $(ARCH) -O2 -g3 -ffunction-sections -fdata-sections -fno-common \
           -Wall -Wextra -Wno-attributes
ASFLAGS := $(ARCH) -x assembler-with-cpp -g3
LDFLAGS := $(ARCH) -T$(LDSCRIPT) -nostartfiles \
           -Wl,--gc-sections -Wl,-Map,$(MAP)

# ---- per-app config (included if present) ----
# Apps can provide app.mk to add extra sources, includes, libs, etc.
-include $(APP)/app.mk

# ---- sources ----
SRCS_C += \
  $(wildcard $(APP)/*.c) \
  $(RVMSIS_DIR)/core_riscv.c \
  $(wildcard $(PERIPH_SRC)/*.c)

SRCS_S := $(STARTUP_S)

OBJS := \
  $(patsubst %.c,$(BUILD)/%.o,$(SRCS_C)) \
  $(patsubst %.s,$(BUILD)/%.o,$(SRCS_S))

# ---- rules ----
.PHONY: all clean flash

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
	$(LD) $(OBJS) $(LDFLAGS) -o $@ $(LIBS)

$(BIN): $(ELF)
	$(OBJCOPY) -O binary -R .DMADATA $< $@

$(HEX): $(ELF)
	$(OBJCOPY) -O ihex -R .DMADATA $< $@

clean:
	rm -rf $(BUILD)

flash: all
	sudo ./wch-ch56x-isp/wch-ch56x-isp -f $(BIN)

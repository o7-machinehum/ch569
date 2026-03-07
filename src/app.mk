# Extra sources and includes for the USB mass storage app
USB20DIR := $(APP)/usb20
USB30DIR := $(APP)/usb30
SDDIR    := evt/exam/sd/user

INCS += -I$(USB20DIR) -I$(USB30DIR) -I$(SDDIR)

SRCS_C += \
  $(wildcard $(USB20DIR)/*.c) \
  $(wildcard $(USB30DIR)/*.c) \
  $(SDDIR)/sd.c

LIBS += $(USB30DIR)/libch56x_usb30_device_lib.a

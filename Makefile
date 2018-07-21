# BOARD=debug
# BOARD=crickit
BOARD=feather_m0_express
-include Makefile.user
include boards/$(BOARD)/board.mk
CC=arm-none-eabi-gcc
CXX=arm-none-eabi-g++

ifeq ($(DEBUG), 1)
ENABLE_LOGGING = -DENABLE_LOGGING
else
ENABLE_LOGGING =
endif

COMMON_FLAGS = -mthumb -mcpu=cortex-m0plus -Os -g3 -D$(CHIP_FAMILY) -D__$(CHIP_VARIANT)__ -DBOARD_$(BOARD_NAME) $(ENABLE_LOGGING)

WFLAGS = \
-Wall -Werror

SFLAGS = $(COMMON_FLAGS) \
-x assembler-with-cpp -c \
$(WFLAGS)
CFLAGS = $(COMMON_FLAGS) \
-x c -std=gnu99 -c \
-MD -MP -MF "$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" \
$(WFLAGS)
CXXFLAGS = $(COMMON_FLAGS) \
-ffunction-sections -fdata-sections \
-fno-rtti -fno-exceptions -c -std=c++11 \
-MD -MP -MF "$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" \
$(WFLAGS)

LDFLAGS= $(COMMON_FLAGS) \
-Wall -Werror -Wl,--cref -Wl,--check-sections -Wl,--gc-sections -Wl,--unresolved-symbols=report-all -Wl,--warn-common \
-Wl,--warn-section-align -Wl,--warn-unresolved-symbols \
-save-temps \
--specs=nano.specs --specs=nosys.specs
BUILD_PATH=build/$(BOARD)

QPPORT = lib/qp/ports/arm-cm/qxk/gnu

INCLUDES = -I. -I./include -I./bsp -I./lib/qp/extras -I./lib/qp/include -I./lib/qp/source -I$(QPPORT)
INCLUDES += -I./boards/$(BOARD) -Ilib/cmsis/CMSIS/Include
INCLUDES += -I$(BUILD_PATH)
INCLUDES += -I./arduino15/packages/adafruit/hardware/samd/1.2.1/cores/arduino
INCLUDES += -I./arduino15/packages/adafruit/hardware/samd/1.2.1/variants/$(BOARD)

ifeq ($(CHIP_FAMILY), SAMD21)
INCLUDES += -Ilib/samd21/samd21a/include/
endif

ifeq ($(CHIP_FAMILY), SAMD09)
INCLUDES += -Ilib/samd09/include/
endif

ifeq ($(CHIP_FAMILY), SAMD21)
CSOURCES = Device_Startup/startup_samd21.c \
	Device_Startup/system_samd21.c
endif

ifeq ($(CHIP_FAMILY), SAMD09)
CSOURCES = Device_Startup/startup_samd09.c \
	Device_Startup/system_samd09.c
endif

COMMON_SRC =

SOURCES = $(COMMON_SRC) \
	source/main.cpp \
	bsp/bsp_neopix.cpp

# SOBJECTS = $(patsubst %.S,$(BUILD_PATH)/%.o,$(SSOURCES))
SOBJECTS =
COBJECTS = $(patsubst %.c,$(BUILD_PATH)/%.o,$(CSOURCES))
OBJECTS = $(patsubst %.cpp,$(BUILD_PATH)/%.o,$(SOURCES))

NAME=saw-saw-$(BOARD)
EXECUTABLE=$(BUILD_PATH)/$(NAME).bin

all: dirs $(EXECUTABLE)

dirs:
	@echo "Building $(BOARD)"
	@python scripts/datecode.py
	-@mkdir -p $(BUILD_PATH)
	-@mkdir -p $(BUILD_PATH)/lib/qp/source
	-@mkdir -p $(BUILD_PATH)/lib/qp/include
	-@mkdir -p $(BUILD_PATH)/lib/qp/extras
	-@mkdir -p $(BUILD_PATH)/lib/qp/ports/arm-cm/qxk/gnu/
	-@mkdir -p $(BUILD_PATH)/source
	-@mkdir -p $(BUILD_PATH)/Device_Startup
	-@mkdir -p $(BUILD_PATH)/bsp

$(EXECUTABLE): $(SOBJECTS) $(COBJECTS) $(OBJECTS)
	$(CC) -L$(BUILD_PATH) $(LDFLAGS) \
		 -T$(LINKER_SCRIPT) \
		 -Wl,-Map,$(BUILD_PATH)/$(NAME).map -o $(BUILD_PATH)/$(NAME).elf $(SOBJECTS) $(COBJECTS) $(OBJECTS)
	arm-none-eabi-objcopy -O binary $(BUILD_PATH)/$(NAME).elf $@
	@echo
	-@arm-none-eabi-size $(BUILD_PATH)/$(NAME).elf
	@echo

$(BUILD_PATH)/%.o: %.S $(wildcard include/*.h boards/*/*.h)
	echo "$<"
	$(CC) $(SFLAGS) $(BLD_EXTA_FLAGS) $(INCLUDES) $< -o $@

$(BUILD_PATH)/%.o: %.c $(wildcard include/*.h boards/*/*.h)
	echo "$<"
	$(CC) $(CFLAGS) $(BLD_EXTA_FLAGS) $(INCLUDES) $< -o $@

$(BUILD_PATH)/%.o: %.cpp $(wildcard include/*.h boards/*/*.h)
	echo "$<"
	$(CXX) $(CXXFLAGS) $(BLD_EXTA_FLAGS) $(INCLUDES) $< -o $@

install:
	./scripts/_bossac_local.sh ./build/feather_m0_express/saw-saw-feather_m0_express.bin

clean:
	rm -rf build

all-boards:
	for f in `cd boards; ls` ; do "$(MAKE)" BOARD=$$f ; done

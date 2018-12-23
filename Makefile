
TOOLCHAIN_DIR=/home/jeremy/bin/gcc-arm-none-eabi-8-2018-q4-major
AS=$(TOOLCHAIN_DIR)/bin/arm-none-eabi-as
CC=$(TOOLCHAIN_DIR)/bin/arm-none-eabi-gcc
OBJCOPY=$(TOOLCHAIN_DIR)/bin/arm-none-eabi-objcopy
LD=$(TOOLCHAIN_DIR)/bin/arm-none-eabi-ld
 
CFLAGS=-mcpu=cortex-m4  -mfpu=fpv4-sp-d16 -mthumb -mfloat-abi=softfp  --specs=nosys.specs -nostartfiles -Og -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -ffreestanding -fno-move-loop-invariants -Wall -Wextra  -g3 -DDEBUG -DUSE_FULL_ASSERT -DTRACE -DOS_USE_TRACE_SEMIHOSTING_DEBUG -DSTM32F407xx -DUSE_HAL_DRIVER -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" #-c -o "$@" "$<"
# CFLAGS += -fpic -pie
CFLAGS+=-I$(INCLUDE_DIR) -I$(INCLUDE_DIR)/cmsis -I$(INCLUDE_DIR)/stm32f4-hal -Wl,-Map,kernel.map

SUBDIRS=$(shell ls -l | grep ^d | awk '{if($$9 != "bin" && $$9 != "include") print $$9}')

ROOT_DIR=$(shell pwd)
INCLUDE_DIR=$(ROOT_DIR)/include

ELF=bootloader.elf
BIN=bootloader.bin
BIN_DIR=$(ROOT_DIR)/bin

CUR_DIR=$(shell pwd)

BUILD_DIR=$(BIN_DIR)/src

GLB_OBJS=$(wildcard $(BUILD_DIR)/*.o)

# OBJS=$(shell ls -l $(OBJS_DIR) | grep ^- | awk '{print $9}' | sed "s:^:$(OBJS_DIR)/:")
OBJS+=$(GLB_OBJS)
# OBJS=$(wildcard $(OBJS_DIR)/*.o)
# OBJ=kernel_obj.elf

export CC ROOT_DIR CFLAGS OBJS BIN_DIR BUILD_DIR

.PHONY : all clean 

all: bootloader
	
prepare:
	./mk_bin.sh $(BIN_DIR)
	./mk_bin.sh $(BUILD_DIR)

target: subdirs 
	$(CC) $(CFLAGS) -T $(ROOT_DIR)/bootloader.ld $(OBJS) -o $(BIN_DIR)/$(ELF)
#	$(LD) -T $(ROOT_DIR)/kernel.ld -L /Users/apple/bin/gcc-arm-none-eabi-5_4-2016q3/lib/gcc/arm-none-eabi/5.4.1/ -lgcc $^ -o $(BIN_DIR)/$(ELF)

bootloader: target
	$(OBJCOPY) -O binary $(BIN_DIR)/$(ELF)  $(BIN_DIR)/$(BIN)

# define build-dir
# 	echo building $1 with action $2
# 	make -C $1 $2
# endef

subdirs: prepare $(SUBDIRS)
#	$(foreach dir, $(SUBDIRS), $(call build-dir $(dir)))
	make -C src
	
# %.o:%.c
# 	$(CC) $(CFLAGS) -c $^ -o $@
	
# %.o:%.s
# 	$(CC) $(CFLAGS) -c $^ -o $@


clean: $(SUBDIRS)
# $(foreach dir, $(SUBDIRS), $(call build-dir $(dir) clean))
	make -C src clean
	rm -f $(CUR_DIR)/*.o
	rm -rf $(BIN_DIR)
	

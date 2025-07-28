CC = clang
ARCH = -target	armv7m-none-eabi -mthumb -mcpu=cortex-m3
CFLAGS = $(ARCH) -O3 -Wall -std=c2y -MMD -MP -Iinclude/ -ffreestanding

LD = clang -fuse-ld=lld
LDFLAGS = $(ARCH) -Tflash.ld -nostartfiles -nostdlib -static
LDFLAGS += -WL,-X,-s,-S,--as-needed,--gc-sections,--icf=all

#SRCS = $(wildcard src/*.c src/sys/*.c)
#OBJS = $(SRCS:src/%.c=obj/%.o)
SRC_DIRS = src src/sys src/driver
SRCS = $(foreach d,$(SRC_DIRS),$(wildcard $(d)/*.c))
OBJS = $(patsubst src/%.c,obj/%.o,$(SRCS))
DEPS = $(OBJS:.o=.d)

TARGET = obj/main

SF = st-flash

all : $(TARGET).bin
	$(SF) write $(TARGET).bin 0x08000000

$(TARGET).bin: $(TARGET).elf
	llvm-objcopy -O binary $< $@

$(TARGET).elf: $(OBJS)
	$(LD) $(LDFLAGS) $(OBJS) -o $@

obj/%.o: src/%.c 
	$(CC) $(CFLAGS) -c $< -o $@

-include $(DEPS)

clean :
	rm -rf obj/**/*.*

.PHONY: all clean 




















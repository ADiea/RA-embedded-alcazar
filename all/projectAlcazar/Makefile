#Makefile for STM32f0discovery simple blink example

#Based on work by Frank Duignan 
# [http://eleceng.dit.ie/frank/arm/BareMetalSTM32F0Discovery/blinky.html]

#A makefile is a file describig the steps needed to make a project. 
#It avoids having to type multiple commands everytime. 

#Set WINDOWS variable default 0; ?= means set if not already set; if you type in console "make all WINDOWS=1" you will set WINDOWS to 1 from outside
#For windows users set this in eclipse, build targets.
WINDOWS ?= 0
MACOSX ?= 0

ifeq ($(WINDOWS),1)
	CC = arm-none-eabi-gcc
	AS = arm-none-eabi-as
	LD = arm-none-eabi-ld
	OBJCOPY = arm-none-eabi-objcopy
	OBJDUMP = arm-none-eabi-objdump
	SIZE = arm-none-eabi-size
	DELETE = rm
	DELETEFLAGS = -rf
else ifeq ($(MACOSX),1)
	CC = arm-none-eabi-gcc
	AS = arm-none-eabi-as
	LD = arm-none-eabi-ld
	OBJCOPY = arm-none-eabi-objcopy
	OBJDUMP = arm-none-eabi-objdump
	SIZE = arm-none-eabi-size
	DELETE = rm
	DELETEFLAGS = -rf 
else
	CC=arm-linux-gnueabi-gcc
	AS=arm-linux-gnueabi-as
	LD=arm-linux-gnueabi-ld
	OBJCOPY=arm-linux-gnueabi-objcopy
	OBJDUMP=arm-linux-gnueabi-objdump
	SIZE=arm-linux-gnueabi-size
	DELETE = rm
	DELETEFLAGS = -rf
endif

#These are the flags or parameters we will pass to the compiler and assembler.
CCFLAGS = -mcpu=cortex-m0 -mthumb -g -Iinclude/
ASFLAGS = -mcpu=cortex-m0 -mthumb -g 

# List the object files involved in this project. They will be located in the out folder
OBJS =	out/startup.o  out/project.o out/gpio.o out/spi.o out/system.o out/timer.o \
		out/delay.o out/interrupts.o out/max7219.o out/spiSoft.o

#A linker script file informs the linker of the memory layout of the architecture so that the linker can correctly create the final binary file. 
#See the file for additional details
LINKER_SCRIPT = ld/linker_script.ld
	
#A makefile contains one or more 'recipies' or targets. 
#A target is specified like this target_name : dependencies which means that in order to make the target first the dependencies targets have to be made

# The default 'target' (output) is main.elf and it depends on the object files being there.
# These object files are linked together to create main.elf
# Also main.map is generated which contains the contents of main.o and startup.o mapped accordingly to the linker script file 
# [!] If not clear ask your trainer to clarify memory mapping or learn more here [https://youtu.be/aT5XMOrid7Y]
main.elf : $(OBJS)
	$(LD) $(OBJS) -T $(LINKER_SCRIPT) --cref -Map out/main.map -nostartfiles -o out/main.elf
	$(OBJCOPY) -O ihex out/main.elf out/main.hex
	$(OBJCOPY) -O binary out/main.elf out/main.bin
#	$(OBJDUMP) -St out/main.elf > out/main.lst
	$(SIZE) out/main.elf

# The object file project.o depends on project.c.  project.c is compiled into project.o
#$@ is the target, $< is the first prerequisite
out/project.o: src/app/project.c
	$(CC) -c $(CCFLAGS) $< -o $@
out/gpio.o: src/sys/gpio.c
	$(CC) -c $(CCFLAGS) $< -o $@
out/spi.o: src/sys/spi.c
	$(CC) -c $(CCFLAGS) $< -o $@
out/system.o: src/sys/system.c
	$(CC) -c $(CCFLAGS) $< -o $@
out/timer.o: src/sys/timer.c
	$(CC) -c $(CCFLAGS) $< -o $@
out/delay.o: src/sys/delay.c
	$(CC) -c $(CCFLAGS) $< -o $@
out/interrupts.o: src/sys/interrupts.c
	$(CC) -c $(CCFLAGS) $< -o $@
out/max7219.o: src/sys/max7219.c
	$(CC) -c $(CCFLAGS) $< -o $@
out/spiSoft.o: src/sys/spiSoft.c
	$(CC) -c $(CCFLAGS) $< -o $@
	

# The object file startup.o depends on startup.s => startup.s is assembled to make startup.o
out/startup.o: src/sys/startup.s
	$(AS) $(ASFLAGS) src/sys/startup.s -asghl=out/startup.lst -o out/startup.o
# if someone types in 'make clean' then remove all object files and executables
# Just remove everything in the out/ folder
clean: 
	$(DELETE) $(DELETEFLAGS) out/*
# the all target should first make clean then make main.elf above which depends on the objs as shown
all: main.elf

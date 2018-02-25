#Makefile for STM32f0discovery simple blink example

#Based on work by Frank Duignan 
# [http://eleceng.dit.ie/frank/arm/BareMetalSTM32F0Discovery/blinky.html]

#A makefile is a file describig the steps needed to make a project. 
#It avoids having to type multiple commands everytime. 

#This is how we define constants in a Makefile constant_name=value

# Specify the compiler to use
CC=arm-none-eabi-gcc
# Specify the assembler to use
AS=arm-none-eabi-as
# Specity the linker to use
LD=arm-none-eabi-ld

#Tools to copy, perform dump and show size of final binary
OBJCOPY=arm-none-eabi-objcopy
OBJDUMP=arm-none-eabi-objdump
SIZE=arm-none-eabi-size

#These are the flags or parameters we will pass to the compiler and assembler.
#The final command will look like "arm-none-eabi-gcc -mcpu=cortex-m0 -mthumb -g" 
#  which tells the compiler what microcontroller(architecture) it should compile for and that is should use Thumb instruction-set 
# (ARM architecture supports two instruction sets but cortex m0 only supports thumb which is a simpler instruction set)
CCFLAGS=-mcpu=cortex-m0 -mthumb -g 
ASFLAGS=-mcpu=cortex-m0 -mthumb -g 

# List the object files involved in this project. They will be located in the out folder
OBJS=	out/startup.o \
	out/main.o 

#A linker script file informs the linker of the memory layout of the architecture so that the linker can correctly create the final binary file. 
#See the file for additional details
LINKER_SCRIPT= ld/linker_script.ld
	
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
	$(OBJDUMP) -St out/main.elf >out/main.lst
	$(SIZE) out/main.elf

# The object file main.o depends on main.c.  main.c is compiled to make main.o
out/main.o: main.c
	$(CC) -c $(CCFLAGS) main.c -o out/main.o
# The object file startup.o depends on startup.s => startup.s is assembled to make startup.o
out/startup.o: startup.s
	$(AS) $(ASFLAGS) startup.s -asghl=out/startup.lst -o out/startup.o
# if someone types in 'make clean' then remove all object files and executables
# Just remove everything in the out/ folder
clean: 
	rm out/*
# the all target should first make clean then make main.elf above which depends on the objs as shown
all: clean main.elf
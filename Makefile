NAME = esp8266
CC = arm-none-eabi-gcc
LIBPI = ../libpi
CFLAGS = -I$(LIBPI) -I. -Wall -O2 -nostartfiles -ffreestanding 

SRC = $(NAME).c esp.c str.c
OBJS = $(SRC:.c=.o)

all : kernel.img

kernel.img : $(LIBPI)/memmap $(LIBPI)/start.o $(OBJS)
	make -C $(LIBPI)
	arm-none-eabi-ld $(LIBPI)/start.o $(OBJS) $(LIBPI)/libpi.a -T $(LIBPI)/memmap -o $(NAME).elf
	arm-none-eabi-objdump -D $(NAME).elf > $(NAME).list
	arm-none-eabi-objcopy $(NAME).elf -O binary kernel.img

clean :
	rm -f *.o *.bin *.elf *.list *.img *~ Makefile.bak

depend:
	makedepend -I$(LIBPI)/.. *.[ch] str.h 

# DO NOT DELETE
esp8266.c: esp.h str.h

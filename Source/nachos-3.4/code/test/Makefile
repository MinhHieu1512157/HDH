# use normal make for this Makefile
#
# Makefile for building user programs to run on top of Nachos
#
# Several things to be aware of:
#
#    Nachos assumes that the location of the program startup routine (the
# 	location the kernel jumps to when the program initially starts up)
#       is at location 0.  This means: start.o must be the first .o passed 
# 	to ld, in order for the routine "Start" to be loaded at location 0
#

# if you are cross-compiling, you need to point to the right executables
# and change the flags to ld and the build procedure for as

GCCDIR = /home/sv/hdh/cross-compiler/decstation-ultrix/2.95.3/

LDFLAGS = -T script -N
ASFLAGS = -mips2
CPPFLAGS = $(INCDIR)

# if you aren't cross-compiling:
# GCCDIR =
# LDFLAGS = -N -T 0
# ASFLAGS =
# CPPFLAGS = -P $(INCDIR)

PATH = $(GCCDIR):/lib:/usr/bin:/bin

CC = $(GCCDIR)gcc -B /home/sv/hdh/cross-compiler/decstation-ultrix/2.95.3/
AS = $(GCCDIR)as
LD = $(GCCDIR)ld

CPP = gcc -E
INCDIR =-I../userprog -I../threads
CFLAGS = -G 0 -c $(INCDIR)

all: halt shell matmult sort createfile help ascii echo cat copy reverse testAll multiprog1 multiprog2 student faucet water

start.o: start.s ../userprog/syscall.h
	$(CPP) $(CPPFLAGS) start.c > strt.s
	$(AS) $(ASFLAGS) -o start.o strt.s
	rm strt.s

halt.o: halt.c
	$(CC) $(CFLAGS) -c halt.c
halt: halt.o start.o
	$(LD) $(LDFLAGS) start.o halt.o -o halt.coff
	../bin/coff2noff halt.coff halt

shell.o: shell.c
	$(CC) $(CFLAGS) -c shell.c
shell: shell.o start.o
	$(LD) $(LDFLAGS) start.o shell.o -o shell.coff
	../bin/coff2noff shell.coff shell

_sort.o: _sort.c
	$(CC) $(CFLAGS) -c _sort.c
_sort: _sort.o start.o
	$(LD) $(LDFLAGS) start.o _sort.o -o _sort.coff
	../bin/coff2noff _sort.coff _sort

matmult.o: matmult.c
	$(CC) $(CFLAGS) -c matmult.c
matmult:	
	matmult.o start.o
	$(LD) $(LDFLAGS) start.o matmult.o -o matmult.coff
	../bin/coff2noff matmult.coff matmult

createfile.o: createfile.c
	$(CC) $(CFLAGS) -c createfile.c
createfile: createfile.o start.o
	$(LD) $(LDFLAGS) start.o createfile.o -o createfile.coff
	../bin/coff2noff createfile.coff createfile

# khai bao bien dich cho chuong trinh viet trong file ./test/hep.c, ascii.c va sort.c	
help.o: help.c
	$(CC) $(CFLAGS) -c help.c
help: help.o start.o
	$(LD) $(LDFLAGS) start.o help.o -o help.coff
	../bin/coff2noff help.coff help	
	
ascii.o: ascii.c
	$(CC) $(CFLAGS) -c ascii.c
ascii: ascii.o start.o
	$(LD) $(LDFLAGS) start.o ascii.o -o ascii.coff
	../bin/coff2noff ascii.coff ascii

sort.o: sort.c
	$(CC) $(CFLAGS) -c sort.c
sort: sort.o start.o
	$(LD) $(LDFLAGS) start.o sort.o -o sort.coff
	../bin/coff2noff sort.coff sort	
	
echo.o: echo.c
	$(CC) $(CFLAGS) -c echo.c
echo: echo.o start.o
	$(LD) $(LDFLAGS) start.o echo.o -o echo.coff
	../bin/coff2noff echo.coff echo	
	
cat.o: cat.c
	$(CC) $(CFLAGS) -c cat.c
cat: cat.o start.o
	$(LD) $(LDFLAGS) start.o cat.o -o cat.coff
	../bin/coff2noff cat.coff cat
	
copy.o: copy.c
	$(CC) $(CFLAGS) -c copy.c
copy: copy.o start.o
	$(LD) $(LDFLAGS) start.o copy.o -o copy.coff
	../bin/coff2noff copy.coff copy
	
reverse.o: reverse.c
	$(CC) $(CFLAGS) -c reverse.c
reverse: reverse.o start.o
	$(LD) $(LDFLAGS) start.o reverse.o -o reverse.coff
	../bin/coff2noff reverse.coff reverse
	
testAll.o: testAll.c
	$(CC) $(CFLAGS) -c testAll.c
testAll: testAll.o start.o
	$(LD) $(LDFLAGS) start.o testAll.o -o testAll.coff
	../bin/coff2noff testAll.coff testAll
	
multiprog1.o: multiprog1.c
	$(CC) $(CFLAGS) -c multiprog1.c
multiprog1: multiprog1.o start.o
	$(LD) $(LDFLAGS) start.o multiprog1.o -o multiprog1.coff
	../bin/coff2noff multiprog1.coff multiprog1
	
multiprog2.o: multiprog2.c
	$(CC) $(CFLAGS) -c multiprog2.c
multiprog2: multiprog2.o start.o
	$(LD) $(LDFLAGS) start.o multiprog2.o -o multiprog2.coff
	../bin/coff2noff multiprog2.coff multiprog2

student.o: student.c
	$(CC) $(CFLAGS) -c student.c
student: student.o start.o
	$(LD) $(LDFLAGS) start.o student.o -o student.coff
	../bin/coff2noff student.coff student

faucet.o: faucet.c
	$(CC) $(CFLAGS) -c faucet.c
faucet: faucet.o start.o
	$(LD) $(LDFLAGS) start.o faucet.o -o faucet.coff
	../bin/coff2noff faucet.coff faucet

water.o: water.c
	$(CC) $(CFLAGS) -c water.c
water: water.o start.o
	$(LD) $(LDFLAGS) start.o water.o -o water.coff
	../bin/coff2noff water.coff water


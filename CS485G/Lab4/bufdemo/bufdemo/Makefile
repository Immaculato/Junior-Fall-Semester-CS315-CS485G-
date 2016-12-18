# Makefile for lab4

GOAL = bufdemo
CFLAGS = -Wall -g -O0 -fno-stack-protector

all: $(GOAL)

asm: $(GOAL)
	objdump -d $(GOAL) > $(GOAL).s

clean: 
	rm -f $(GOAL) $(GOAL).s

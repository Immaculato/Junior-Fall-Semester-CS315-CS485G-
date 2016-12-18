# Makefile for Project 1 of CS485, Spring 2015.
# This project is to manipulate binary data in C.
# I take no credit for creating this makefile: Dr. Raphael Finkel is the original creator
#  and provider of the makefile for this project.

# How to build from command line: `make prog1`

PROJECT = prog1
GOAL = prog1
CFLAGS = -Wall
DATAFILE = file.data
INPUT = inputFile
OUTPUT = outputFile

# interactive
run-i: $(GOAL) $(DATAFILE)
	./$(GOAL) $(DATAFILE)

# batch
run-b: $(GOAL) $(DATAFILE) $(INPUT) $(OUTPUT)
	./$(GOAL) $(DATAFILE) < $(INPUT) > $(OUTPUT)

clean:
	rm -f $(GOAL) $(OUTPUT)

submit: $(GOAL).c Makefile README
	tar -czf $(PROJECT).tgz $(GOAL).c Makefile README


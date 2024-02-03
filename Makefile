.PHONY: compile run bench doxy clean

CC = gcc
FLAGS = -Wall -Wextra -Werror -pedantic -std=c99 -O2
SRCS = main.c
BENCHDIR = utils
BENCHTARGET = benchmark
TARGET = main

all: run

compile: $(SRCS)
	$(CC) $(FLAGS) $(SRCS) -o $(TARGET)
	@echo Compilation complete

run: compile
	@$(TARGET).exe
	@echo Done runnig complete

bench:
	$(CC) $(FLAGS) $(SRCS) $(BENCHDIR)/*.c -o $(BENCHDIR)/$(BENCHTARGET)
	@$(BENCHDIR)\$(BENCHTARGET).exe
	@echo Benchmarking complete

doxy: Doxyfile
	@doxygen
	@echo Doxygen documentation generated

clean:
	del /Q $(TARGET).exe
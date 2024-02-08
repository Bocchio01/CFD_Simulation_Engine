.PHONY: compile run bench doxy clean

CC = gcc
# FLAGS = -Wall -Wextra -Werror -pedantic -std=c99 -O2
SRCS = *.c input/*.c solver/*.c solver/mesh/*.c solver/methods/*.c solver/schemes/*.c output/*.c
# SRCS = main.c
LIBS = utils/algebra/*.c utils/cJSON/*.c
BENCHDIR = utils
BENCHTARGET = benchmark
TARGET = main

all: run

compile: $(SRCS)
	$(CC) $(FLAGS) $(LIBS) $(SRCS) -o $(TARGET)
	@echo Compilation complete

run: compile
	@$(TARGET).exe
	@echo Done runnig complete

bench:
	$(CC) $(FLAGS) $(LIBS) $(SRCS) $(BENCHDIR)/*.c -o $(BENCHDIR)/$(BENCHTARGET)
	@$(BENCHDIR)\$(BENCHTARGET).exe
	@echo Benchmarking complete

doxy: Doxyfile
	@doxygen
	@echo Doxygen documentation generated

clean:
	del /Q $(TARGET).exe
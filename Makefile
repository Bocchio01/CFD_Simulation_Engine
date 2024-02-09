.PHONY: compile run bench doxy clean

CC = gcc
# FLAGS = -Wall -Wextra -Werror -pedantic -std=c99 -O2
SRCS = *.c in/*.c in/parsers/*.c engine/*.c engine/mesh/*.c engine/methods/*.c engine/schemes/*.c out/*.c
# SRCS = main.c
LIBS = utils/algebra/*.c utils/cJSON/*.c  utils/custom_file/*.c utils/log/*.c
DEFINES = -DLOG_USE_COLOR
BENCHDIR = utils
BENCHTARGET = benchmark
TARGET = main

all: run

compile: $(SRCS)
	$(CC) $(DEFINES) $(FLAGS) $(LIBS) $(SRCS) -o $(TARGET)
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
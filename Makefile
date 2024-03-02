.PHONY: compile run bench doxy clean

CC = gcc
FLAGS = -Wall -Wextra -Werror -std=c99 -O2 # -pedantic
SRCS = src/CFD.c src/in/*.c src/out/*.c src/in/parsers/*.c src/engine/*.c src/engine/mesh/*.c src/engine/methods/*.c src/engine/schemes/*.c
LIBS = src/utils/cALGEBRA/*.c src/utils/cJSON/*.c  src/utils/cFILE/*.c src/utils/cLOG/*.c
DEFINES = -DLOG_USE_COLOR
# BENCHDIR = utils
BENCHTARGET = bench
TARGET = main

all: run

compile: $(SRCS)
	$(CC) $(DEFINES) $(FLAGS) $(LIBS) src/main.c $(SRCS) -o $(TARGET)
	@echo Compilation complete

run: compile
	@$(TARGET).exe
	@echo Done runnig complete

bench:
	$(CC) $(DEFINES) $(FLAGS) $(LIBS) $(SRCS) bench.c -o $(BENCHTARGET)
	@$(BENCHTARGET).exe
	@echo Benchmarking complete

doxy: Doxyfile
	@doxygen
	@echo Doxygen documentation generated

clean:
	del /Q $(TARGET).exe
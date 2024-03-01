.PHONY: compile run bench doxy clean

CC = gcc
FLAGS = -Wall -Wextra -Werror -std=c99 -O2 # -pedantic
SRCS = src/*.c src/in/*.c src/out/*.c src/in/parsers/*.c src/engine/*.c src/engine/mesh/*.c src/engine/methods/*.c src/engine/schemes/*.c
LIBS = src/utils/cALGEBRA/*.c src/utils/cJSON/*.c  src/utils/cFILE/*.c src/utils/cLOG/*.c
DEFINES = -DLOG_USE_COLOR
# BENCHDIR = utils
# BENCHTARGET = benchmark
TARGET = main

all: run

compile: $(SRCS)
	$(CC) $(DEFINES) $(FLAGS) $(LIBS) $(SRCS) -o $(TARGET)
	@echo Compilation complete

run: compile
	@$(TARGET).exe
	@echo Done runnig complete

# bench:
# 	$(CC) $(FLAGS) $(LIBS) $(SRCS) $(BENCHDIR)/*.c -o $(BENCHDIR)/$(BENCHTARGET)
# 	@$(BENCHDIR)\$(BENCHTARGET).exe
# 	@echo Benchmarking complete

doxy: Doxyfile
	@doxygen
	@echo Doxygen documentation generated

clean:
	del /Q $(TARGET).exe
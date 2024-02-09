.PHONY: compile run bench doxy clean

CC = gcc
# FLAGS = -Wall -Wextra -Werror -pedantic -std=c99 -O2
SRCS = src/*.c src/in/*.c src/in/parsers/*.c src/engine/*.c src/engine/mesh/*.c src/engine/methods/*.c src/engine/schemes/*.c src/out/*.c
LIBS = src/utils/algebra/*.c src/utils/cJSON/*.c  src/utils/custom_file/*.c src/utils/log/*.c
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
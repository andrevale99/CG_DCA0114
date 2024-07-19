GCC = gcc
FLAGS = -Wall -lglut -lGLU -lGL

OUT = Planeta.out
MAIN = main.c

all: compile clear

compile: $(MAIN)
	$(GCC) $(MAIN) -o $(OUT) $(FLAGS)

clear:
	@rm $(OUT)

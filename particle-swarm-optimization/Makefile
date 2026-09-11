# Makefile for Particle Swarm Optimization

CC = gcc
CFLAGS = -Wall -O3 -std=gnu99
EXECUTABLE = pso
SRC = main.c PSO.c OF.c
OBJ = $(SRC:.c=.o)

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $(OBJ) -lm

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(EXECUTABLE)

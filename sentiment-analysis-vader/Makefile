# Makefile for VADER Sentiment Analysis in C

CC = gcc
CFLAGS = -Wall -Wextra -std=gnu99
EXECUTABLE = vaderSentiment
SRC = main.c vaderSentiment.c
HDR = utility.h
OBJ = $(SRC:.c=.o)

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $(OBJ) -lm

%.o: %.c $(HDR)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(EXECUTABLE)

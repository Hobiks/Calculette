# Makefile for Simple Calculator

CC = g++
CFLAGS = -Wall -g

all: calculator

calculator: calculator.o
	$(CC) -o calculator calculator.o

calculator.o: calculator.cpp
	$(CC) $(CFLAGS) -c calculator.cpp

clean:
	rm -f *.o calculator

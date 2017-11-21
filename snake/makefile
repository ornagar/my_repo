RM = /bin/rm -f
CC = g++ 
CFLAGS = -std=c++11 -Wall -pedantic -D_DEBUG -g

snake :
	 $(CC) $(CFLAGS) main.cpp -lGL -lGLU -lglut  -o snake 

.PHONY : clean
clean :
	$(RM) snake

.PHONY: all
all: snake

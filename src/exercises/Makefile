RM = /bin/rm -f
CC = gcc 
CFLAGS = -std=c89 -ansi -Wall -pedantic -Werror -D_DEBUG -g

OBJS = bursa.o ws2_test.o ws2_string.o ws5_exercize.o ws6.o ws9.o \
final_test_c.o ws1.o ws2_test.o ws5_funcs.o ws7.o ws9.o \
ws2_exercizes.o ws3.o ws8.o ws9_test.o \
milion_chars.o ws2_string.o ws4.o ws5_main.o ws9_assignments.o 

ws1.out : ws1.o
	 $(CC) $(CFLAGS) ws1.o -o ws1.out 

ws2_string.out : ws2_string.o ws2_test.o 
	$(CC) $(CFLAGS) ws2_string.o ws2_test.o -o ws2_string.out

ws2_exercizes.out : ws2_exercizes.o
	$(CC) $(CFLAGS) ws2_string.o ws2_test.o -o ws2_exercizes.out

ws3.out : ws3.o
	 $(CC) $(CFLAGS) ws3.o -o ws3.out 

ws4.out : ws4.o
	 $(CC) $(CFLAGS) ws4.o -o ws4.out 

ws5.out : ws5_main.o ws5_funcs.o
	 $(CC) $(CFLAGS) ws5_main.o ws5_funcs.o -o ws5.out 

ws6.out : ws6.o
	 $(CC) $(CFLAGS) ws6.o -o ws6.out 

ws7.out : ws7.o
	 $(CC) $(CFLAGS) ws7.o -o ws7.out 

ws8.out : ws8.o
	 $(CC) $(CFLAGS) ws8.o -o ws8.out 

ws9.out : ws9.o ws9_test.o
	 $(CC) $(CFLAGS) ws9.o ws9_test.o -o ws9.out 

ws9_assignments.out : ws9_assignments.o 
	 $(CC) $(CFLAGS) ws9_assignments.o -o ws9_assignments.out 

milion_chars.out : milion_chars.o
	 $(CC) $(CFLAGS) milion_chars.o -o milion_chars.out 

bursa.out : bursa.o
	 $(CC) $(CFLAGS) bursa.o -o bursa.out 

final_test_c.out : final_test_c.o
	 $(CC) $(CFLAGS) final_test_c.o -o final_test_c.out 

ws2_test.o: ws2_test.c ws2_string.h
	 $(CC) $(CFLAGS) -c ws2_test.c

ws2_string.o: ws2_string.c ws2_string.h
	$(CC) $(CFLAGS) -c ws2_string.c

depends :
	$(CC) -MM $(OBJS:.o=.c) > depends

include depends

.PHONY : clean
clean :
	$(RM) *.out 

.PHONY: all
all: final_test_c.out bursa.out milion_chars.out \
	 ws9_assignments.out ws9.out ws8.out ws7.out ws6.out ws6.out ws5.out \
	 ws4.out ws3.out ws2_exercizes.out ws2_string.out ws1.out

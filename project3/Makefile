CC  = gcc
CFLAGS = -g -Wall
OBJS = indexPage.o crawler.o

all: webSearch
webSearch: webSearch.c $(OBJS)
	$(CC) $(CFLAGS) $(ObJS) $< -o $@
%.o: %.c $.h
	$(CC) $(CFLAGS) -c $< -o $@
clean:
	rm *.o *~ webSearch
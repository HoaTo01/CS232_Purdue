CC  = gcc
CFLAGS = -g -Wall
OBJS = indexPage.o crawler.o tf_idf.o

all: webSearch
webSearch: webSearch.c $(OBJS)
	$(CC) $(CFLAGS) $(ObJS) $< -o $@ -lm
%.o: %.c $.h
	$(CC) $(CFLAGS) -c $< -o $@
clean:
	rm *.o webSearch
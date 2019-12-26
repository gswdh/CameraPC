CC = gcc

CFILES = main.c 

CFLAGS = -O0 -o cam -L./ftd2xx -I. -D _WIN32 
LIBS = ftd2xx.lib

all:
	$(CC) $(CFILES) $(LIBS) $(CFLAGS)

clean:
	rm -f cam *.o
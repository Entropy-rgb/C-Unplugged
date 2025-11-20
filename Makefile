CC = gcc
CFLAGS = -Wall -Wextra -g

OBJ = C-Unplugged.o Songs.o Albums.o Playlist.o Logging.o Utils.o

all: c-unplugged

c-unplugged: $(OBJ)
	$(CC) $(CFLAGS) -o c-unplugged $(OBJ)

C-Unplugged.o: C-Unplugged.c C-Unplugged.h Songs.h Albums.h Playlist.h Logging.h Utils.h
	$(CC) $(CFLAGS) -c C-Unplugged.c

Songs.o: Songs.c Songs.h
	$(CC) $(CFLAGS) -c Songs.c

Albums.o: Albums.c Albums.h
	$(CC) $(CFLAGS) -c Albums.c

Playlist.o: Playlist.c Playlist.h
	$(CC) $(CFLAGS) -c Playlist.c

Logging.o: Logging.c Logging.h
	$(CC) $(CFLAGS) -c Logging.c

Utils.o: Utils.c Utils.h
	$(CC) $(CFLAGS) -c Utils.c

clean:
	rm -f *.o c-unplugged

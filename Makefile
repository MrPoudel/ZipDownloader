
CC=gcc
CFLAGS=-g -Wall

BIN=downloader

all: $(BIN)

%: %.c 
	$(CC) $(CFLAGS) $< -o $@ -lcurl

clean:
	$(RM) -rf $(BIN) *.o *.zip
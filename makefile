CC=gcc
#CFLAGS=-Wall
CFLAGS=

nova7Mixer: Nova7MixController.c
	$(CC) $(CFLAGS) -o nova7Mixer Nova7MixController.c

clean: 
	-rm nova7Mixer

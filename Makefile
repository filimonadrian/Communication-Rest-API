CC=g++
CFLAGS=-I -std=c++11.
SOURCES=client.cpp requests.cpp helpers.cpp buffer.cpp

client: $(SOURCES)
	$(CC) -o client $(SOURCES) -Wall

run: client
	./client

clean:
	rm -f *.o client

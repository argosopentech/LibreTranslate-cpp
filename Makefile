CC = g++

CXXFLAGS = -pthread

TARGET = libretranslate

all:
	$(CC) -o $(TARGET) main.cpp $(CXXFLAGS)

sync:
	$(CC) -o sync sync_client.cpp $(CXXFLAGS)

clean:
	$(RM) $(TARGET)

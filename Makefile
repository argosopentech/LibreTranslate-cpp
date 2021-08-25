CC = g++

CXXFLAGS = -lcurl

TARGET = libretranslate

all:
	$(CC) -o $(TARGET) main.cpp $(CXXFLAGS)

clean:
	$(RM) $(TARGET)

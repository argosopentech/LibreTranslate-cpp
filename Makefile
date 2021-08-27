CC = g++

CXXFLAGS = -std=c++17 -lcurl

TARGET = libretranslate

all:
	$(CC) -o $(TARGET) main.cpp LibreTranslate.h LibreTranslate.cpp $(CXXFLAGS)

clean:
	$(RM) $(TARGET)

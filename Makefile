CC = g++

CXXFLAGS = -lcurl

TARGET = libretranslate

all:
	$(CC) -o $(TARGET) main.cpp LibreTranslate.h $(CXXFLAGS)

clean:
	$(RM) $(TARGET)

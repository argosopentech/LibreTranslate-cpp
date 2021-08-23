CC = g++

TARGET = libretranslate

all:
	$(CC) -o $(TARGET) main.cpp

clean:
	$(RM) $(TARGET)

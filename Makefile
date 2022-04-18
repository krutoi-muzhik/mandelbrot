TARGET = mandelbrot
BOOST = MandelbrotBoost
CC = gcc
GLLIBS = -lopengl32 -lglfw3 -lgdi32 -lglew32

.PHONY: boost

all: $(TARGET)

boost: main.c $(BOOST).c $(TARGET).h
	$(CC) main.c $(BOOST).c $(GLLIBS) -o $(TARGET).exe

$(TARGET): $(TARGET).c $(TARGET).h
	$(CC) main.c $(TARGET).c $(GLLIBS) -o $(TARGET).exe

run:
	./$(TARGET).exe

clean:
	del $(TARGET).exe

MAIN=main.c
EXEC=main
FLAGS=-lSDL2 -lSDL2_image -l wiringPi

run: $(EXEC)
	./$(EXEC)

$(EXEC): $(MAIN)
	gcc -o $(EXEC) $(MAIN) $(FLAGS)

clean:
	rm -rf $(EXEC)
CC = g++
CFLAGS = -std=c++11 -Wall -Wextra -pedantic

main: main.o robot.o maze.o
	$(CC) $(CFLAGS) $^ -o $@

main.o: main.cpp robot.hpp maze.hpp
	$(CC) $(CFLAGS) -c $< -o $@

robot.o: robot.cpp robot.hpp maze.hpp
	$(CC) $(CFLAGS) -c $< -o $@

maze.o: maze.cpp maze.hpp
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f main *.o

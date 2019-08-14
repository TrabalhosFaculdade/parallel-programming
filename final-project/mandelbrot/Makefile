FLAGS=-O3 -std=c++11 -march=native -fopenmp

CXX=g++

RM=rm -f

EXEC=mandelbrot

all: $(EXEC)

$(EXEC):
	$(CXX) $(FLAGS) $(EXEC).cpp -c -o $(EXEC).o
	$(CXX) $(FLAGS) $(EXEC).o -o $(EXEC)
	# $(CXX) $(FLAGS) mandelbrot.c -o $(EXEC)

cpp:
	$(CXX) $(FLAGS) $(EXEC).cpp -c -o $(EXEC).o
	$(CXX) $(FLAGS) $(EXEC).o -o $(EXEC)

clean:
	$(RM) $(EXEC).o $(EXEC) 
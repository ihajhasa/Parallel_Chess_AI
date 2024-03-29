OUTPUTDIR := bin/

#-std=c++14
CFLAGS := -std=c++11

ifeq (,$(CONFIGURATION))
	CONFIGURATION := minimax
endif

ifeq (debug,$(CONFIGURATION))
CFLAGS += -g
else
CFLAGS += -O2 -fopenmp
endif

SOURCES := src/*.cpp
HEADERS := src/*.h

TARGETBIN := test-$(CONFIGURATION)

.SUFFIXES:
.PHONY: all clean

all: $(TARGETBIN)

$(TARGETBIN): $(HEADERS)
	$(CXX) -o $@ $(CFLAGS) $(SOURCES) 

clean:
	rm -rf ./test-$(CONFIGURATION)

board:
	g++ -std=c++11 -O2 -o test_board src/Test\ Files/test_board.cpp src/board_rep.cpp

openmpai:
	g++ -std=c++11 -O2 -o test_openmp_minimax src/Test\ Files/test_minimax_openmp.cpp src/minimax_openmp.cpp src/gen_moves.cpp src/board_rep.cpp

game:
	g++ -std=c++11 -O2 -o run_game src/Test\ Files/game.cpp src/minimax.cpp src/minimax_openmp.cpp src/gen_moves.cpp src/board_rep.cpp

time:
	g++ -std=c++11 -O2 -o time src/Test\ Files/timing_ai.cpp src/minimax.cpp src/minimax_openmp.cpp src/gen_moves.cpp src/board_rep.cpp


aileakcheck:
	g++ -std=c++11 -O2 -o memory_ai_openmp src/Test\ Files/timing_ai.cpp src/minimax.cpp src/minimax_openmp.cpp src/gen_moves.cpp src/board_rep.cpp
	valgrind --leak-check=full --track-origins=yes ./memory_ai_openmp

FILES = src/*.cpp \
		src/*.h

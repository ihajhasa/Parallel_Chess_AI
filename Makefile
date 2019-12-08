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

game:
	g++ -o run_game src/Test\ Files/game.cpp src/minimax.cpp src/board_rep.cpp

FILES = src/*.cpp \
		src/*.h

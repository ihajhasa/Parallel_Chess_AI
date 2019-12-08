OUTPUTDIR := bin/

#-std=c++14
CFLAGS := -std=c++11 -fvisibility=hidden -lpthread

ifeq (,$(CONFIGURATION))
	CONFIGURATION := minimax-first-move
endif

SOURCES := src/*.cpp
HEADERS := src/*.h

TARGETBIN := test-$(CONFIGURATION)

.SUFFIXES:
.PHONY: all clean

all: $(TARGETBIN)

$(TARGETBIN): $(SOURCES) $(HEADERS)
	$(CXX) -o $@ $(CFLAGS) $(SOURCES) 

clean:
	rm -rf ./test-$(CONFIGURATION)

check:	default
	./checker.pl

FILES = src/*.cpp \
		src/*.h

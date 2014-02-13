CPPFLAGS=-std=c++11 -g -Wall -Wextra -pedantic $(OPTFLAGS)
CPPFLAGS_MORE=-Isrc
LIBS=-ldl $(OPTLIBS)
PREFIX?=usr/local
CC=g++

SOURCES=$(wildcard src/**/*.cpp src/*.cpp)
OBJECTS=$(patsubst %.cpp,%.o,$(SOURCES))
HEADERS=$(patsubst %.cpp,%.h,$(SOURCES))

TEST_SRC=$(wildcard tests/prog3B.cpp)
TESTS=$(patsubst %.cpp,%,$(TEST_SRC))

TARGET=build/libprog3b.a
SO_TARGET=$(patsubst %.a,%.so,$(TARGET))

# target: all       Default target. Creates all the important files.
all: $(TARGET) $(SO_TARGET)

$(TARGET): CPPFLAGS += -fPIC
$(TARGET): build $(OBJECTS)
	ar rcs $@ $(OBJECTS)
	ranlib $@

$(SO_TARGET): $(TARGET) $(OBJECTS)
	$(CC) -shared -std=c++11 -o $@ $(OBJECTS)

# target: build     Create the build and bin directories
build:
	mkdir -p build
	mkdir -p bin

# target: tests     Compile the test code.
# This needs to run `g++ -std=c++11 -g -Wall -Wextra -pedantic -o tests/prog3B tests/prog3B.cpp build/libprog3b.a -Isrc'
.PHONY: tests
#tests: CPPFLAGS += $(TARGET)
#tests: $(TESTS) $(CPPFLAGS_MORE)
#	mv tests/prog3B bin/prog3B
tests:
	g++ -std=c++11 -g -Wall -Wextra -pedantic -o tests/prog3B tests/prog3B.cpp build/libprog3b.a -Isrc
	mv tests/prog3B bin/prog3B

# target: clean     Remove the compiled files.
.PHONY: clean
clean:
	rm -rf build $(OBJECTS) $(TESTS)
	find . -name "*.gc*" -exec rm {} \;
	find . -name "*.*~" -exec rm {} \;
	rm -rf `find . -name "*.dSYM" -print`
	rm -rf **/test test

# target: install   Install the library to the prefixed directory.
.PHONY: install
install: all
	install -d $(DESTDIR)/$(PREFIX)/lib/
	install $(TARGET) $(DESTDIR)/$(PREFIX)/lib/
	echo Installed to $(DESTDIR)/$(PREFIX)/lib

# target: help      List the available targets
help:
	egrep "^# target:" [Mm]akefile

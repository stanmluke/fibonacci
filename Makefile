CC=g++
CFLAGS=-c -Wall -I/usr/local/lib
LDFLAGS=-lmicrohttpd

SOURCES=httphandler.cpp api.cpp executor.cpp fibo.cpp
OBJECTS=$(SOURCES:.cpp=.o)
TEST_SOURCES=tests/test_fibo.cpp fibo.cpp executor.cpp
TEST_OBJECTS=$(TEST_SOURCES:.cpp=.o)

all: $(SOURCES) $(TEST_SOURCES) fibo_api tests/test_fibo
    
fibo_api: $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

tests/test_fibo: $(TEST_OBJECTS)
	$(CC) $(LDFLAGS) $(TEST_OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean: 
	rm -rf *.o fibo_api tests/test_fibo

#g++ ./tests/test_fibo.cpp fibo.cpp executor.cpp -o ./tests/test_fibo
#g++ httphandler.cpp api.cpp executor.cpp fibo.cpp -o fibo_api -I /usr/local/lib -lmicrohttpd


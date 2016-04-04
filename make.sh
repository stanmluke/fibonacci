
g++ ./tests/test_fibo.cpp fibo.cpp executor.cpp -o ./tests/test_fibo
g++ httphandler.cpp api.cpp executor.cpp fibo.cpp -o fibo_api -I /usr/local/lib -lmicrohttpd


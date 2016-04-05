#include <errno.h>
#include <stdio.h>
#include <iostream>
#include <vector>
#include <sstream>

#include <stdint.h>
#include "executor.hpp"

extern int fibo_memoize(unsigned n, uint64_t &fn);
using namespace ourapi;


Executor::Executor()
{
}

bool 
Executor::fibonacci(const string& val,
        string& response)
{
    char *endc;
    int fibo_index = strtol(val.c_str(), &endc, 10);
    if (errno || (*endc != '\0') || (fibo_index < 0)) {
	std::cout << "invalid input:" << val.c_str() << ", errno=" << errno << std::endl;
	return false;
    }
    std::cout << "Fibonacci numbers for n=" << fibo_index << std::endl;
    string output;
    std::ostringstream osstr;
    int err;
    for (int i=0; i<fibo_index; i++) {
	uint64_t fn;
	if (i != 0) { //separator after each number, except first and last
		osstr << ", ";
	}
	/* NB: possibly this can exceed string output, for large index */
        if (0 == (err = fibo_memoize(i, fn))) {
		osstr << fn;
	} else {
		std::cout << "fibo call fails=" << err << std::endl;
		return false;
	}
    }

    _generateOutput(osstr.str(), response);
    std::cout << response << std::endl;
    return true;
}

void 
Executor::_generateOutput(string data, string& output)
{
#define HEADER "<html><head><title>Fibonacci values</title></head><body>"
#define FOOTER "</body></html>"
	output = HEADER + data + FOOTER;
	return;
}

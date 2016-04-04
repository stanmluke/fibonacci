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
Executor::fibonacci(const string& val, outputType type, 
        string& response)
{
    bool pingtest = false;
    bool do_fibo  = false;

    char *endc;
    int fibo_index = strtol(val.c_str(), &endc, 10);
    if (*endc != '\0') {
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

    _generateOutput(osstr.str(), TYPE_XML, response);
    std::cout << response << std::endl;
    return true;
}

void 
Executor::_generateOutput(string data, outputType type, string& output)
{
    /* only TYPE_XML supported for now */

    string xml_head("<?xml version=\"1.0\"?>\n"
		"<xs:schema xmlns:xs=\"http://www.w3.org/2001/XMLSchema\">\n"
		"<xs:element name=\"ulongvalues\" type=\"valuelist\"/>\n"
		"<xs:simpleType name=\"valuelist\">\n"
		"\t<xs:list itemType=\"xs:unsignedLong\"/>\n"
		"</xs:simpleType>\n");
    string xml_foot("</xs:schema>\n");
    string val_head("<ulongvalues>");
    string val_foot("</ulongvalues>");
    if (TYPE_JSON == type) {
        //write_json(ostr, data);
    } else if (TYPE_XML == type) {
	output = xml_head + val_head + data + val_foot + xml_foot;
    }
    return;
}

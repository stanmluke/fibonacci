#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <string.h>
#include <microhttpd.h>
#include "api.hpp"

using namespace std;
using namespace ourapi;

struct validate_data {
    string api;
    vector<string> fields;
};

vector<string> 
split(string str, char delim) {
   vector<string> internal;
   stringstream ss(str);
   string tok;

   while(getline(ss, tok, delim)) {
	if (tok.size() != 0)
 	    internal.push_back(tok);
   }
   for (int i=0; i<internal.size(); i++) {
	std::cout << "split[" << i << "]=" << internal[i] << std::endl;
   }
   return internal;
}

api::api()
{
}

unsigned int 
api::executeAPI(const string& url, const map<string, string>& argvals, string& response)
{
    validate_data vdata ;
    vdata.api = url;
    vdata.fields = split(url, '/');

    if ( !_validate(&vdata)) {
        _getInvalidResponse(response);
        return MHD_HTTP_BAD_REQUEST;
    }

    return _executeAPI(vdata.fields[0], vdata.fields[1], response);
}

unsigned int 
api::_executeAPI(const string& urlobj, const string& val, 
		string& response)
{
    unsigned int ret = MHD_HTTP_OK;
    bool did_fib = false;
    std::cout  << "DEBUG_executeAPI urlobj=" << urlobj << std::endl;
    if (urlobj == "fibonacci") {
        did_fib = _executor.fibonacci(val, response);
	if (false == did_fib) {
		_getInvalidResponse(response);
		return MHD_HTTP_BAD_REQUEST;
	}
    } else {
        _getInvalidResponse(response);
        return MHD_HTTP_BAD_REQUEST;
    }

    return ret;
}

/* verify REST API is in expected format, tokenized in vdata.fields
 * expected api format:
 *    /fibonacci/<n>
 * - field#1: only allowable object is "fibonacci"
 * - field#2: must be numeric, and specifies number of fibo series to calc
 * no other fields allowed`
 */
bool 
api::_validate(const void *data)
{
    string fobject("fibonacci");
    const validate_data *vdata = static_cast<const validate_data *>(data );
    std::cout  << "DEBUG_validate api=" << vdata->api << std::endl;

    if (2 != vdata->fields.size()) { 
 	return false; /* must be fibonacci and number */
    }
    std::cout << "DEBUG_validate field=" << vdata->fields[0] << std::endl;
    if (fobject != vdata->fields[0]) {
        return false;
    }

    char *endc = NULL;
    errno = 0;
    int fibo_index = strtol(vdata->fields[1].c_str(), &endc, 10);
    if ((0 != errno) || *endc != '\0') { 
	std::cout << "DEBUG_validate fails errno=" << errno << 
		" endc=" << *endc << std::endl;
	return false; /* not valid numeric */
    }
    std::cout << "DEBUG_validate val=" << vdata->fields[1] << 
		"(" << fibo_index << ")" << std::endl;
    return true;
}

void 
api::_getInvalidResponse(string& response)
{
    response = "<html><head><title>Invalid Request</title></head><body>requested value is invalid</body></html>";
}


#include <iostream>
#include <sstream>
#include <errno.h>
#include <stdlib.h>

#include "../executor.hpp"

using namespace std;
extern int fibo_memoize(unsigned n, uint64_t &fn);

/* primitive input handling, but it was non-iteresting.
 */
int 
main(int argc, char*argv[])
{
    ourapi::Executor _executor;
    char *endc;
    if (argc < 2) {
	cout << "count missing" << endl;
	return EINVAL;
    }
    int fibo_index = strtol(argv[1], &endc, 10);
    if (errno || *endc != '\0') {
	cout << "invalid input:" << argv[1] << ", errno=" << errno << endl;
	return EINVAL;
    }
    int ret = 0;
    string response;
    ret = _executor.fibonacci(argv[1], ourapi::Executor::TYPE_XML, response);
    
    return 0;
}

#ifndef __EXECUTOR_FOR_API__
#define __EXECUTOR_FOR_API__

#include <string>
#include <set>

using std::string;
using std::set;

namespace ourapi
{

class Executor
{   
public:
    enum outputType {
        TYPE_JSON, TYPE_XML   
    };
    Executor();
    bool fibonacci(const string& val, string& response);
private:
    void _generateOutput(string data, string& output);

};



}  // namespace ourapi

#endif

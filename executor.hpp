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
    bool fibonacci(const string& val, outputType type, string& response);
private:
    void _generateOutput(string data, outputType type, string& output);

};



}  // namespace ourapi

#endif

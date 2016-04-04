#ifndef __API_FOR_REST_FIBONACCI__
#define __API_FOR_REST_FIBONACCI__

#include <map>
#include <string>
#include <set>
#include "executor.hpp"

using std::map;
using std::string;
using std::set;

namespace  ourapi
{

class api
{
public:
    api();
    bool executeAPI(const string& url, const map<string, string>& argval, 
            string& response);
private:
    Executor _executor;
    bool _validate(const void*  data);
    bool _executeAPI(const string& urlobj, const string& val, 
            Executor::outputType type, string& response);
    void _getInvalidResponse(string& response);
};

} // namespace ourapi ends

#endif //__API_FOR_REST_FIBONACCI__

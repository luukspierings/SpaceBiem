#pragma once


#include <list>
#include <string>

using std::string;
using std::list;

namespace spacebiem
{
    class SaveBlobEntityComponentBuilder
    {
    public:
        SaveBlobEntityComponentBuilder();

        void prepare(string pComponentName);
        void addValue(string value);
        string build();

    private:
        string componentName;
        list<string> values;
    };
}

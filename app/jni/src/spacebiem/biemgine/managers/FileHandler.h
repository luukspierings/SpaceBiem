#pragma once

#include <string>
#include <vector>
#include <map>

#include <iostream>
#include <fstream>
#include <sstream>

using std::fstream;
using std::istringstream;
using std::ios_base;
using std::vector;
using std::string;

namespace biemgine
{
    class FileHandler
    {
    public:
        FileHandler(string filePath, bool overwrite = false);
        FileHandler() {};
        ~FileHandler() { close(); };

        vector<vector<string>> getValues();
        void writeLine(vector<string> values);
        void writeLine(string value);

        bool remove(string filePath);
        static bool exists(string filePath);

        void close();

    private:
//        fstream currentFile;
        string currentPath;

        char* read_file_string();
    };
}

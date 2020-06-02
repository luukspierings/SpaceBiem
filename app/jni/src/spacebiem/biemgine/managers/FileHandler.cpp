#include <sys/stat.h>
#include "FileHandler.h"
#include <SDL.h>

#include <android/log.h>
#define LOG(...) __android_log_print(ANDROID_LOG_WARN, "SPACEBIEM", __VA_ARGS__)

namespace biemgine
{
    string currentFile;
    bool fileModified;

    std::map<string, string> memoryFiles;

    char* file_read(std::string filename) {
        SDL_RWops *rw = SDL_RWFromFile(filename.data(), "rb");
        if (rw == NULL) return NULL;

        Sint64 res_size = SDL_RWsize(rw);
        char* res = (char*)malloc(res_size + 1);

        Sint64 nb_read_total = 0, nb_read = 1;
        char* buf = res;
        while (nb_read_total < res_size && nb_read != 0) {
            nb_read = SDL_RWread(rw, buf, 1, (res_size - nb_read_total));
            nb_read_total += nb_read;
            buf += nb_read;
        }
        SDL_RWclose(rw);
        if (nb_read_total != res_size) {
            free(res);
            return NULL;
        }

        res[nb_read_total] = '\0';
        return res;
    }

    void file_write(std::string fileName, std::string data){

        LOG("InternalStoragePath: %s", SDL_AndroidGetInternalStoragePath());
        LOG("ExternalStoragePath: %s", SDL_AndroidGetExternalStoragePath());

        std::string slash = "/";
        fileName = SDL_AndroidGetExternalStoragePath() + slash + fileName;

        LOG("Writing: %s", fileName.data());

        const char *str = data.data();
        SDL_RWops *rw = SDL_RWFromFile(fileName.data(), "wb");
        if(rw != NULL) {
            size_t len = SDL_strlen(str);
            if (SDL_RWwrite(rw, str, 1, len) != len) {
                LOG("Couldn't fully write string: %s", SDL_GetError());
            } else {
                LOG("Wrote blocks");
            }
            SDL_RWclose(rw);
        }
        else{
            LOG("RW is null: %s", SDL_GetError());
        }
    }

    char* FileHandler::read_file_string(){

        LOG("Reading: %s", currentPath.data());

        char* fileContent = nullptr;

//        if ( memoryFiles.find(currentPath) != memoryFiles.end() ) {
//            LOG("READING FILE FROM MEMORY");
//            fileContent = memoryFiles[currentPath];
//        } else {
            LOG("READING FILE FROM EXTERNAL");

            std::string slash = "/";
            std::string fileName = SDL_AndroidGetExternalStoragePath() + slash + currentPath;
            fileContent = file_read(fileName);

            LOG("CONTENT: %s", fileContent);

            if(fileContent == NULL){
                LOG("READING FILE FROM DISC");
                fileContent = file_read(currentPath.data());

                LOG("CONTENT: %s", fileContent);
            }
//        }

        return fileContent;
    }


    FileHandler::FileHandler(string filePath, bool overwrite)
    {
//        if (overwrite) {
//            currentFile.open(filePath, fstream::in | fstream::out | fstream::trunc);
//        }
//        else {
//            currentFile.open(filePath, fstream::in | fstream::out | fstream::app);
//        }
        currentPath = filePath;

        if(overwrite){
            currentFile = "";
        }
        else{
            char* fileContent = read_file_string();
            if(fileContent != nullptr)
                currentFile = std::string(fileContent);
            else
                currentFile = "";
        }

    }

    vector<vector<string>> FileHandler::getValues()
    {
        LOG("GOING TO READ: %s", currentPath.data());

        char* fileContent = read_file_string();

        vector<vector<string>> values;
        vector<string> line;
        string value;

        std::stringstream ss(fileContent);

        for (string i; ss >> i;) {
            LOG("HANDLING FILE VAL: %s", i.data());

            string delim = ",";
            i += delim;
            auto start = 0U;
            auto end = i.find(delim);
            while (end != std::string::npos)
            {
                string val = i.substr(start, end - start);

                LOG("HANDLING SPLIT FILE VAL: %s", val.data());

                line.push_back(val);

                start = end + delim.length();
                end = i.find(delim, start);
            }
//            LOG("HANDLING SPLIT FILE END: %s", val.data());

            values.push_back(line);
            line.clear();
        }

        LOG("DONE WITH READING");

        return values;
    }

    void FileHandler::writeLine(vector<string> values)
    {

        fileModified = true;

        for (auto v = values.begin(); v != values.end(); v++) {
            LOG("WRITING LINE VALUES: %s", v);

            if (v != values.begin()) {
                currentFile += ",";
            }
            currentFile += *v;
        }
        currentFile += "\n";
    }

    void FileHandler::writeLine(string value)
    {
        LOG("WRITING LINE: %s", value.data());

        fileModified = true;
        currentFile += value + "\n";

        LOG("FINISHED WRITING LINE");
    }

    bool FileHandler::remove(const string filePath)
    {
//        const char *str = filePath.c_str();
//        return std::remove(str);
        return true;
    }

    bool FileHandler::exists(const string filePath)
    {
//        struct stat buffer;
//        return (stat(filePath.c_str(), &buffer) == 0);
        return true;
    }
    void FileHandler::close()
    {
        if(fileModified){
            memoryFiles[currentPath] = currentFile;
            file_write(currentPath, currentFile);
            fileModified = false;
        }
//        currentFile.close();
    }
}

#pragma once

#include <string>

namespace MarkTwo
{
    struct FileUtilities
    {
        static std::string read_file(const char* filePath)
        {
            // standard C library file, lot faster than fstream
            FILE* file;
            fopen_s(&file, filePath, "rt"); //read in as text file
            fseek(file, 0, SEEK_END);
            unsigned long fileLength = ftell(file);

            char* data = new char[fileLength + 1]; // add termination character
            memset(data, 0, fileLength + 1);
            fseek(file, 0, SEEK_SET); // reset position

            fread(data, 1, fileLength, file);
            fclose(file);

            std::string result(data);
            delete[] data;
            return result;
        }
        
        static char* read_file_to_char(const char* filePath)
        {
            // standard C library file, lot faster than fstream
            FILE* file;
            fopen_s(&file, filePath, "rt"); //read in as text file
            fseek(file, 0, SEEK_END);
            unsigned long fileLength = ftell(file);

            char* data = new char[fileLength + 1]; // add termination character
            memset(data, 0, fileLength + 1);
            fseek(file, 0, SEEK_SET); // reset position

            fread(data, 1, fileLength, file);
            fclose(file);

            return data;
        }


    };
}

#ifndef CUSTOMTYPES_H_
#define CUSTOMTYPES_H_

#include <vector>
#include <string>

/////////////////////////////////////////////////////////////
// New Type Definitions
/////////////////////////////////////////////////////////////

struct Dir {
    /*
    Dir holds the directory path which should be scraped
    */

    std::string pathToDir;

    Dir() {}
    Dir(std::string& path)
        : pathToDir(path) {}
};

struct File {
    /*
    File is describing a single file and its attributes
    */

    std::string name;
    std::string suffix;
    std::string location;
    float       size_of_file;

    File() {}
    File(std::string& name, std::string& suffix, std::string& location, float& size_of_file) 
        : name(name), suffix(suffix), location(location), size_of_file(size_of_file) {}
};

#endif
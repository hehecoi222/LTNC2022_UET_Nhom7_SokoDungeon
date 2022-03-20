// Header to define res path using SDL_GetBasePath()
// If the game has multiple directories for resources
// Code inspired by: https://www.willusher.io/sdl2%20tutorials/2014/06/16/postscript-0-properly-finding-resource-paths
// With the implementation class

#ifndef FIND_RES_H
#define FIND_RES_H

// stdio for logging errors, string for finding and concatenating paths, SDL for get errors and base path
#include <stdio.h>
#include <string>
#include <SDL.h>

// Class to find the path of the resource directory
class FindRes {
public:
    // Constructor
    FindRes();
    // Destructor
    ~FindRes();
    // Constructor with a subdir
    FindRes(const std::string& subdir);
    // operator+ for the path of object
    std::string operator+(const std::string& subPath) const;
private:
    // The path
    std::string path;
    // Get the base path
    std::string retPath(const std::string& path);
    // Get the path to the resource directory
    std::string resPath(const std::string& subPath = "");
};

FindRes::FindRes() {
    // Get the path without subdir
    path = resPath();
}

FindRes::~FindRes() {
    path.clear();
}

FindRes::FindRes(const std::string& subdir) {
    // Get the path with subdir
    path = resPath(subdir);
}

std::string FindRes::operator+(const std::string& subPath) const {
    // Return the path with subdir
    return path + subPath;
}

// Returns the path to the resource directory
// sub path for any sub directories inside the resource directory
std::string FindRes::resPath(const std::string& subPath) {
    char *basePath = SDL_GetBasePath();

    // if the base path is null, there was an error
    if (basePath == NULL) {
        printf("SDL_GetBasePath Error: %s\n", SDL_GetError());
        return "";
    }

    // Convert the base path to a string for concat and find
    path = basePath;

    // Platform-dependent
    #ifdef _WIN32
        // Windows
        path = retPath(path)  + "res" + "\\" + subPath + "\\";
    #else
        // Linux, Unix
        path = retPath(path)  + "res" + "/" + subPath + "/";
    #endif
    SDL_free(basePath);
    return path;

}

std::string FindRes::retPath(const std::string& path) {

    // Get the path to the resource directory if being run after build
    size_t pos = path.find("bin");

    // If not found, probably being debugged
    if (pos == std::string::npos) {
        pos = path.find("build");

        // If not found, probably being run at top level directory
        if (pos == std::string::npos) {
            return path;
        }
    }
    return path.substr(0, pos);
}
#endif
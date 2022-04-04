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
    FindRes() {
    // Get the path without subdir
    path = resPath();
    }
    // Destructor
    ~FindRes() {
    path.clear();
    }
    // Constructor with a subdir
    FindRes(const std::string& subdir) {
    // Get the path with subdir
    path = resPath(subdir);
    }
    // operator+ for the path of object
    std::string operator+(const std::string& subPath) const {
        // Return the path with subdir
        return path + subPath;
    }
    static char* getPath(const std::string& subdir, const std::string& file) {
        // Get the path to the resource directory
        FindRes res(subdir);
        // Concat the path to the file
        std::string path = res + file;
        // Allocate memory for the path
        char* pathC = new char[path.length() + 1];
        // Copy the path to the allocated memory
        strcpy(pathC, path.c_str());
        // Return the path
        return pathC;
    }
    
private:
    // The path
    std::string path;
    // Get the base path
    std::string retPath(const std::string& path) {
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
    // Get the path to the resource directory
    std::string resPath(const std::string& subPath = "") {
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
};

#endif
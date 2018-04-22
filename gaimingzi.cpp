
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <algorithm>
#include <string>
#include <vector>

#include "common.h"
#include "alphanum.hpp"

//
// gaimingzi A pattern
//
// A can be folder path or file list
// pattern can be IMG_%d.JPG
// %d stands for index number
//

int main(int argc, char** argv)
{
    if (argc != 3)
    {
        fprintf(stderr, "Usage: %s [A] [pattern]\n", argv[0]);
        return -1;
    }

    const char* a = argv[1];
    const char* p = argv[2];

    // load
    std::vector<std::string> alist = load_file_list_or_folder_path(a);

    // sort
    std::sort(alist.begin(), alist.end(), doj::alphanum_less<std::string>());

    // dump
    for (size_t i=0; i<alist.size(); i++)
    {
        char newname[256];
        sprintf(newname, p, i);

//         fprintf(stderr, "%16s -> %s\n", alist[i].c_str(), newname);

        std::string oldpath = a + alist[i];
        std::string newpath = a + std::string(newname);

        fprintf(stderr, "%16s -> %s\n", oldpath.c_str(), newpath.c_str());
    }

    return 0;
}


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <algorithm>
#include <string>
#include <vector>

#include "common.h"
#include "alphanum.hpp"

//
// bijiao A B
//
// A and B can be folder path or file list
//
// example
// bijiao A.txt B.txt
// bijiao A.txt /home/nihui/B
// bijiao /home/nihui/A /home/nihui/B
//
// output
// A-list.txt
// B-list.txt
// A-B-dou-you.txt
// A-you-B-meiyou.txt
// B-you-A-meiyou.txt
//

int main(int argc, char** argv)
{
    if (argc != 3)
    {
        fprintf(stderr, "Usage: %s [A] [B]\n", argv[0]);
        return -1;
    }

    const char* a = argv[1];
    const char* b = argv[2];

    // load
    std::vector<std::string> alist = load_file_list_or_folder_path(a);
    std::vector<std::string> blist = load_file_list_or_folder_path(b);

    // sort
    std::sort(alist.begin(), alist.end(), doj::alphanum_less<std::string>());
    std::sort(blist.begin(), blist.end(), doj::alphanum_less<std::string>());

    // dump
    fprintf(stderr, "%5d in A-list.txt\n", (int)alist.size());
    fprintf(stderr, "%5d in B-list.txt\n", (int)blist.size());
    dump_list_file("A-list.txt", alist);
    dump_list_file("B-list.txt", blist);

    // compare
    std::vector<std::string> a_b_douyou;
    std::vector<std::string> a_you_b_meiyou;
    std::vector<std::string> b_you_a_meiyou;

    size_t i=0;
    size_t j=0;
    while (i<alist.size() && j<blist.size())
    {
        if (alist[i] == blist[j])
        {
            a_b_douyou.push_back(alist[i]);
            i++;
            j++;
        }
        else if (alist[i] < blist[j])
        {
            a_you_b_meiyou.push_back(alist[i]);
            i++;
        }
        else// if (alist[i] > blist[j])
        {
            b_you_a_meiyou.push_back(blist[j]);
            j++;
        }
    }
    while (i<alist.size())
    {
        a_you_b_meiyou.push_back(alist[i]);
        i++;
    }
    while (j<blist.size())
    {
        b_you_a_meiyou.push_back(blist[j]);
        j++;
    }

    // dump
    fprintf(stderr, "%5d in A-B-dou-you.txt\n", (int)a_b_douyou.size());
    fprintf(stderr, "%5d in A-you-B-meiyou.txt\n", (int)a_you_b_meiyou.size());
    fprintf(stderr, "%5d in B-you-A-meiyou.txt\n", (int)b_you_a_meiyou.size());
    dump_list_file("A-B-dou-you.txt", a_b_douyou);
    dump_list_file("A-you-B-meiyou.txt", a_you_b_meiyou);
    dump_list_file("B-you-A-meiyou.txt", b_you_a_meiyou);

    return 0;
}

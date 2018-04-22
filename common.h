
#include <dirent.h>
#include <sys/types.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <algorithm>
#include <string>
#include <vector>

static std::vector<std::string> load_folder_path(const char* dirpath)
{
    std::vector<std::string> paths;

    DIR* dp = opendir(dirpath);
    if (!dp)
    {
        fprintf(stderr, "can not open directory %s\n", dirpath);
        return paths;
    }

    struct dirent* ep;
    while ((ep = readdir(dp)))
    {
        if (ep->d_type == DT_DIR)
        {
            if (strcmp(ep->d_name, ".") == 0 || strcmp(ep->d_name, "..") == 0)
                continue;

            char subdirpath[1024];
            sprintf(subdirpath, "%s/%s", dirpath, ep->d_name);

            std::vector<std::string> subpaths = load_folder_path(subdirpath);
            for (size_t i=0; i<subpaths.size(); i++)
            {
                paths.push_back(ep->d_name + std::string("/") + subpaths[i]);
            }
        }
        else
        {
            paths.push_back(ep->d_name);
        }
    }

    closedir(dp);

    return paths;
}

static std::vector<std::string> load_file_list(const char* listpath)
{
    std::vector<std::string> paths;

    FILE* fp = fopen(listpath, "rb");
    if (!fp)
    {
        fprintf(stderr, "can not open file %s\n", listpath);
        return paths;
    }

    char line[1024];
    while (!feof(fp))
    {
        int nscan = fscanf(fp, "%1023[^\r\n]%*[\r\n]", line);
        if (nscan != 1)
        {
            // skip empty line
            fscanf(fp, "%*[\r\n]");
            continue;
        }

        paths.push_back(line);
    }

    fclose(fp);

    return paths;
}

static bool is_txt_file(const char* path)
{
    int len = strlen(path);
    if (len <= 3)
        return false;

    const char* ext = path + strlen(path) - 4;
    return (strcmp(ext, ".txt") == 0);
}

static std::vector<std::string> load_file_list_or_folder_path(const char* path)
{
    return is_txt_file(path) ? load_file_list(path) : load_folder_path(path);
}

static void dump_list_file(const char* path, const std::vector<std::string>& list)
{
    FILE* fp = fopen(path, "wb");
    if (!fp)
    {
        fprintf(stderr, "can not open file %s\n", path);
        return;
    }

    for (size_t i=0; i<list.size(); i++)
    {
        fprintf(fp, "%s\n", list[i].c_str());
    }

    fclose(fp);
}

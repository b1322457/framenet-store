//
// Created by 王鹏飞 on 16/4/6.
//
#include <iostream>
#include <dirent.h>
#include <vector>
int main(){

    std::vector<std::string> listnames;
    DIR           *d;
    struct dirent *dir;
    d = opendir("/Users/wangpf/Downloads/fndata-1.6/frame");
    if (d)
    {
        while ((dir = readdir(d)) != NULL)
        {
            if (dir->d_name[0] == '.')
                continue;
            printf("%s\n", dir->d_name);
            listnames.push_back(dir->d_name);
        }
        closedir(d);
    }
    std::cout<<listnames[0]<<std::endl;
}
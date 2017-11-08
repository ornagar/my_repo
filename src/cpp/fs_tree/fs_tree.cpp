
#include <iostream>
#include <memory>

#include <dirent.h>
#include <exception>
#include <cstring>
#include "fs_tree.hpp"

namespace ilrd {
namespace fs_tree {

static char* path_to_name(const std::string& path);

File::File(const std::string& name): Entry(name) {}


Directory::Directory(const std::string& name)
	: Entry(name), m_entries(0) {}

void Directory::print(const std::string& pre) const 
{
    std::string p = pre;
    if(p.length() >= 3)
    {
        p.pop_back();
        p.pop_back();
        p.pop_back();
        
        std::cout << KCYN << pre << std::endl << p << "├──";
    }

    std::cout << KRED << get_name() << KCYN << std::endl;

    for (auto i : m_entries) {
        i->print(pre + "   │");
    }
}


std::shared_ptr<Entry> build_tree(const std::string& name, size_t* count_libs,
                                                            size_t* count_files)
{
    DIR *dir;
    struct dirent *entry;
    
    // If root is invalid or the user doesn't have permissions to open the
    // requested path, throw exception
    if (!(dir = opendir(name.c_str()))) 
        throw std::invalid_argument(name.c_str());
    
    char* str = path_to_name(name);
	std::shared_ptr<Directory> directory(new Directory(str));
    
    while ((entry = readdir(dir)) != nullptr) {
        if (entry->d_type == DT_DIR) {
            if (strcmp(entry->d_name, ".") == 0 || 
                strcmp(entry->d_name, "..") == 0) {
                continue;
            }
            DIR* temp;
            if (!(temp = opendir((name + '/' + entry->d_name).c_str())))
            { // If the user doesn't have permissions to open 
              // a specific directory, skip it and continue 
                closedir(temp);
                continue;
            }
            closedir(temp);
            ++(*count_libs);
            directory->add_entry(build_tree(name + '/' + entry->d_name, 
                                                      count_libs, count_files));
            
        } else if (entry->d_type == DT_REG){
            ++(*count_files);
            directory->add_entry(std::shared_ptr<Entry>
                                            (new File(entry->d_name)));
        }
    }
    closedir(dir);
    
    return directory;
}    

static char* path_to_name(const std::string& path)
{
    char* str = const_cast<char*>(path.c_str());
    char* begin = str;
    str += path.length() - 1;
    
    while (begin < str && *(str - 1) != '/') { 
        --str; 
    }
    return str;
}

}//namespace fs_tree
}//namespace ilrd

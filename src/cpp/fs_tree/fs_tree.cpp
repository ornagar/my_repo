
#include <iostream>
#include <memory>

#include <dirent.h>
#include <exception>
#include <cstring>
#include "fs_tree.hpp"

namespace ilrd {
namespace fs_tree {

File::File(const std::string& name): Entry(name) {}


Directory::Directory(const std::string& name)
	: Entry(name), m_entries(0) {}

void Directory::print(const std::string& pre) const 
{
    
    std::cout << pre << std::endl << pre << "___";
    printf("%s", KRED);
    std::cout << get_name() << std::endl;
    printf("%s", KCYN);
    for (auto i : m_entries) {
        i->print(pre + "   |");
    }
}


std::shared_ptr<Entry> build_tree(const std::string& name)
{
    /**************************************************************************/
    //TODO: try make it cleaner
    char* str = const_cast<char*>(name.c_str());
    char* begin = str;
    str += strlen(str) - 1;
    while (begin < str && *(str - 1) != '/') { --str; }
    /**************************************************************************/
    
	std::shared_ptr<Directory> directory(new Directory(str));
    DIR *dir;
    struct dirent *entry;

    if (!(dir = opendir(name.c_str())))
        throw std::invalid_argument(name.c_str());

    while ((entry = readdir(dir)) != nullptr) {
        if (entry->d_type == DT_DIR) {
            if (strcmp(entry->d_name, ".") == 0 || 
                strcmp(entry->d_name, "..") == 0) {
                continue;
            }

            directory->add_entry(build_tree(name + '/' + entry->d_name));
            
        } else if (entry->d_type == DT_REG){
            directory->add_entry(std::shared_ptr<Entry>
                                            (new File(entry->d_name)));
        }
    }
    closedir(dir);
    
    return directory;
}

}//namespace fs_tree
}//namespace ilrd

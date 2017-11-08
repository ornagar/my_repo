#include <exception>

#include "fs_tree.hpp"

using namespace ilrd;
using namespace fs_tree;

int main(int argc, char **argv)
{
    size_t count_libs = 0;
    size_t count_files = 0;
    int status = 0;
    std::string name = ".";
    if (argc > 1) {
        name = argv[1];
    }
    std::shared_ptr<Entry> entry;
    try  {
        entry = build_tree(name, &count_libs, &count_files);
        entry->print_tree();
    }catch (const std::exception& i) {
        std::cout << i.what() << " [error opening dir]"<< std::endl;
        status = 1;
    }
        
    
    std::cout << "\n" << count_libs << 
                        ((count_libs == 1) ? " directory, " : " directories, ")
       << count_files << ((count_files == 1) ? " file" : " files") << std::endl;
    
    return status;
}

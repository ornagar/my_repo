#include "fs_tree.hpp"

using namespace ilrd;
using namespace fs_tree;

int main(int argc, char **argv)
{
    std::string name = ".";
    if (argc > 1) {
        name = argv[1];
    }
    
    std::shared_ptr<Entry> entry = build_tree(name);
    if (entry) {
        entry->print_tree();
    }
    
    return 0;
}

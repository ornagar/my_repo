//
// fs_tree.hpp
//
//  Created on: Sep 26, 2017
//      Author: noname
//

#ifndef FS_TREE_HPP_
#define FS_TREE_HPP_

#include <iostream>
#include <memory>
#include <string>
#include <vector>

#define KNRM  "\x1B[0m"
#define KRED  "\x1B[31m"
#define KGRN  "\x1B[32m"
#define KYEL  "\x1B[33m"
#define KBLU  "\x1B[34m"
#define KMAG  "\x1B[35m"
#define KCYN  "\x1B[36m"
#define KWHT  "\x1B[37m"


namespace ilrd {

namespace fs_tree {
class Entry;

std::shared_ptr<Entry> build_tree(const std::string& root); //throws bad_alloc, more?

class Entry {
public:
    explicit inline Entry(const std::string& name); //throws bad_alloc
    virtual ~Entry() noexcept = default;
    Entry(const Entry&) = delete;
    Entry& operator=(const Entry&) = delete;
    void print_tree() const noexcept { print(""); }

    inline const std::string& get_name() const;
	bool is_dir();
   
	virtual void print(const std::string& pre) const = 0;
private:
	std::string m_name;
};

class File : public Entry {
public:
	explicit File(const std::string& name);//throws bad_alloc, more?
	File(const File& other) = delete;
	File& operator=(const File& other) = delete;
    virtual ~File() = default;

    virtual void print(const std::string& pre) const override;
};

class Directory : public Entry {
public:
    explicit Directory(const std::string& name);
	Directory(const Directory& other) = delete;
	Directory& operator=(const Directory& other)= delete;
    virtual ~Directory() = default;

	inline void add_entry(std::shared_ptr<Entry> entry);
	virtual void print(const std::string& pre) const override;
    
private:    
	std::vector<std::shared_ptr<Entry>> m_entries;
};


inline Entry::Entry(const std::string& name) : m_name(name) {}

inline const std::string& Entry::get_name() const
{
	return m_name;
}


inline void Directory::add_entry(std::shared_ptr<Entry> entry)
{
	m_entries.push_back(entry);
}

inline void File::print(const std::string& pre) const 
{ 
    std::cout << pre << "_" << Entry::get_name() <<std::endl; 
}

} //namespace fs_tree
} // namespace ilrd

#endif // FS_TREE_HPP_

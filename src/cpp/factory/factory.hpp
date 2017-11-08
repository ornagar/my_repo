#ifndef FACTORY_HPP_
#define FACTORY_HPP_

#include <functional> //std::function
#include <stdexcept> //runtime_error
#include <map>
#include <memory> //shared_ptr

namespace ilrd {

template <class Key, class Base, class Params = int>
class Factory {
public:
	
	Factory() = default; //throw: bad alloc (map ctor)
	~Factory() = default;
	Factory(const Factory& other) = delete;
	Factory& operator=(const Factory& other) = delete;
    
    struct BadKey : public std::runtime_error {
        BadKey(const std::string& what = "Bad key sent to Factory::create()")
          : std::runtime_error(what) {}
    };
	
	// throw: BadKey / bad alloc (operator new in functor)
	std::shared_ptr<Base> create(const Key& key); 
	std::shared_ptr<Base> create(const Key& key, Params params); 
	
	//throw: bad alloc? (map insertion) / key already exist?
	// func - functor
	void add(const Key& key, std::shared_ptr<Base>(*func)(Params)); 

private:
	std::map<Key, std::shared_ptr<Base>(*)(Params)> m_map;
};

template<class Key, class Base, class Params>
std::shared_ptr<Base> Factory<Key, Base, Params>::create(const Key& key, Params params)
{
    try {
      return m_map.at(key)(params); 
    } catch(std::out_of_range) {
        throw BadKey();
    }
}
	
template<class Key, class Base, class Params>
std::shared_ptr<Base> Factory<Key, Base, Params>::create(const Key& key)
{
    try {
      return m_map.at(key)(0); 
    } catch(std::out_of_range) {
        throw BadKey();
    }
}

template<class Key, class Base, class Params>
void Factory<Key, Base, Params>::add(const Key& key, std::shared_ptr<Base>(*func)(Params))
{
    m_map[key] = func; 
}


} //namespace ilrd

#endif //FACBaseORY_HPP_

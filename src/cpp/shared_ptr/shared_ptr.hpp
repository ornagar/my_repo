/*
 * shared_ptr.hpp
 *
 *  Created on: Oct 9, 2017
 *      Author: noname
 */

#ifndef SHARED_PTR_HPP_
#define SHARED_PTR_HPP_

#include <cstddef>      // size_t
#include <mutex>        // mutex

namespace ilrd {

template <class T>
class SharedPtr;

template <class T>
inline bool operator==(const SharedPtr<T>& lhs, const SharedPtr<T>& rhs) noexcept;

template <class T>
inline bool operator!=(const SharedPtr<T>& lhs, const SharedPtr<T>& rhs) noexcept;

template <class T>
inline bool operator<(const SharedPtr<T>& lhs, const SharedPtr<T>& rhs) noexcept;

template <class T>
inline bool operator>(const SharedPtr<T>& lhs, const SharedPtr<T>& rhs) noexcept;

template<class T>
class SharedPtr {

public:
    inline SharedPtr(T* ptr = nullptr);
   ~SharedPtr();
    SharedPtr(const SharedPtr&);
    SharedPtr& operator=(const SharedPtr& other);

    inline T* operator->() const noexcept;
    inline T& operator*() const noexcept;

    inline T* get() const noexcept;

    inline operator bool() const noexcept;

    template <class U>
    inline SharedPtr(const SharedPtr<U>& other);

private:
    template <class U>
    friend class SharedPtr;

    T* m_ptr;
    size_t* m_cnt;
    std::mutex *m_mutex; //use lock_guard
};

template<class T>
inline SharedPtr<T>::SharedPtr(T* ptr): m_ptr(ptr), m_cnt(new size_t(1))
{
    try {
        m_mutex = new std::mutex;
    }catch (std::bad_alloc) {
        delete m_cnt;
        throw;
    }
}

template<class T>
SharedPtr<T>::~SharedPtr()
{
    bool last_flag = false;
    {
        std::lock_guard<std::mutex> guard(*m_mutex);
        if (*m_cnt > 1) {
            --(*m_cnt);
        } else {
            delete m_ptr;
            delete m_cnt;
            last_flag = true;
        }
    }
    if (last_flag) {
        delete m_mutex;
    }
}

template<class T>
inline SharedPtr<T>::SharedPtr(const SharedPtr<T>& other): m_mutex(other.m_mutex),
    m_cnt(other.m_cnt), m_ptr(other.m_ptr)
{
    std::lock_guard<std::mutex> guard(*m_mutex);
    ++(*m_cnt);
}

template<class T>
SharedPtr<T>& SharedPtr<T>::operator=(const SharedPtr<T>& other)
{
    SharedPtr<T> temp(other);

    size_t* cnt = temp.m_cnt;
    T* ptr = temp.m_ptr;
    std::mutex* mutex = temp.m_mutex;

    temp.m_cnt = m_cnt;
    temp.m_ptr = m_ptr;
    temp.m_mutex = m_mutex;

    m_cnt = cnt;
    m_ptr = ptr;
    m_mutex = mutex;

    return *this;
}

template<class T>
inline T* SharedPtr<T>::operator->() const noexcept
{
    return m_ptr;
}

template<class T>
inline T& SharedPtr<T>::operator*() const noexcept
{
    return *m_ptr;
}

template<class T>
inline T* SharedPtr<T>::get() const noexcept
{
    return m_ptr;
}

template<class T>
inline SharedPtr<T>::operator bool() const noexcept
{
    return (m_ptr);
}

template <class T>
template <class U>
inline SharedPtr<T>::SharedPtr(const SharedPtr<U>& other): m_mutex(other.m_mutex),
m_cnt(other.m_cnt), m_ptr(other.m_ptr)
{
   std::lock_guard<std::mutex> guard(*m_mutex);
   ++(*m_cnt);
}

template <class T>
inline bool operator==(const SharedPtr<T>& lhs, const SharedPtr<T>& rhs) noexcept
{
    return lhs.get() == rhs.get();
}

template <class T>
inline bool operator!=(const SharedPtr<T>& lhs, const SharedPtr<T>& rhs) noexcept
{
    return !operator==(lhs, rhs);
}

template <class T>
inline bool operator<(const SharedPtr<T>& lhs, const SharedPtr<T>& rhs) noexcept
{
    return lhs.get() < rhs.get();
}

template <class T>
inline bool operator>(const SharedPtr<T>& lhs, const SharedPtr<T>& rhs) noexcept
{
    return lhs.get() > rhs.get();
}

} // namespace ilrd

#endif // SHARED_PTR_HPP_

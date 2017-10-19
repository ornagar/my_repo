#include <cstring>  //strlen
#include <iosfwd>   //istream, ostream
#include <new>      //(std::nothrow)
#include <cstdlib>  //(malloc(), realloc())
#include <sstream>  //get

#include "rc_string.hpp"

namespace ilrd {
namespace rc_string {

static bool atomic_add(std::atomic<size_t>& val);
static bool atomic_sub(std::atomic<size_t>& val);

String::String(const char *in_val)
{
    size_t length = strlen(in_val) + 1;
    m_rc = new std::atomic<size_t>;
    m_cp = reinterpret_cast<char*>(m_rc);
    m_cp += sizeof(std::atomic<size_t>);

    m_cp = new char[length];

    memcpy(m_cp, in_val, length);

    m_rc->store(1);
}

String::String(const String& rhs)
{
    if (atomic_add(*rhs.m_rc)) {
        m_cp = rhs.m_cp;
        m_rc = rhs.m_rc;
    } else {
        size_t length = strlen(rhs.m_cp) + 1 + sizeof(std::atomic<size_t>);
        m_cp = new char[length];

        m_rc = reinterpret_cast<std::atomic<size_t>*>(m_cp);
        m_rc = new (m_rc) std::atomic<size_t>;
        m_cp += sizeof(std::atomic<size_t>);
        memcpy(m_cp, rhs.m_cp, length);
        m_rc->store(1);
    }
}

String& String::operator=(const String& rhs) //TODO: make normal.
{
    if (m_rc == rhs.m_rc) {
        return *this;
    }

    if (atomic_add(*rhs.m_rc)) {
        if (!atomic_sub(*m_rc)) {
            delete[] m_cp;
            delete m_rc;
        }

        m_cp = rhs.m_cp;
        m_rc = rhs.m_rc;
    } else {
        size_t length = strlen(rhs.m_cp) + 1;
        m_rc = new std::atomic<size_t>;
        m_cp = new char[length];

        memcpy(m_cp, rhs.m_cp, length);
        m_rc->store(1);
    }

    return *this;
}

String::~String()
{
    if (!atomic_sub(*m_rc)) {
        delete[] m_cp;
        delete m_rc;
    }
    m_rc = 0;
    m_cp = 0;
}

char& String::operator[](size_t idx)
{
    char* temp;

    if (atomic_sub(*m_rc)) {
        size_t length = len() + 1;

        temp = new char[length];
        m_rc = new std::atomic<size_t>;
        memcpy(temp, m_cp, length);
        m_cp = temp;
    }

    m_rc->store(0);

    return m_cp[idx];
}
/*
 String& String::operator+=(const String& rhs)
 {

 size_t length = len() + 1 + sizeof(std::atomic <size_t>);
 char *temp = new char[length + strlen(rhs.m_cp)];

 memcpy(temp, m_rc, length);
 strcat((temp + sizeof(std::atomic <size_t>)), rhs.m_cp);

 if (!atomic_sub(*m_rc)) {
 delete[] m_cp;

 m_rc->store(1);
 }
 delete[] m_cp;
 m_cp = temp;


 return *this;
 }
 */
/*
 std::istream& operator>>(std::istream& is, String& str)
 {
 String temp;
 char new_str[STRING_SIZE];

 // takes every iteration a buffer of 124B and concats it to temp (String).
 while ('\n' != (new_str[0] = is.get())) {
 is.get((new_str + 1), STRING_SIZE - 2);
 temp += new_str;
 }

 str = temp;

 return is;
 }*/
/*****************************************************************************/
static bool atomic_add(std::atomic<size_t>& val)
{
    size_t old_val = val.load();
    size_t new_val;
    do {
        if (old_val == 0)
            return false;
        new_val = old_val + 1;
    } while (!val.compare_exchange_weak(old_val, new_val,
            std::memory_order_relaxed));

    return true;
}

static bool atomic_sub(std::atomic<size_t>& val)
{
    size_t old_val = val.load();
    size_t new_val;
    do {
        if (old_val <= 1)
            return false;
        new_val = old_val - 1;
    } while (!val.compare_exchange_weak(old_val, new_val,
            std::memory_order_acq_rel));

    return true;
}

}
} //namespace ilrd;


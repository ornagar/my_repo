#ifndef STRING_HPP_
#define STRING_HPP_

#include <atomic>
#include <cstring> //strlen
#include <iosfwd> //istream, ostream

namespace ilrd
{
namespace rc_string
{

const size_t STRING_SIZE = 124;

class String {
public:
    String(const char *in_val = ""); //non explicit by purpose
   ~String();
    String(const String& rhs);
    String& operator=(const String& rhs); // s1 = s2

    size_t len() const;					// s1.len()

    bool operator==(const char *rhs) const;                // s1 == "hello"
    bool operator==(const String& rhs) const;              // s1 == s2
    bool operator!=(const String& rhs) const;              // s1 != s2
    bool operator>(const String& rhs) const;               // s1 < s2
    bool operator<(const String& rhs) const;               // s1 > s2

    const char* c_str() const;

    //String& operator+=(const String& rhs);				   //s += s2

    char  operator[](size_t idx) const;		// s1[8] == 'a' ,'a' == s1[8]
    char& operator[](size_t idx);			// s1[8] = 'a'

    friend std::ostream& operator<<(std::ostream& os, const String& str);// cout
    //friend std::istream& operator>>(std::istream& is, String& str);    // cin
    friend bool operator==(const char* lhs, const String& rhs);		// "hello" == s1
    //friend String operator+(const String& lhs, const String& rhs);     // s + s2

private:
    char *m_cp;
    std::atomic <size_t> *m_rc;
};

inline const char* String::c_str() const
{
    return m_cp;
}

inline size_t String::len() const
{
    return strlen(m_cp);
}

inline bool String::operator==(const char *rhs) const
{
    return 0 == strcmp(rhs, m_cp);
}

inline bool String::operator==(const String& rhs) const
{
    return 0 == strcmp(rhs.m_cp, m_cp);
}

inline bool String::operator!=(const String& rhs) const
{
    return !(rhs == *this);
}

inline bool String::operator>(const String& rhs) const
{
    return 0 < strcmp(m_cp, rhs.m_cp);
}
inline bool String::operator<(const String& rhs) const
{
    return 0 > strcmp(m_cp, rhs.m_cp);
}

inline char String::operator[](size_t idx) const
{
    return m_cp[idx];
}

inline std::ostream& operator<<(std::ostream& os, const String& str)
{
    return os << str.m_cp;
}


inline bool operator==(const char* lhs, const String& rhs)
{
    return rhs == lhs;
}
/*
inline String operator+(const String& lhs, const String& rhs)
{
    String temp(lhs);

    return temp += rhs;
}

*/
}//namespace rc_string
} //namespace ilrd

#endif  //STRING_HPP_




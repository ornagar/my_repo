
#ifndef STRING_HPP_
#define STRING_HPP_

#include <cstring> //strlen
#include <iosfwd> //istream, ostream

namespace ilrd
{

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

    String& operator+=(const String& rhs);				   //s += s2

    char  operator[](size_t idx) const;		// s1[8] == 'a' ,'a' == s1[8]
    char& operator[](size_t idx);			// s1[8] = 'a'

    friend std::ostream& operator<<(std::ostream& os, const String& str);// cout
    friend std::istream& operator>>(std::istream& is, String& str);    // cin
    friend bool operator==(const char* lhs, const String& rhs);		// "hello" == s1
    friend String operator+(const String& lhs, const String& rhs);     // s + s2

private:
    char *m_cp;
};

inline String::String(const char *in_val)
{
    size_t length = strlen(in_val) + 1;
    m_cp = new (std::nothrow)char[length];
    if (0 == m_cp){
        return;
    }

    memcpy(m_cp, in_val, length);
}

inline String::~String()
{
   delete[] m_cp;
}

inline String::String(const String& rhs)
{
    size_t length = strlen(rhs.m_cp) + 1;

    m_cp = new (std::nothrow)char[length];
    if (0 == m_cp){
        return;
    }
    memcpy(m_cp, rhs.m_cp, length);
}

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

inline char& String::operator[](size_t idx)
{
    return m_cp[idx]; // return previous with const cast.
}

inline std::ostream& operator<<(std::ostream& os, const String& str)
{
    return os << str.m_cp;
}


inline bool operator==(const char* lhs, const String& rhs)
{
    return rhs == lhs;
}

inline String operator+(const String& lhs, const String& rhs)
{
    String temp(lhs);

    return temp += rhs;
}

} //namespace ilrd

#endif  //STRING_HPP_

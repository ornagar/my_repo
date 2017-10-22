#include <iostream>
#include "rc_string.hpp"

using namespace ilrd;
using namespace rc_string;
using namespace std;

int main()
{
    String str = "Hello";
    String str2(str);
    String str3;
    str3 = str;
    //String str4(str2);
    char s[] = "jello";

    bool result;

    result = str == str2;
    if (true != result) {cout << "problem line " << __LINE__ << endl;}

    result = str == s;
    if (false != result) {cout << "problem line " << __LINE__ << endl;}

    result = str == str3;
    if (true != result) {cout << "problem line " << __LINE__ << endl;}

    result = str != str3;
    if (false != result) {cout << "problem line " << __LINE__ << endl;}

    result = str > str2;
    if (false != result) {cout << "problem line " << __LINE__ << endl;}

    result = str < str2;
    if (false != result) {cout << "problem line " << __LINE__ << endl;}

    //char peek;
    /*peek = str[0];
    if ('H' != peek) {cout << "problem line " << __LINE__ << endl;}

    peek = str2[2];
    if ('l' != peek) {cout << "problem line " << __LINE__ << endl;}*/

    str[0] = 'j';
    result = (str == s);
    if (true != result) {cout << "problem line " << __LINE__ << endl;}

// override str4 with new cin.
    String str4 = "somthing";
    //cin >> str4;

    cout << "str: " << str << " |str2: " << str2 << " |str4: " << str4 << endl;

    return 0;
}

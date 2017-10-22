#include <iostream>                  /* cout                     */
#include "string.hpp"                /* all functions declerations    */
using namespace ilrd;
using namespace std;

void PrintResult(int outcome, const char *func_name);
int CTORTest();
int EqualesOpTest();
int AssigmentOpTest();
int NotEqualsOpTest();
int AddAssignOpTest();
int BiggerOpTest();
int SmallerOpTest();
int IndexOpTest();
int LenTest();
int InOutOpTest();
int Plus();

/*->->->->->->->->->->->->->->->->- M A I N -<-<-<-<-<-<-<-<-<-<-<-<-<-<-<-<-<*/
int main(void)
{
    int outcome = 0;

    outcome = CTORTest();
    PrintResult(outcome, "CTORTest");
    outcome = EqualesOpTest();
    PrintResult(outcome, "EqualesOpTest");
    outcome = AssigmentOpTest();
    PrintResult(outcome, "assigment operator");
    outcome = NotEqualsOpTest();
    PrintResult(outcome, "not equales operator");
    outcome = AddAssignOpTest();
    PrintResult(outcome, "add and assign operator");
    outcome = BiggerOpTest();
    PrintResult(outcome, "bigger operator");
    outcome = SmallerOpTest();
    PrintResult(outcome, "smaller operator");
    outcome = IndexOpTest();
    PrintResult(outcome, "index operator");
    outcome = LenTest();
    PrintResult(outcome, "length operator");
    outcome = InOutOpTest();
    PrintResult(outcome, "in out operator");
    outcome = Plus();
    PrintResult(outcome, "in out Plus");

    return (0);
}

/******************************************************************************/
void PrintResult(int outcome, const char *func_name)
{
    if (outcome != 0)
    {
        std::cout<<func_name<<" failed in "<<outcome<<" testing\n";
    }
    else
    {
        std::cout<<func_name<<" suscess!\n";
    }
}

/******************************************************************************/
int CTORTest()
{
    int counter = 0;
    char string[] = "hello";
    const char *ptrString = "hello";
    String s1("hello");
    String s2(s1);
    String s3(String);
    String s4(ptrString);
    String s5 = string;
    String s6 = s1;

    return counter;
}

/******************************************************************************/
int EqualesOpTest() // ==
{
    int counter = 0;
    String s1("hello");
    String s2(s1);

    if(!(s1 == s2))
    {
        ++counter;
    }

    String s3("hi");
    if(s3 == s1)
    {
        ++counter;
    }

    String s4("");
    if(s4 == s1)
    {
        ++counter;
    }
    char str[] = "hello";

    String s5(str);
    if(!(s5 == str))
    {
        ++counter;
    }
    if(!("hello" == s1))
    {
        ++counter;
    }
    if(!(s1 == "hello"))
    {
        ++counter;
    }

    if(!(s1 == s1))
    {
        ++counter;
    }

    return counter;
}

/******************************************************************************/
int AssigmentOpTest()// =
{
    int counter = 0;
    String s1("hello");
    String s2("bbb");

    if(s1 == s2)
    {
        ++counter;
    }
    s2 = s1;
    if(!(s1 == s2))
    {
        ++counter;
    }
    s2 = "jjj";
    if(!(s2 == "jjj"))
    {
        ++counter;
    }
    char str[] = "hi";
    s2 = str;
    if(!(s2 == "hi"))
    {
        ++counter;
    }
    s1 = s2 = "bb8";
    if(!(s1 == "bb8"))
    {
        ++counter;
    }
    if(!(s2 == "bb8"))
    {
        ++counter;
    }
    s1 = s1;
    if(s1 != s1)
    {
        ++counter;
    }


    return counter;
}

/******************************************************************************/
int NotEqualsOpTest()// !=
{
    int counter = 0;
    String s1("hello");
    String s2(s1);

    if(s1 != s2)
    {
        ++counter;
    }

    String s3("hi");
    if(!(s3 != s1))
    {
        ++counter;
    }

    String s4("");
    if(!(s4 != s1))
    {
        ++counter;
    }
    char str[] = "hello";

    String s5(str);
    if(s5 != str)
    {
        ++counter;
    }

    const String s6("r2d2");

    s1 = "r2d2";
    if(s6 != s1)
    {
        ++counter;
    }
    if(s6!=s6)
    {
        ++counter;
    }

    return counter;
}

/******************************************************************************/
int AddAssignOpTest()// +=
{
    int counter = 0;
    String s1("hello");
    String s2("bbb");

    s1 += s2;

    if(s1 != "hellobbb")
    {
        ++counter;
    }
    s2 += s2;
    if(s2 != "bbbbbb")
    {
        ++counter;
    }

    String s3("");
    s1 = "bbbbbb";
    s2 += s3;
    if(s2 != s1)
    {
        ++counter;
    }
    s1 = "may the ";
    s2 = "force be ";
    s1+=s2+="with you";

    if(s1 != "may the force be with you")
    {
        ++counter;
    }

    String s4("j");

    s4+=s4;
    if(s4 != "jj")
    {
        ++counter;
    }

    return counter;
}

/******************************************************************************/
int BiggerOpTest()// <
{
    int counter = 0;
    const String s1 = "a";
    String s2 = "b";

    if(s2 < s1)
    {
        ++counter;
    }

    s2 = "aa";
    if(s2 < s1)
    {
        ++counter;
    }

    s2 = "A";
    if(s1 < s2)
    {
        ++counter;
    }

    s2 = "c3po";
    if(s2 < "c3p")
    {
        ++counter;
    }
    if(s2 < s2)
    {
        ++counter;
    }

    return counter;
}


/******************************************************************************/
int SmallerOpTest()// >
{
    int counter = 0;
    const String s1 = "a";
    String s2 = "b";

    if(s1 > s2)
    {
        ++counter;
    }

    s2 = "aa";
    if(s1 > s2)
    {
        ++counter;
    }

    s2 = "A";
    if(s2 > s1)
    {
        ++counter;
    }

    s2 = "c3po";
    if(s2 > "c3poo")
    {
        ++counter;
    }
    if(s2 < s2)
    {
        ++counter;
    }

    return counter;
}

/******************************************************************************/
int IndexOpTest()// []
{
    int counter = 0;
    String s1 = "abc3ef";

    if(s1[0] != 'a')
    {
        ++counter;
    }

    if(s1[3] != '3')
    {
        ++counter;
    }

    if(s1[6] != 0)
    {
        ++counter;
    }

    s1[3] = 'd';
    if(s1 != "abcdef")
    {
        ++counter;
    }

    s1[2] = 0;
    if(s1 != "ab")
    {
        ++counter;
    }

    return counter;
}


/******************************************************************************/
int LenTest()
{
    int counter = 0;

    String s1 = "";
    if(s1.len() != 0)
    {
        ++counter;
    }

    s1 += "a";
    if(s1.len() != 1)
    {
        ++counter;
    }

    s1 += "a";
    if(s1.len() != 2)
    {
        ++counter;
    }

    s1 += "a";
    if(s1.len() != 3)
    {
        ++counter;
    }

    const String s2("");
    if(s2.len() != 0)
    {
        ++counter;
    }

    const String s3("abc");
    if(s3.len() != 3)
    {
        ++counter;
    }

    return counter;
}

/******************************************************************************/
int InOutOpTest()
{
    String s = "iodhaslkjdflks fsdlkf fsdkj";

    cout<<"Please enter a string\n";
    cin >> s;
    cout<< "The string is:" <<s<<endl;
    return 0;
}

/******************************************************************************/
int Plus()
{
    String s1 = "Shlomi";
    String s2 = "Shemesh";
    String s3;

    s3 = s1 + s2;

    cout<<s3<<endl;
    return 0;
}

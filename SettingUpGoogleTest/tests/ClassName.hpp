//
// Created by xyz on 09/11/17.
//

#ifndef SETTINGUPGOOGLETEST_CLASSNAME_HPP
#define SETTINGUPGOOGLETEST_CLASSNAME_HPP


class ClassName {
public:
    int age;

    int getAge() const {
        return age;
    }

    void setAge(int age) {
        ClassName::age = age;
    }
};


#endif //SETTINGUPGOOGLETEST_CLASSNAME_HPP

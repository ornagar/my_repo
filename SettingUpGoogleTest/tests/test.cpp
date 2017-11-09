//
// Created by xyz on 09/11/17.
//

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "ClassName.hpp"
using testing::Eq;

namespace {
class ClassDeclaration : public testing::Test {
public:
    ClassName obj;
    ClassDeclaration(){
        obj; // could put here a make method
    }
};
TEST_F(ClassDeclaration, nameOfTheTest1) {
    obj.setAge(22);
    ASSERT_EQ(22, obj.getAge());

}

TEST_F(ClassDeclaration, nameOfTheTest2) {
    obj.setAge(58);
    ASSERT_THAT(57, testing::Eq(obj.getAge()));
}
    
}
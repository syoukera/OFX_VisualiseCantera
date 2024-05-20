// MyClass.cpp
#include "MyClass.h"
#include <iostream>

MyClass::MyClass() : someMemberVariable(0) {
    // コンストラクタの実装
}

void MyClass::doSomething() {
    std::cout << "Doing something!" << std::endl;
}

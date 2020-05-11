#include <iostream>

struct Base {
    Base(int a = 0) : value(a) {}
    int value;
};

void Func(Base a, Base b) {
    std::cout << "void Func(Base a, Base b)" << std::endl;
    return ;
}

void Func(Base& a, Base& b) {
    std::cout << "void Func(Base& a, Base& b)" << std::endl;
    return ;
}

void Func(const Base& a, const Base& b) {
    std::cout << "void Func(const Base& a, const Base& b)" << std::endl;
    return ;
}

void TFunc(Base& a, Base& b) {
    std::cout << "void Func(Base& a, Base& b)" << std::endl;
    return ;
}

void TFunc(const Base& a, const Base& b) {
    std::cout << "void Func(const Base& a, const Base& b)" << std::endl;
    return ;
}



void Func(int a, int b) {
    std::cout << "void Func(int a, int b)" << std::endl;
}

void Func(double a, double b) {
    std::cout << "void Func(double a, double b)" << std::endl;
}

void Quote() {
    const Base& a = Base();

    ((void (*)(const Base&, const Base&))Func)(a, a);
    ((void (*)(Base, Base))Func)(a, a);

    Base b;
    Base& c = b;
    const Base d(1);
    TFunc(b, b);
    TFunc(d, d);
}

void ValueType() {
    int i = 1;
    double d = 1.0;

    Func(i, i);
    Func(d, d);
    // Func(i, d); // 无法确认最优调用函数
}


int main(int argc, char* argv[])
{
    Quote();
    ValueType();
    return 0;
}

#include <iostream>
#include <string>
#include <memory.h>

class Base {
public:
    Base(const std::string& name = "") {
        std::cout << "Base()" << std::endl;
    }

    ~Base() {
        std::cout << "~Base()" << std::endl;
    }

    Base(const Base& a) {
        std::cout << "Base(const Base& a)" << std::endl;
    }
    
    Base(const Base&& a) {
        std::cout << "Base(const Base&& a)" << std::endl;
    }

    Base& operator= (const Base& a) {
        std::cout << "operator=(const Base& a)" << std::endl;
        return *this;
    }

    Base& operator= (Base&& a) {
        std::cout << "operator=(Base&& a)" << std::endl;
        return *this;
    }
private:
    std::string _name;
};


Base GenBase() {
    Base a;
    return a;
}

Base GenBase(bool flag) {
    if (flag) {
        Base a = Base("TRUE");
        return a;
    } else {
        Base b = Base("FALSE");
        return b;
    }
}

int main(int argc, char* argv[])
{
    const int& i = 0; // 常量左值引用
    // int& i = 0; // 编译错误 用类型为‘int’的右值初始化类型为‘int&’的非常量引用无效
    int&& j = 0; // 实质上就是将不具名(匿名)变量取了个别名
    int k = 0;
    // int&& l = k; // 无法将左值‘int’绑定到‘int&&’
    Base a = std::move(Base()); // Base() Base(const Base&& a)
    Base b = Base(); // Base()
    Base c = GenBase(); // 默认开启的 NRVO（具名返回值优化）导致的调用顺序 Base()  
    Base d = GenBase(true); // 返回不同路径上不同名对象，NRVO（失效）Base() Base(const Base&& a)
    Base e = std::move(a); // 优先使用 Base(Base&& a), 无移动拷贝构造函数时使用 Base(const Base& a)
    Base f;
    f = std::move(b); // 类比拷贝构造函数调用赋值函数
    return 0;
}

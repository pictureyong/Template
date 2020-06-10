#include <tuple>
#include <string>
#include <iostream>

// g++ -std=c++11 Tuple.cc

std::tuple<int, std::string, std::string> Func() {
    return std::make_tuple(2020, "C++11", "hello world!");
}

int main(int argc, char* argv[])
{
    int year;
    std::string name;
    std::string msg;
    tie(year, name, msg) = Func();
    std::cout << year << ": " << name << "\t" << msg << std::endl;
    return 0;
}

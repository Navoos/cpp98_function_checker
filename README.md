# c++98_function_checker
## Description
This is a simple command-line tool that allows you to check whether a function is available in the C++98 standard. The program takes as argument the functions names and checks whether it is available in C++98 using an online reference (legacy.cplusplus.com).
This project can be useful for programmers who need to write code that is compatible with older versions of C++ or who want to learn more about the differences between C++98 and more recent versions of the language.
## Usage
### libcurl must be installed on your system
    g++ main.cpp -o cpp98_function_checker -lcurl

    ./cpp98_function_checker function function ...

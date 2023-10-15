cmake_minimum_required(VERSION 3.10)
project(Dargon-Lang 
    VERSION 0.1
    DESCRIPTION "The Dargon Programming Language Interpreter"
    HOMEPAGE_URL https://github.com/kylemmorris/dargon-lang)
set(CMAKE_CXX_STANDARD 17)
add_executable(Dargon src/main.cpp)

cmake_minimum_required(VERSION 2.8.4)
project(CatClient)
include_directories("jsoncpp/dist/")

set(SOURCE_FILES main.cpp
                 jsoncpp/dist/jsoncpp.cpp
                 CmdGenerator.cpp)

add_executable(CatClient ${SOURCE_FILES})
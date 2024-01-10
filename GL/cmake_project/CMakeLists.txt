cmake_minimum_required(VERSION 3.14)

set(PROJECT_NAME cmake_project) #set a variable
set(CMAKE_CXX_STANDARD 17) #global variable = version 17

project(${PROJECT_NAME}) #use env variable for ${} ,  project setting option
add_executable(${PROJECT_NAME} src/main.cpp) #create object file with src/... all file

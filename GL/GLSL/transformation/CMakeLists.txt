cmake_minimum_required(VERSION 3.14)

set(PROJECT_NAME GLSL_example) #set a variable
set(CMAKE_CXX_STANDARD 17) #global variable = version 17

set(WINDOW_NAME "pipeline_example_OPENGL!") #global variable for create window 
set(WINDOW_WIDTH 960)
set(WINDOW_HEIGHT 540)

project(${PROJECT_NAME}) #use env variable for ${} ,  project setting option
add_executable(${PROJECT_NAME}  src/main.cpp
                                src/common.cpp src/common.h
                                src/shader.cpp src/shader.h 
                                src/program.cpp src/program.h
                                src/context.cpp src/context.h
                                src/buffer.cpp src/buffer.h
                                src/image.cpp src/image.h
                                src/vertex_layout.cpp src/vertex_layout.h
                                src/texture.cpp src/texture.h
                                ) #create object file with src/... all file auto link

#include(ExternalProject) # ExternalProject 

find_package(OpenGL REQUIRED)
if(NOT OPENGL_FOUND)
    message("ERROR: OpenGL not found")
endif(NOT OPENGL_FOUND)
set(GL_LIBRARY GL GLU X11)

include(Dependency.cmake)

# 우리 프로젝트에 include / lib 관련 옵션 추가
target_include_directories(${PROJECT_NAME} PUBLIC ${DEP_INCLUDE_DIR})
target_link_directories(${PROJECT_NAME} PUBLIC ${DEP_LIB_DIR})
target_link_libraries(${PROJECT_NAME} PUBLIC ${DEP_LIBS} dl ${GL_LIBRARY} m pthread)

#변수의 값을 끌어와서 compile_definitions를 설정해준다. #define과 같은 매크로를 바깥에서 쓰는 것이다.
target_compile_definitions(${PROJECT_NAME} PUBLIC
    WINDOW_NAME="${WINDOW_NAME}"
    WINDOW_WIDTH=${WINDOW_WIDTH}
    WINDOW_HEIGHT=${WINDOW_HEIGHT}
)

#add_dependencies(${PROJECT_NAME} ${DEP_LIST}) #${DEP_LIST}를 먼저 컴파일 한 후에  ${PROJECT_NAME} 프로젝트를 컴파일 하라는 명령 
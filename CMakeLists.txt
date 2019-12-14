cmake_minimum_required(VERSION 3.15)
project(untitled)

set(OpenGlLinkers -lglut -lGLU -lGL) # setting all the Glut libraries as one variable.
set(CMAKE_CXX_STANDARD 14)

add_executable(untitled main.cpp LoaderManager.cpp LoaderManager.h)
target_link_libraries(untitled ${OpenGlLinkers}) # linking opengl libraries to the project

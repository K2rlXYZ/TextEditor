cmake_minimum_required(VERSION 3.25)
project(BigCode VERSION 0.0.1)


include_directories(include)

file(GLOB RESOURCES "resources/test.rc")
configure_file("resources/small.ico" "${CMAKE_CURRENT_BINARY_DIR}/Debug/small.ico" COPYONLY)
configure_file("resources/test.ico" "${CMAKE_CURRENT_BINARY_DIR}/Debug/test.ico" COPYONLY)

file(GLOB SOURCES "src/*.cpp")
add_executable(${PROJECT_NAME} WIN32 ${SOURCES})

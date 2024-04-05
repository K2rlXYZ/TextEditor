cmake_minimum_required(VERSION 3.25)
project(BigCode VERSION 0.0.1)


include_directories(include)
file(GLOB SOURCES "src/*.cpp")
file(GLOB RESOURCES "resources/test.rc")
add_executable(${PROJECT_NAME} WIN32 ${SOURCES} ${RESOURCES})

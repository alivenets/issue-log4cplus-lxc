cmake_minimum_required(VERSION 3.0.2)

project(Log4CplusLXCIssue LANGUAGES CXX)

find_package(PkgConfig REQUIRED)

pkg_check_modules(LXC REQUIRED lxc>=2.0.8)

find_package(log4cplus CONFIG REQUIRED)

set(LoggingLibrary_FOUND 1)
set(LoggingLibrary_NAME "log4cplus")

set(LoggingLibrary_LIBRARIES log4cplus::log4cplus)
set(LoggingLibrary_VERSION ${log4cplus_VERSION})

add_executable(log4cplus-lxc-issue main.cpp)

# NOTE: Enabled ThreadSanitizer detects the issue
# set(SANITIZE_FLAGS "-fsanitize=undefined -fsanitize=thread")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -std=c++11 ${SANITIZE_FLAGS}")

target_link_libraries(log4cplus-lxc-issue PRIVATE
    ${LoggingLibrary_LIBRARIES}
    ${LXC_LIBRARIES}
)

install(TARGETS log4cplus-lxc-issue DESTINATION bin)

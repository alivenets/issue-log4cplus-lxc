cmake_minimum_required(VERSION 3.0.2)

project(Log4CplusLXCIssue LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

find_package(PkgConfig REQUIRED)

pkg_check_modules(LXC REQUIRED lxc>=3.1.0)

set(USED_LIBRARY "boostlog")

if (USED_LIBRARY STREQUAL "log4cplus")
    find_package(log4cplus CONFIG REQUIRED)

    set(LoggingLibrary_FOUND 1)
    set(LoggingLibrary_NAME "log4cplus")

    set(LoggingLibrary_LIBRARIES log4cplus::log4cplus)
    set(LoggingLibrary_VERSION ${log4cplus_VERSION})
    set(LOG_DEFS -DUSE_LOG4CPLUS)
elseif(USED_LIBRARY STREQUAL "spdlog")
    find_package(spdlog REQUIRED)

    set(LoggingLibrary_FOUND 1)
    set(LoggingLibrary_NAME "spdlog")

    set(LoggingLibrary_LIBRARIES spdlog)
    set(LoggingLibrary_VERSION ${spdlog_VERSION})
    set(LOG_DEFS -DUSE_SPDLOG)
elseif(USED_LIBRARY STREQUAL "boostlog")
    find_package(Boost REQUIRED COMPONENTS log_setup log)
    set(LoggingLibrary_FOUND 1)
    set(LoggingLibrary_NAME "boostlog")

    set(LoggingLibrary_LIBRARIES ${Boost_LIBRARIES})
    set(LoggingLibrary_VERSION ${Boost_VERSION})
    set(LoggingLibrary_INCLUDE_DIRS ${Boost_INCLUDE_DIRS})
    set(LOG_DEFS -DUSE_BOOST_LOG -DBOOST_ALL_DYN_LINK)
else()
    message(FATAL_ERROR "Unknown library ${USED_LIBRARY}!")
endif()

add_executable(log4cplus-lxc-issue main.cpp)

# NOTE: Enabled ThreadSanitizer detects the issue
set(SANITIZE_FLAGS -fsanitize=undefined)

#list(APPEND SANITIZE_FLAGS -fsanitize=address)
#list(APPEND SANITIZE_FLAGS -fsanitize=thread)

target_include_directories(log4cplus-lxc-issue PRIVATE ${LoggingLibrary_INCLUDE_DIRS})
target_compile_options(log4cplus-lxc-issue PRIVATE -g -std=c++11 ${LOG_DEFS} ${SANITIZE_FLAGS})

target_link_libraries(log4cplus-lxc-issue PRIVATE
    ${LoggingLibrary_LIBRARIES}
    ${LXC_LIBRARIES}
    PUBLIC ${SANITIZE_FLAGS}
)

install(TARGETS log4cplus-lxc-issue DESTINATION bin)

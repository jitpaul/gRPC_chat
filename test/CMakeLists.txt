cmake_minimum_required(VERSION 3.5)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_LIST_DIR}/../cmake")
include(downloadproject)

#GoogleTest
download_project(PROJ                googletest
                 GIT_REPOSITORY      https://github.com/google/googletest.git
                 GIT_TAG             master
                 UPDATE_DISCONNECTED 1
                 QUIET
)
add_subdirectory(${googletest_SOURCE_DIR} ${googletest_BINARY_DIR})

add_executable(
    client_test
    client.t.cpp)

add_executable(
    server_test
    server.t.cpp
)

target_link_libraries(
    client_unit_tests
    gtest_main
    client_test
)

target_link_libraries(
    server_unit_tests
    gtest_main
    server_test
)

add_test(
  NAME
    unit
  COMMAND
    ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_BINDIR}/unit_tests
)
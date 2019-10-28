cmake_minimum_required(VERSION 3.5)

project(grpc-chat CXX)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_LIST_DIR}/../cmake")
include(downloadproject)

download_project(PROJ                grpc
                 GIT_REPOSITORY      https://github.com/grpc/grpc.git
                 GIT_TAG             master
                 UPDATE_DISCONNECTED 1
                 QUIET
)
add_subdirectory(${grpc_SOURCE_DIR} ${grpc_BINARY_DIR})

set(_PROTOBUF_LIBPROTOBUF libprotobuf)
set(_PROTOBUF_PROTOC $<TARGET_FILE:protoc>)
set(_GRPC_GRPCPP_UNSECURE grpc++_unsecure)
set(_GRPC_CPP_PLUGIN_EXECUTABLE $<TARGET_FILE:grpc_cpp_plugin>)

# Proto file
get_filename_component(chat_proto "../protos/chat.proto" ABSOLUTE)
get_filename_component(chat_proto_path "${chat_proto}" PATH)

# Generated sources
set(chat_proto_srcs "${CMAKE_CURRENT_BINARY_DIR}/chat.pb.cc")
set(chat_proto_hdrs "${CMAKE_CURRENT_BINARY_DIR}/chat.pb.h")
set(chat_grpc_srcs "${CMAKE_CURRENT_BINARY_DIR}/chat.grpc.pb.cc")
set(chat_grpc_hdrs "${CMAKE_CURRENT_BINARY_DIR}/chat.grpc.pb.h")
add_custom_command(
      OUTPUT "${chat_proto_srcs}" "${chat_proto_hdrs}" "${chat_grpc_srcs}" "${chat_grpc_hdrs}"
      COMMAND ${_PROTOBUF_PROTOC}
      ARGS --grpc_out "${CMAKE_CURRENT_BINARY_DIR}"
        --cpp_out "${CMAKE_CURRENT_BINARY_DIR}"
        -I "${chat_proto_path}"
        --plugin=protoc-gen-grpc="${_GRPC_CPP_PLUGIN_EXECUTABLE}"
        "${chat_proto}"
      DEPENDS "${chat_proto}")

# Include generated *.pb.h files
include_directories("${CMAKE_CURRENT_BINARY_DIR}")

# Targets chat_(client|server)
foreach(_target
  chat_client chat_server)
  
  add_executable(${_target} "${_target}.cc"
    ${chat_proto_srcs}
    ${chat_grpc_srcs})
  
  target_link_libraries(${_target}
    ${_GRPC_GRPCPP_UNSECURE}
    ${_PROTOBUF_LIBPROTOBUF})

endforeach()

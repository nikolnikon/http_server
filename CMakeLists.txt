project(http_server)
cmake_minimum_required(VERSION 2.8)
aux_source_directory(. SRC_LIST)
#set(SOURCES main.cpp connection.cpp connection_manager.cpp mime_types.cpp)
add_executable(${PROJECT_NAME} ${SRC_LIST})


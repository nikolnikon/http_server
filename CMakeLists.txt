#aux_source_directory(. SRC_LIST)
#set(SOURCES main.cpp connection.cpp connection_manager.cpp mime_types.cpp)
#add_executable(${PROJECT_NAME} ${SRC_LIST})

cmake_minimum_required (VERSION 2.6)
# Укажите здесь имя вашего проекта.
# Учитываете установку переменных 
# <project_name>_BINARY_DIR и  <project_name>_SOURCE_DIR
# в значение имени каталога с проектом.
project (final)

set (SRC_DIR ${PROJECT_SOURCE_DIR}/src)

# Укажите вместо my-project имя своего приложения
# - имя исполняемого файла
set (APP_NAME final)

# Управление типом сборки через задание значения
# предопределенной переменной CMAKE_BUILD_TYPE
# Возможные значения:
# DEBUG|RELEASE|RELWITHDEBINFO|MINSIZEREL
set(CMAKE_BUILD_TYPE RELEASE)

# Снять комментарий для добавления пути на 
# заголовочные файлы, которые следует добавить 
# для компиляции проекта
include_directories (${PROJECT_SOURCE_DIR}/headers)

# Снять комментарий для добавления пути на 
# библиотеки, которые следует добавить 
# для линковки проекта
#link_directories (/path/to/lib_1)
#link_directories (/path/to/lib_2)
# ...
#link_directories (/path/to/lib_N)

list(APPEND SRC ${SRC_DIR}/connection.cpp)
list(APPEND SRC ${SRC_DIR}/main.cpp)
list(APPEND SRC ${SRC_DIR}/mime_types.cpp)
list(APPEND SRC ${SRC_DIR}/reply.cpp)
list(APPEND SRC ${SRC_DIR}/request_handler.cpp)
list(APPEND SRC ${SRC_DIR}/request_parser.cpp)
list(APPEND SRC ${SRC_DIR}/server.cpp)

set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTITHREADED ON)
find_package(Boost COMPONENTS system thread REQUIRED)

FIND_PACKAGE(Threads)

add_executable (${APP_NAME} ${SRC})
target_link_libraries(${APP_NAME} ${Boost_LIBRARIES})
target_link_libraries(${APP_NAME} ${CMAKE_THREAD_LIBS_INIT})


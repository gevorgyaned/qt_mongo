cmake_minimum_required(VERSION 3.16)

project(helloworld VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets)
find_package(libmongocxx REQUIRED)
find_package(libbsoncxx REQUIRED)

include_directories(${LIBMONGOCXX_INCLUDE_DIRS})
include_directories(${LIBBSONCXX_INCLUDE_DIRS})

qt_standard_project_setup()

qt_add_executable(app
    main.cpp
)

target_link_libraries(app PRIVATE Qt6::Widgets)
target_include_directories(app PRIVATE ${MONGOCXX_INCLUDE_DIRS})
target_link_libraries(app PRIVATE ${LIBMONGOCXX_LIBRARIES})

set_target_properties(app PROPERTIES
    MACOSX_BUNDLE ON
)
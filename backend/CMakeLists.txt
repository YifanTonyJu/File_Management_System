cmake_minimum_required(VERSION 3.10)
project(file-management-server)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(third_library/oatpp)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/third_library/oatpp/src)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/third_library/json/single_include)

add_executable(file-management-server
    main.cpp
    database_api.cpp
    database_api.hpp
    oatpp_data_controller.hpp
)

target_link_libraries(file-management-server oatpp mysqlclient)

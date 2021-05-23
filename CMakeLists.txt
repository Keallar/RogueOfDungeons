cmake_minimum_required(VERSION 3.5)

project(RougeOfDungeons LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(thirdParty/include src/Ui src/Instruments src src/main)

link_directories(thirdParty/libs)
set (PROJECT_LIBS SDL2main SDL2 SDL2_image SDL2_ttf)

link_libraries(${PROJECT_LIBS})

file(GLOB_RECURSE PROJECT_SOURCES src/*.cpp src/*.h data/*.txt data/*.json)

add_executable(RougeOfDungeons ${PROJECT_SOURCES})

add_custom_command(TARGET RougeOfDungeons PRE_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory
                       ${CMAKE_SOURCE_DIR}/thirdParty/bin $<TARGET_FILE_DIR:RougeOfDungeons>)

if(EXISTS ${CMAKE_SOURCE_DIR}/data)
    add_custom_command(TARGET RougeOfDungeons PRE_BUILD
                      COMMAND ${CMAKE_COMMAND} -E copy_directory
                          ${CMAKE_SOURCE_DIR}/data $<TARGET_FILE_DIR:RougeOfDungeons>/data)
endif()

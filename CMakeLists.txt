cmake_minimum_required(VERSION 3.5)

project(RogueOfDungeons LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(RogueOfDungeons)

include_directories(SDL2_image-2.0.5/include
    SDL2_ttf-2.0.15/include
    SDL2-2.0.14/include)

link_directories(SDL2_image-2.0.5/lib
    SDL2_ttf-2.0.15/lib
    SDL2-2.0.14/lib)

link_libraries(SDL2main SDL2 SDL2_image SDL2_ttf)

file(GLOB_RECURSE PROJECT_SOURCES ${CMAKE_SOURCE_DIR}/RogueOfDungeons/*.cpp ${CMAKE_SOURCE_DIR}/RogueOfDungeons/*.h)
file(GLOB_RECURSE PROJECT_DLLS ${CMAKE_SOURCE_DIR}/RogueOfDungeons/*.dll)

add_executable(RogueOfDungeons ${PROJECT_SOURCES})

foreach(dll ${PROJECT_DLLS})
add_custom_command(TARGET RogueOfDungeons PRE_BUILD
                  COMMAND ${CMAKE_COMMAND} -E copy
                      ${dll} $<TARGET_FILE_DIR:RogueOfDungeons>)
endforeach()

if(EXISTS ${CMAKE_SOURCE_DIR}/RogueOfDungeons/images)
    add_custom_command(TARGET RogueOfDungeons PRE_BUILD
                      COMMAND ${CMAKE_COMMAND} -E copy_directory
                          ${CMAKE_SOURCE_DIR}/RogueOfDungeons/images $<TARGET_FILE_DIR:RogueOfDungeons>/images)
endif()

if(EXISTS ${CMAKE_SOURCE_DIR}/RogueOfDungeons/fonts)
    add_custom_command(TARGET RogueOfDungeons PRE_BUILD
                      COMMAND ${CMAKE_COMMAND} -E copy_directory
                          ${CMAKE_SOURCE_DIR}/RogueOfDungeons/fonts $<TARGET_FILE_DIR:RogueOfDungeons>/images)
endif()

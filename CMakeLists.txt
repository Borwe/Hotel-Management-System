cmake_minimum_required(VERSION 3.2)

include($ENV{CMAKES_LOCAL}/poco.cmake)
 
#Replace PROJECT_NAME with project name, and _SOURCES, with sources
set(PROJECT_NAME borwe_hotel_management)
project(${PROJECT_NAME})

#for resting the project information
add_executable(testing src/test.cpp)
target_include_directories(testing PUBLIC ${POCO_INCLUDES}
    include/)
target_link_libraries(testing -lPocoNet -lPocoUtil -lPocoFoundation)
 
#This is for the YCM settings
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
if(EXISTS ${CMAKE_CURRENT_BINARY_DIR}/compile_commands.json)
    EXECUTE_PROCESS(COMMAND ${CMAKE_COMMAND} -E copy_if_different  ${CMAKE_CURRENT_BINARY_DIR}/compile_commands.json ${CMAKE_CURRENT_SOURCE_DIR}/compile_commands.json)
ENDIF()

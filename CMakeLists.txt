cmake_minimum_required(VERSION 3.10)
project(Discord_WebHook CXX)

set(CMAKE_CXX_STANDARD 17)

add_definitions(-DCURL_STATICLIB)

add_executable(Discord_WebHook main.cpp DiscordWebHook/DiscordWebHook.cpp)

target_link_libraries(Discord_WebHook ${CMAKE_SOURCE_DIR}/lib/libcurl.dll.a)

configure_file(${CMAKE_SOURCE_DIR}/lib/libcurl-x64.dll ${CMAKE_CURRENT_BINARY_DIR}/Debug COPYONLY) # This is necessary for the "Debug" folder to be able to run the program.
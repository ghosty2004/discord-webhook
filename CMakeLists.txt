cmake_minimum_required(VERSION 3.15)
project(Discord_WebHook CXX)

set(CMAKE_CXX_STANDARD 17)

include(FetchContent)
FetchContent_Declare(
		cpr
		GIT_REPOSITORY https://github.com/libcpr/cpr.git
		GIT_TAG 47438c7c73d61463520b27759ea58ffb03a31cec
)
FetchContent_MakeAvailable(cpr)

add_executable(Discord_WebHook main.cpp DiscordWebHook/DiscordWebHook.cpp)

target_link_libraries(Discord_WebHook cpr::cpr)

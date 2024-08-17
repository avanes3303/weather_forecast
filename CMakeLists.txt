cmake_minimum_required(VERSION 3.20)
project(weather_forecast)

set(CMAKE_CXX_STANDARD 17)

add_executable(application
        bin/main.cpp
        lib/interface.h
        lib/weather.cpp
        lib/weather.h
        lib/interface.cpp)

include(FetchContent)

FetchContent_Declare(cpr
        GIT_REPOSITORY https://github.com/libcpr/cpr.git
        GIT_TAG 3020c34ae2b732121f37433e61599c34535e68a8)

FetchContent_Declare(nlohmann_json
        GIT_REPOSITORY https://github.com/nlohmann/json.git
        GIT_TAG v3.10.0)

FetchContent_Declare(ncurses URL https://ftp.gnu.org/pub/gnu/ncurses/ncurses-6.2.tar.gz)

FetchContent_MakeAvailable(cpr)
FetchContent_MakeAvailable(nlohmann_json)
FetchContent_MakeAvailable(ncurses)


target_link_libraries(application PUBLIC ncurses cpr nlohmann_json)


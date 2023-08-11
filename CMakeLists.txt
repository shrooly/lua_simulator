cmake_minimum_required(VERSION 3.0.0)
project(lua_simulator VERSION 0.1.0 LANGUAGES C)

find_package(Lua REQUIRED)


add_executable(lua_simulator src/main.c)
target_link_libraries(lua_simulator PRIVATE ${LUA_LIBRARIES})
target_include_directories(lua_simulator PRIVATE ${LUA_INCLUDE_DIR})

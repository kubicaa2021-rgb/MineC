cmake_minimum_required(VERSION 3.16)
project(mineCplus)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

file(GLOB SOURCE_FILES "src/*.cpp" "headers/*.h")
add_executable(mineCplus ${SOURCE_FILES})

target_include_directories(
  mineCplus
  PRIVATE headers
)


find_package(SDL3 REQUIRED)
target_link_libraries(
  mineCplus
  SDL3
)


if(NOT CMAKE_BUILD_TYPE)
  set(default_build_type "Debug")
  message(STATUS
          "Set the build type to `
          ${default_build_type}` as none was specified.")
  set(CMAKE_BUILD_TYPE ${default_build_type} CACHE STRING
      "Choose the build type." FORCE)
  set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS
  "Debug" "Release" "MinSizeRel" "RelWithDebInfo")
endif()
message(STATUS "Mine Cplus Build Type: ${CMAKE_BUILD_TYPE}")

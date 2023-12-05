cmake_minimum_required(VERSION 3.20)

project(
  scratchcards
  DESCRIPTION "Advent of code 2023 - 4th of december"
  VERSION 1.0.0
  LANGUAGES C
)

option(BUILD_FOR_PART_1 "Builds for part 1 of the exercise" ON)

add_executable(app)

if(BUILD_FOR_PART_1)
  message(STATUS "Building for part 1 : determining total number of points worth on all games")
  target_compile_definitions(app PUBLIC -DBUILD_FOR_PART_1=1)
else()
  message(STATUS "Building for part 2 : TODO")
  target_compile_definitions(app PUBLIC -DBUILD_FOR_PART_1=0)
endif()

set(SRCDIR "src")
target_sources(app PUBLIC ${SRCDIR}/main.c)

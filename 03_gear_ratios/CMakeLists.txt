cmake_minimum_required(VERSION 3.20)

project(
  gear_ratios
  DESCRIPTION "Advent of code 2023 - 3rd of december"
  VERSION 1.0.0
  LANGUAGES C
)

option(BUILD_FOR_PART_1 "Builds for part 1 of the exercise" ON)

if(BUILD_FOR_PART_1)
  message(STATUS "Building for part 1 : determining all part numbers in the schematic")
endif()

add_executable(app)
target_compile_definitions(app PUBLIC -DBUILD_FOR_PART_1=${BUILD_FOR_PART_1})

set(SRCDIR "src")

target_sources(app PUBLIC ${SRCDIR}/main.c)

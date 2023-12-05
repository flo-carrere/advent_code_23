cmake_minimum_required(VERSION 3.20)

project(
  code_conundrum
  DESCRIPTION "Advent of code 2023 - 2nd of december"
  VERSION 1.0.0
  LANGUAGES C
)

# Defaultly builds for part 2
option(BUILD_FOR_PART_1 "Builds for part 1 of the exercise (ON), otherwise for part 2" OFF)

if(BUILD_FOR_PART_1)
  message(
    STATUS "Building for part 1 : Determining if games are (im)possible based on fixed set of cube (12r, 13g, 14b)"
  )
else()
  message(STATUS "Building for part 2 : Determining minimum set of cubes necessary to make games possible")
endif()

add_executable(app)
target_compile_definitions(app PUBLIC -DBUILD_FOR_PART_1=${BUILD_FOR_PART_1})

set(SRCDIR "src")

target_sources(app PUBLIC ${SRCDIR}/main.c)

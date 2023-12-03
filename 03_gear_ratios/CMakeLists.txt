cmake_minimum_required(VERSION 3.20)

project(
  gear_ratios
  DESCRIPTION "Advent of code 2023 - 3rd of december"
  VERSION 1.0.0
  LANGUAGES C
)

option(BUILD_FOR_PART_1 "Builds for part 1 of the exercise" ON)
option(DISPLAY_SCHEMATIC "Debug option to display schematic" ON)
option(DISPLAY_PARTS "Debug option to display parts" OFF)
option(DISPLAY_SYMBOLS "Debug option to display symbols" OFF)

add_executable(app)

if(BUILD_FOR_PART_1)
  message(STATUS "Building for part 1 : determining all part numbers in the schematic")
  target_compile_definitions(app PUBLIC -DBUILD_FOR_PART_1)
endif()

if(DISPLAY_SCHEMATIC)
  message(STATUS "Display the input schematic : ON")
  target_compile_definitions(app PUBLIC -DDISPLAY_SCHEMATIC)
endif()

if(DISPLAY_PARTS)
  message(STATUS "Display all part in the schematic : ON")
  target_compile_definitions(app PUBLIC -DDISPLAY_PARTS)
endif()

if(DISPLAY_SYMBOLS)
  message(STATUS "Display all symbols in the schematic : ON")
  target_compile_definitions(app PUBLIC -DDISPLAY_SYMBOLS)
endif()

set(SRCDIR "src")
target_sources(app PUBLIC ${SRCDIR}/main.c)

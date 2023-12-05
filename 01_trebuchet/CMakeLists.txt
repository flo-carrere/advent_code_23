cmake_minimum_required(VERSION 3.20)

project(
  trebuchet
  DESCRIPTION "advent of code 2023 - 1st of december"
  VERSION 1.0.0
  LANGUAGES C
)

option(CHECKS_PART_2 "Includes checks for part 2 of the exercice" ON)

if(CHECKS_PART_2)
  message(STATUS "Include checks for part 1 AND 2")
else()
  message(STATUS "Include checks for part 1 only")
endif()

add_executable(app)
target_compile_definitions(app PUBLIC -DCHECKS_PART_2=${CHECKS_PART_2})

set(SRCDIR "src")

target_sources(app PUBLIC ${SRCDIR}/main.c)

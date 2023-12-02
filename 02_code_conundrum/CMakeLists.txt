cmake_minimum_required(VERSION 3.20)

project(
  code_conundrum
  DESCRIPTION "Advent of code 2023 - 2nd of december"
  VERSION 1.0.0
  LANGUAGES C
)

# Available choice are 1 or 2
message(STATUS "Building for part: ${CHECK_PART}")

add_executable(app)
target_compile_definitions(app PUBLIC CHECK_PART=${CHECK_PART})

set(SRCDIR "src")

target_sources(app PUBLIC ${SRCDIR}/main.c)

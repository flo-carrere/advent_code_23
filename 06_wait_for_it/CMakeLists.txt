cmake_minimum_required(VERSION 3.20)

project(
  wait_for_it
  DESCRIPTION "Advent of code 2023 - 6th of december"
  VERSION 1.0.0
  LANGUAGES C
)

add_executable(app)

set(SRCDIR "src")
target_sources(app PUBLIC ${SRCDIR}/main.c)

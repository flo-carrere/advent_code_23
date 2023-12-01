cmake_minimum_required(VERSION 3.20)

project(
  trebuchet
  DESCRIPTION "advent of code 2023 - 1st of december"
  VERSION 1.0.0
  LANGUAGES C
)

add_executable(app)

set(SRCDIR "src")

target_sources(app PUBLIC ${SRCDIR}/main.c)

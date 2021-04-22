cmake_minimum_required(VERSION 2.8)

project(test1)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c11 -Wall -Wextra")

add_executable(
test1
one.c
parser.c
scanner.c
token.c
buffer.c
)

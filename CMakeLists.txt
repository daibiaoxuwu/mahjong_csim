cmake_minimum_required(VERSION 3.14)
project(mahjong_csim)

set(CMAKE_CXX_STANDARD 14)

add_executable(mahjong_csim main.cpp Mahjong.cpp Mahjong.h mahjong_choice.cpp BigInteger.h)
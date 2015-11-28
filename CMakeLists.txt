# Laptop angle
# Copyright (C) 2015 Dietrich Daroch <dietr1ch@acm.org>
# Based on sdl-jstest by Ingo Ruhnke
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# To get the GNU General Public License visit gnu.org/licenses

cmake_minimum_required(VERSION 3.0)
project(joyAngle VERSION 0.1.0)

find_package(SDL REQUIRED)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c11")

if(WARNINGS)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pedantic -Wall -Wextra -Wnon-virtual-dtor -Weffc++")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wold-style-cast -Wshadow -Wcast-qual -Wconversion")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Winit-self -Wno-unused-parameter")
endif()

if(WERROR)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror")
endif()

add_executable(laptopAngle laptopAngle.c)
target_link_libraries(laptopAngle ${SDL_LIBRARY} m)
target_include_directories(laptopAngle PUBLIC ${SDL_INCLUDE_DIR})


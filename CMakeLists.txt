cmake_minimum_required(VERSION 3.10)
project(Dargon-Lang 
    VERSION 0.1
    DESCRIPTION "The Dargon Programming Language Interpreter"
    HOMEPAGE_URL https://github.com/kylemmorris/dargon-lang)

set(CMAKE_CXX_STANDARD 17)

###############################################################################
## file globbing ##############################################################
###############################################################################

# these instructions search the directory tree when CMake is
# invoked and put all files that match the pattern in the variables
# `sources` and `data`
file(GLOB_RECURSE sources      src/*.cpp src/*.h)
# you can use set(sources src/main.cpp) etc if you don't want to
# use globbing to find files automatically

###############################################################################
## target definitions #########################################################
###############################################################################

# add the data to the target, so it becomes visible in some IDE
add_executable(dargon ${sources})

# just for example add some compiler flags
#target_compile_options(example PUBLIC -std=c++1y -Wall -Wfloat-conversion)

# this lets me include files relative to the root source directory with a <> pair
target_include_directories(dargon PUBLIC src)

###############################################################################
## packaging ##################################################################
###############################################################################

# all install commands get the same destination. this allows us to use paths
# relative to the executable.
install(TARGETS dargon DESTINATION dargon_destination)

# now comes everything we need, to create a package
# there are a lot more variables you can set, and some
# you need to set for some package types, but we want to
# be minimal here
set(CPACK_PACKAGE_NAME "Dargon Lang")
set(CPACK_PACKAGE_VERSION "0.1")

# we don't want to split our program up into several things
set(CPACK_MONOLITHIC_INSTALL 1)

# This must be last
include(CPack)

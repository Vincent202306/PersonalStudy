
file(GLOB_RECURSE SRCS ./ *.h *.cpp )

add_library(wrapper ${SRCS})
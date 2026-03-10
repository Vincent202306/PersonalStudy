# glStudy.txt: glStudy 的 CMake 项目，在此处包括源代码并定义
# 项目特定的逻辑。
#

#将funcs文件夹纳入编译系统
add_subdirectory(funcs)

#搜索所有的cpp，加入SRCS变量中
aux_source_directory (./ SRCS)
aux_source_directory (./thirdParty SRCS)
#aux_source_directory (./funcs SRCS)

#include_directories 定义该项目中的头文件搜索路径 目的是为了不用在包含头文件时写全路径
include_directories(
	SYSTEM ${CMAKE_CURRENT_SOURCE_DIR}/thirdParty/include
	${CMAKE_CURRENT_SOURCE_DIR}/wrapper
)

link_directories(
	${CMAKE_CURRENT_SOURCE_DIR}/thirdParty/lib
)

add_subdirectory(wrapper)
add_subdirectory(application)

add_definitions(-DDEBUG)

# 将源代码添加到此项目的可执行文件。
#本工程所有cpp文件的编译链接，生成exe
add_executable (glStudy ${SRCS} )


if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET glStudy PROPERTY CXX_STANDARD 20)
endif()

#将funcs.lib链接到当前目标
target_link_libraries(glStudy myFuncs glfw3.lib wrapper Application)

# TODO: 如有需要，请添加测试并安装目标。



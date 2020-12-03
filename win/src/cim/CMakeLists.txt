cmake_minimum_required(VERSION 3.17)
project(cim)

set(CMAKE_CXX_STANDARD 11)

# 预编译宏定义
add_definitions(-D CIM_DLL_EXPORTS -D _WIN32_WINNT=0x0601)

# 源文件
aux_source_directory(./ src_list)
aux_source_directory(base src_list)
aux_source_directory(core src_list)
aux_source_directory(core/pb src_list)
aux_source_directory(test src_list)

# 包含目录
include_directories(.)
include_directories(../third_party/protobuf/include)
include_directories(../third_party/asio-1.18.0/include)
include_directories(../third_party/spdlog/include)

# 库目录
link_directories(../third_party/spdlog/lib/Debug)
link_directories(../third_party/protobuf/lib/win32/Debug)

# 编译
add_executable(cim_core main.cpp ${src_list})
#add_library(cim_core SHARED ${src_list} test/main.cpp)

# 链接
target_link_libraries(cim_core libprotobufd spdlogd)

set (Main_SRCS main.cpp)
include_directories(${PROJECT_SOURCE_DIR}/Lib/src/)

#  if(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
#
#  include_directories(/usr/local/include)
#  include_directories(/usr/local/opt/openssl/include)
#  link_directories(/usr/local/lib)
#  link_directories(/usr/local/opt/openssl/lib)
#  link_directories(/usr/local/Cellar/libuv/1.11.0/lib)
#
#  endif(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")

add_executable(LinearSolver ${Main_SRCS})
target_link_libraries(Lib)

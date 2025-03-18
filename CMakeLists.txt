cmake_minimum_required(VERSION 3.8)
project(mol_b00_123)

# Default to C++14
if(NOT CMAKE_CXX_STANDARD)
set(CMAKE_CXX_STANDARD 14)
endif()

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
add_compile_options(-Wall -Wextra -Wpedantic)
endif()

find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)
find_package(geometry_msgs REQUIRED)

set(ament_dependencies
  rclcpp
  std_msgs
  geometry_msgs
)

add_executable(point_generator src/p_pub.cpp)
ament_target_dependencies(point_generator ${ament_dependencies} )

add_executable(dist_sub_pub src/dist.cpp)
ament_target_dependencies(dist_sub_pub ${ament_dependencies} )

install(DIRECTORY launch
  DESTINATION share/${PROJECT_NAME})

install(TARGETS
point_generator
dist_sub_pub

DESTINATION lib/${PROJECT_NAME})

ament_package()
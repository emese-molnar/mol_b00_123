from launch import LaunchDescription
from launch_ros.actions import Node

def generate_launch_description():
    return LaunchDescription([
        Node(
            package='mol_b00_123',
            executable='point_generator',
            #output='screen',
        ),
        Node(
            package='mol_b00_123',
            executable='dist_sub_pub',
            #output='screen',
        )
    ])
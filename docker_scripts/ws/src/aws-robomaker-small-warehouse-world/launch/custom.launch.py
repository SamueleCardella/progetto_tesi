import os

from ament_index_python.packages import get_package_share_directory

import launch
from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument, IncludeLaunchDescription
from launch.conditions import IfCondition
from launch.launch_description_sources import PythonLaunchDescriptionSource
from launch.substitutions import LaunchConfiguration, PythonExpression


def generate_launch_description():
    # Get the launch directory
    aws_small_warehouse_dir = get_package_share_directory('aws_robomaker_small_warehouse_world')
    gazebo_ros = get_package_share_directory('gazebo_ros')

    # Launch configuration variables specific to simulation
    use_sim_time = LaunchConfiguration('use_sim_time')
    headless = LaunchConfiguration('headless')
    world = LaunchConfiguration('world')

    declare_use_sim_time_cmd = DeclareLaunchArgument(
        'use_sim_time',
        default_value='True',
        description='Use simulation (Gazebo) clock if true')

    declare_headless_cmd = DeclareLaunchArgument(
        'headless',
        default_value='False',
        description='Whether to execute gzclient')

    declare_world_cmd = DeclareLaunchArgument(
        'world',
        default_value=os.path.join(aws_small_warehouse_dir, 'worlds', 'small_warehouse', 'small_warehouse.world'),
        description='Full path to world model file to load')

    # Specify the actions
    start_gazebo_server_cmd = IncludeLaunchDescription(
        PythonLaunchDescriptionSource(
            os.path.join(gazebo_ros, 'launch', 'gzserver.launch.py')),
        launch_arguments={'world': world}.items()
    )

    start_gazebo_client_cmd = IncludeLaunchDescription(
        PythonLaunchDescriptionSource(
            os.path.join(gazebo_ros, 'launch', 'gzclient.launch.py')),
        condition=IfCondition(PythonExpression(['not ', headless]))
    )

    # Create the launch description and populate
    ld = LaunchDescription()

    # Declare the launch options
    ld.add_action(declare_use_sim_time_cmd)
    ld.add_action(declare_headless_cmd)
    ld.add_action(declare_world_cmd)

    # Add the actions
    ld.add_action(start_gazebo_server_cmd)
    ld.add_action(start_gazebo_client_cmd)

    return ld

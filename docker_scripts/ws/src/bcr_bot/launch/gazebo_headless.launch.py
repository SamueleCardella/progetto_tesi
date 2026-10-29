#!/usr/bin/env python3

from os.path import join
from ament_index_python.packages import get_package_share_directory

from launch import LaunchDescription
from launch.actions import (
    DeclareLaunchArgument,
    IncludeLaunchDescription,
    SetEnvironmentVariable,
    AppendEnvironmentVariable,
    ExecuteProcess,
)
from launch.launch_description_sources import PythonLaunchDescriptionSource
from launch.substitutions import LaunchConfiguration

def generate_launch_description():
    # Get package paths
    bcr_bot_path = get_package_share_directory('bcr_bot')
    gazebo_share = get_package_share_directory('gazebo_ros')

    # Launch config variables
    use_sim_time = LaunchConfiguration('use_sim_time', default='true')
    gui = LaunchConfiguration('gui', default='false')
    verbose = LaunchConfiguration('verbose', default='false')
    world_file = LaunchConfiguration(
        'world_file', default=join(bcr_bot_path, 'worlds', 'small_warehouse.sdf')
    )

    # Launch Gazebo headlessly
    gazebo = IncludeLaunchDescription(
        PythonLaunchDescriptionSource(join(gazebo_share, 'launch', 'gazebo.launch.py')),
        launch_arguments={
            'gui': gui,
            'verbose': verbose,
            'world': world_file,
        }.items()
    )

    # Spawn robot
    spawn_bcr_bot_node = IncludeLaunchDescription(
        PythonLaunchDescriptionSource(join(bcr_bot_path, 'launch', 'bcr_bot_gazebo_spawn.launch.py'))
    )

    # Launch teleop in xterm
    teleop_keyboard_process = ExecuteProcess(
        cmd=['xterm', '-e', 'ros2', 'run', 'teleop_twist_keyboard', 'teleop_twist_keyboard'],
        output='screen'
    )

    return LaunchDescription([
        # Environment setup
        AppendEnvironmentVariable(
            name='GAZEBO_MODEL_PATH',
            value=join(bcr_bot_path, 'models')
        ),
        SetEnvironmentVariable(
            name='GAZEBO_RESOURCE_PATH',
            value='/usr/share/gazebo-11:' + join(bcr_bot_path, 'worlds')
        ),

        # Declare args
        DeclareLaunchArgument('world', default_value=world_file),
        DeclareLaunchArgument('gui', default_value='false'),
        DeclareLaunchArgument('verbose', default_value='false'),
        DeclareLaunchArgument('use_sim_time', default_value=use_sim_time),

        # Launch actions
        gazebo,
        spawn_bcr_bot_node,
        teleop_keyboard_process,
    ])

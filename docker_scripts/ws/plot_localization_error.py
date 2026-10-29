import rclpy
from rclpy.serialization import deserialize_message
from rosidl_runtime_py.utilities import get_message
import numpy as np
import matplotlib.pyplot as plt
from nav_msgs.msg import Odometry
import os
from rosbag2_py import SequentialReader, StorageOptions, ConverterOptions
import math


def euler_from_quaternion(q):
    # Converts quaternion to yaw (heading) in radians
    x, y, z, w = q
    siny_cosp = 2 * (w * z + x * y)
    cosy_cosp = 1 - 2 * (y * y + z * z)
    return math.atan2(siny_cosp, cosy_cosp)


def load_odometry_msgs(bag_path, topic_name):
    reader = SequentialReader()
    storage_options = StorageOptions(uri=bag_path, storage_id='sqlite3')
    converter_options = ConverterOptions(input_serialization_format='cdr', output_serialization_format='cdr')
    reader.open(storage_options, converter_options)

    type_map = {}
    odom_data = []

    while reader.has_next():
        topic, data, timestamp = reader.read_next()
        if topic not in type_map:
            type_map[topic] = get_message(reader.get_all_topics_and_types()[0].type)

        if topic == topic_name:
            msg_type = get_message('nav_msgs/msg/Odometry')
            msg = deserialize_message(data, msg_type)
            odom_data.append((timestamp * 1e-9, msg))  # seconds

    return odom_data


def find_closest(timestamp, ground_truth):
    """Find closest timestamp in ground truth to the given timestamp"""
    times = [t for t, _ in ground_truth]
    idx = np.argmin(np.abs(np.array(times) - timestamp))
    return ground_truth[idx]


def compute_errors(odom_filtered, ground_truth):
    pos_errors = []
    yaw_errors = []
    times = []

    for t_f, msg_f in odom_filtered:
        t_gt, msg_gt = find_closest(t_f, ground_truth)

        # Position error
        pf = msg_f.pose.pose.position
        pt = msg_gt.pose.pose.position
        pos_err = np.sqrt((pf.x - pt.x) ** 2 + (pf.y - pt.y) ** 2 + (pf.z - pt.z) ** 2)
        pos_errors.append(pos_err)

        # Heading (yaw) error
        qf = msg_f.pose.pose.orientation
        qt = msg_gt.pose.pose.orientation
        yaw_f = euler_from_quaternion([qf.x, qf.y, qf.z, qf.w])
        yaw_t = euler_from_quaternion([qt.x, qt.y, qt.z, qt.w])
        yaw_err = abs((yaw_f - yaw_t + np.pi) % (2 * np.pi) - np.pi)  # wrap [-π, π]
        yaw_errors.append(np.degrees(yaw_err))

        times.append(t_f)

    return times, pos_errors, yaw_errors

def extract_xy(odom_data):
    xs = []
    ys = []
    for _, msg in odom_data:
        pos = msg.pose.pose.position
        xs.append(pos.x)
        ys.append(pos.y)
    return xs, ys


def plot_errors(times, pos_errors, yaw_errors, xy_filtered, xy_ground_truth):
    plt.figure(figsize=(18, 5))

    # Position Error
    plt.subplot(1, 3, 1)
    plt.plot(times, pos_errors, label="Position Error (m)")
    plt.xlabel("Time (s)")
    plt.ylabel("Position Error (m)")
    plt.grid(True)
    plt.title("Position Error Over Time")

    # Heading Error
    plt.subplot(1, 3, 2)
    plt.plot(times, yaw_errors, label="Heading Error (deg)", color='orange')
    plt.xlabel("Time (s)")
    plt.ylabel("Heading Error (deg)")
    plt.grid(True)
    plt.title("Heading Error Over Time")

    # XY Trajectories
    plt.subplot(1, 3, 3)
    plt.plot(xy_filtered[0], xy_filtered[1], label="Filtered Odometry", linewidth=2)
    plt.plot(xy_ground_truth[0], xy_ground_truth[1], label="Ground Truth", linestyle='--', linewidth=2)
    plt.xlabel("X position (m)")
    plt.ylabel("Y position (m)")
    plt.title("2D Trajectory")
    plt.legend()
    plt.axis("equal")
    plt.grid(True)

    plt.tight_layout()
    plt.show()


def main():
    rclpy.init()

    bag_path = "/home/ws/rosbag2_2025_06_24-16_59_14"  
    odom_filtered_topic = "/odom/filtered"
    ground_truth_topic = "/p3d_ground_truth"

    print("Loading messages...")
    odom_filtered = load_odometry_msgs(bag_path, odom_filtered_topic)
    ground_truth = load_odometry_msgs(bag_path, ground_truth_topic)

    print(f"Loaded {len(odom_filtered)} /odom/filtered msgs")
    print(f"Loaded {len(ground_truth)} /p3d_ground_truth msgs")

    times, pos_errors, yaw_errors = compute_errors(odom_filtered, ground_truth)

    xy_filtered = extract_xy(odom_filtered)
    xy_ground_truth = extract_xy(ground_truth)

    plot_errors(times, pos_errors, yaw_errors, xy_filtered, xy_ground_truth)

    rclpy.shutdown()


if __name__ == "__main__":
    main()

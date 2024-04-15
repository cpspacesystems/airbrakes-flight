# ROS2 Setup

This directory contains two shell scripts: `build_ros2.sh` that builds the ROS2
Docker container image from `ROS2.Dockerfile` and `run_ros2.sh` that runs the
container. Running the following will perform all steps necessary for first time
setup.

```bash
bash build_ros2.sh
bash run_ros2.sh
```

If you want to run the ROS2 environment again, use:

```bash
bash run_ros2.sh
```

I'll look into persistent ROS2 containers and/or filesystem mounting soon. -
Spandan

## Relevant Sources

https://hub.docker.com/r/osrf/ros/tags

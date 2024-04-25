ARG DOMAIN_ID=42

FROM osrf/ros:humble-desktop-full

# See https://docs.ros.org/en/humble/Tutorials/Beginner-CLI-Tools/Configuring-ROS2-Environment.html for details
RUN apt-get update -y; \
		apt-get upgrade -y; \
		source /opt/ros/humble/setup.bash; \
		echo "source /opt/ros/humble/setup.bash" >> ~/.bashrc; \
		export ROS_DOMAIN_ID=${ROS_DOMAIN_ID}; \
		echo "export ROS_DOMAIN_ID=${DOMAIN_ID}" >> ~/.bashrc

RUN apt install ros-humble-turtlesim




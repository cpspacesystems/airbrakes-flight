FROM osrf/ros:humble-desktop-full
ENV DOMAIN_ID=42
CMD ["bash"]

# See https://docs.ros.org/en/humble/Tutorials/Beginner-CLI-Tools/Configuring-ROS2-Environment.html for details
RUN apt-get update -y; \
		apt-get upgrade -y; \
		source /opt/ros/humble/setup.bash; \
		echo "source /opt/ros/humble/setup.bash" >> ~/.bashrc; \
		export ROS_DOMAIN_ID=${DOMAIN_ID}; \
		echo "export ROS_DOMAIN_ID=${DOMAIN_ID}" >> ~/.bashrc; \
		apt-get install tmux -y; \
		echo "tmux set -g mouse on" >> ~/.bashrc

RUN apt install ros-humble-turtlesim

ENTRYPOINT ["tmux", "new", "-s", "ros2"]




FROM osrf/ros:humble-desktop-full
ENV DOMAIN_ID=42
CMD ["bash"]

# See https://docs.ros.org/en/humble/Tutorials/Beginner-CLI-Tools/Configuring-ROS2-Environment.html for details
RUN apt-get update -y; \
		apt-get upgrade -y; \
		apt-get install tmux -y; \
		apt-get install wget -y; \
		mkdir -p /etc/udev/rules.d; \
    wget -P /etc/udev/rules.d/ https://www.pjrc.com/teensy/00-teensy.rules

RUN useradd -m cpss && echo "cpss:cpss" | chpasswd && adduser cpss sudo

WORKDIR /home/pwd

RUN apt install ros-humble-turtlesim

USER cpss
RUN echo "tmux set -g mouse on" >> ~/.bashrc; \
		source /opt/ros/humble/setup.bash; \
		export ROS_DOMAIN_ID=${DOMAIN_ID}; \
		echo "export ROS_DOMAIN_ID=${DOMAIN_ID}" >> ~/.bashrc; \
		echo "source /opt/ros/humble/setup.bash" >> ~/.bashrc

ENTRYPOINT ["tmux", "new", "-s", "ros2"]




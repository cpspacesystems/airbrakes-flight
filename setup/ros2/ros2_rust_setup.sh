# Cargo's required for the buildscripts provided in the ros2-rust repo
sudo apt install cargo

# These steps are provided in https://github.com/ros2-rust/ros2_rust

# Install ROS 2 as described in https://docs.ros.org/en/humble/Installation.html
# Assuming you installed the minimal version of ROS 2, you need these additional packages:
sudo apt install -y git libclang-dev python3-pip python3-vcstool # libclang-dev is required by bindgen
# Install these plugins for cargo and colcon:
cargo install --debug cargo-ament-build  # --debug is faster to install
pip install git+https://github.com/colcon/colcon-cargo.git
pip install git+https://github.com/colcon/colcon-ros-cargo.git

cd ros2rust_ws
cd src/ros2_rust 
git pull
cd ../../
vcs import src < src/ros2_rust/ros2_rust_humble.repos
. /opt/ros/humble/setup.sh
colcon build

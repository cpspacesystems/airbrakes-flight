# airbrakes-flight

## Quickstart

> If you're on a Mac, follow the steps under "Step-by-Step Guide" on [this page](https://gist.github.com/sorny/969fe55d85c9b0035b0109a31cbcb088) first.

Run

```bash
bash speedystart.sh
```

to instantly start the project. You might have to stop any `cpss-ros2`
containers running on your machine via `docker stop cpss-ros2` if you've
run the script before. You'll be dropped into a `tmux` session.

> It might take a hot second to run; it's building a whole Docker image.

Your current directory is mounted in `/home/pwd` in the container. Edits made in
the container will be reflected in real time on your host machine and vice versa--so the ideal workflow is to develop on your host machine using your favorite IDE, then run the changes in the ROS2 container that the script launches. You don't have to open/close any windows or refresh anything; the mounted directory just updates.

Look up how to use `tmux`; it's how you'll open different terminal windows at
the same time (as ROS2 frequently requires). In particular, learn how to create
panes, which split one terminal window into two. Windows might also be useful for creating "browser tab"-like setups.

## Rust Setup

Enter the container using the steps above. From **inside the container**, run:

```bash
bash setup/ros2/ros2_rust_setup.sh
```

This will install the necessary dependencies for the Rust code to run, including Cargo. You can now create ROS2 Rust projects as described in the ROS2 Rust [tutorial](https://github.com/ros2-rust/ros2_rust/blob/main/docs/writing-your-first-rclrs-node.md)

## Docker Setup

You'll need Docker for this. [Here's a setup tutorial](https://www.docker.com/get-started/).


## Flashing the Teensy with Micro-ROS Code
- Run `sudo apt install python3-venv`
- Give yourself permisison to write to the teensy
 	- in `/etc/udev/rules.d`, run  `sudo wget https://www.pjrc.com/teensy/00-teensy.rules`
- Open VSCode, and install PlatformIO extension for VSCode
- Clone the repo and Open the micro-ros-demo-project
	- MAKE SURE TO CLONE WITH `--recurse-submodules` FLAG (necessary for micro-ros)
- Plug in the teensy 
- Open the Platformio-Projects folder, click on the .ini file, then build and upload the project using the small right arrow in the bottom of your IDE 
- If you get any errors during this process, try restarting VSCode

## Running the Microcontroller code
For this task, We need to run the micro-ros-agent, THEN plug in the teensy. there are 2 methods:
- Building the micro-ros-agent
	- make sure the microros submodule is initialized correctly (cloned with --recurse-submodules, or initialized submodules after cloning)
	- build the agent:
		- cd into `microros_ws`
		- `sudo usermod -a -G dialout $USER`
		- `sudo apt update && sudo apt install python3-rosdep &&  sudo rosdep init  && rosdep update`
		- `rosdep install --from-paths src --ignore-src -y`
		- `sudo apt-get install python3-pip`
		- `colcon build`
		- `source install/local_setup.bash`
		- `ros2 run micro_ros_setup create_agent_ws.sh`
		- `ros2 run micro_ros_setup build_agent.sh`
	- From this point on, you never need to build again on your machine. Anytime you want to use te agent, cd into `microros_ws` and use the following commands
		- `source install/local_setup.bash`
		- `ros2 run micro_ros_agent micro_ros_agent serial --dev /dev/ttyACM0`
			- if ttyACM0 doesn't work, try ttyACM1 
	- After this, you should see your agent start, and if the teensy is created you should see all the subscribers and timers start up
	- To see your nodes and topic data running, you can use the following commands in any terminal:
		- `ros2 node list`
		- `ros2 topic list`
		- `ros2 topic echo /put/topic/name/here`

## Adding new sensors and effector code
Adding new code should be a fairly easy process if you already understand the processes behind ROS.
Inside this repo is the MICRO-ROS-DEMO project, where you can add your sensors and effectors. Here's how:
- Note that this project represents a single node. Each file in "handlers" corresponds to one or more related publishers+timers and/or subscribers (referred to as handlers). To add your code, you'll write a new .hpp file in the handlers directory, then add it to config.hpp
- In the MICRO-ROS-DEMO projects, you should see a number of c++ files. Here's a breakdown of the directories:
	- config -> Contains the config.hpp file you'll use to add your code to this node. Once you create your own c++ file, you can copy the structure of how the other c++ files added their handlers in the 2 functions and to the constant at the top. If you do it right it should just work when the node starts up. 
	- handlers -> the actual code for communicating with hardware. Go ahead and create a file here for your new software. This is the only file you need to create. In this directory should be a bunch of scripts for individual sensors, along with `daylight_sensor.hpp` as an example publisher or sensor, and `light_switch.hpp` as an example of 2 subscribers or effectors. Yo can copy either light switch or daylight sensor to use as a template based on if you're writing an effector or sensor, and refer to the other sensor files if you are a little stuck on where to go.
	- support -> included by every file. Contains helper functions and macros. You never need to edit this file
	- main.cpp -> Runs the node and connects everything together. You never need to edit this file
- TLDR: follow these steps
	1. in handlers/, create a new file and use either daylight_sensor.hpp or light_switch.hpp as a template 
	2. in config/config.hpp, add the information for your code just like the other sensors/effectors
	3. build the code, flash the teensy, start the agent, and it should just work.
	
If you have any questions on Micro-ROS or this demo project, DM Cameron Wolff on teams



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

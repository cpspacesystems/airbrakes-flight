# airbrakes-flight

## Quickstart

Run

```bash
bash speedystart.sh
```

to instantly start the project. You might have to stop any `cpss-ros2`
containers running on your machine via `docker stop cpss-ros2` if you've
run the script before. You'll be dropped into a `tmux` session.

Your current directory is mounted in `/home/pwd` in the container. Edits made in
the container will be reflected on your host machine.

Look up how to use `tmux`; it's how you'll open different terminal windows at
the same time (as ROS2 frequently requires). In particular, learn how to create
panes.

## Docker Setup
You'll need Docker for this. [Here's a setup tutorial](https://www.docker.com/get-started/).  

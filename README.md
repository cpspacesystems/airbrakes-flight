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
the container will be reflected in real time on your host machine and vice versa--so the ideal workflow is to develop on your host machine using your favorite IDE, then run the changes in the ROS2 container that the script launches. 

Look up how to use `tmux`; it's how you'll open different terminal windows at
the same time (as ROS2 frequently requires). In particular, learn how to create
panes.

## Docker Setup
You'll need Docker for this. [Here's a setup tutorial](https://www.docker.com/get-started/).  

xhost +local:docker
docker run --platform linux/amd64 -it --rm --name ros2 --pid=host -e DISPLAY=$DISPLAY -v /tmp/.X11-unix:/tmp/.X11-unix:ro ros2

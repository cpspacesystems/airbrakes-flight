imagename="cpss-ros2"
display=docker.for.mac.host.internal:0

docker build --platform linux/amd64 -t $imagename - < setup/ros2/ROS2.Dockerfile
xhost +local:docker
docker run --platform linux/amd64 -it --rm --name $imagename --pid=host -e DISPLAY=$display -v /tmp/.X11-unix:/tmp/.X11-unix:ro -v $(pwd):/home/pwd $imagename

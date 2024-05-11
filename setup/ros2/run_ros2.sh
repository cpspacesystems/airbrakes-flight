imagename="cpss-ros2"

docker build --platform linux/amd64 -t $imagename - < setup/ros2/ROS2.Dockerfile
xhost +local:docker
docker run --platform linux/amd64 -it --rm --name $imagename --pid=host -e DISPLAY=$DISPLAY -v /tmp/.X11-unix:/tmp/.X11-unix:ro -v $(pwd):/home/pwd $imagename 

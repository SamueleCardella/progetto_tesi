docker run -it \
    --env="DISPLAY" \
    --env="QT_X11_NO_MITSHM=1" \
    --volume="/tmp/.X11-unix:/tmp/.X11-unix:rw" \
    --volume="/etc/machine-id:/etc/machine-id:ro" \
    --volume="/home/samuele/docker_scripts/ws:/home/ws" \
    osrf/ros:humble-desktop

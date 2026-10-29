xhost +local:root

docker run -it \
    --env="DISPLAY=$DISPLAY" \
    --env="QT_X11_NO_MITSHM=1" \
    --env="SDL_AUDIODRIVER=dummy" \
    --volume="/tmp/.X11-unix:/tmp/.X11-unix:rw" \
    --volume="/etc/machine-id:/etc/machine-id:ro" \
    --volume="/home/samuele/docker_scripts/ws:/home/ws" \
    --volume="/home/samuele/docker_scripts/useful_alias.sh:/home/useful_alias.sh" \
    --device /dev/snd \
    --net=host \
    --privileged \
    osrf/ros:humble-desktop

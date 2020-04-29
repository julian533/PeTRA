FROM osrf/ros:dashing-desktop
#FROM osrf/ros2:devel
#FROM maxkratz/ros2dashing:latest

RUN apt update -q && apt upgrade -yq

#RUN apt install python3-colcon-common-extensions

RUN apt install libyaml-cpp-dev -y

RUN pip3 install pytest-repeat
RUN pip3 install pytest-cov
RUN pip3 install pytest-rerunfailures

RUN cd ~
RUN git clone https://github.com/AndreasZachariae/PeTRA.git
RUN cd PeTRA
RUN ls -altr /opt/ros/dashing
RUN /bin/bash -c "source /opt/ros/dashing/setup.bash" 
RUN chmod +x /opt/ros/dashing/setup.sh 

RUN . /opt/ros/dashing/setup.sh \
&& colcon build 
#&& source ~/PeTRA/install/setup.bash

RUN cd ~

#CMD ros2 run petra_output_nodes Screen
#CMD ros2 run petra_input_nodes Keyboard
#CMD ros2 run petra_service_nodes Communication
#CMD ros2 run petra_central_control CentralControlUnit

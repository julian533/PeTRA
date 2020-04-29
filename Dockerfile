# Use ubuntu 18.04
FROM ubuntu:18.04
LABEL maintainer="Julian Narr"
ENV DEBIAN_FRONTEND=noninteractive

RUN apt-get update -q && \
    apt-get upgrade -yq && \
    apt-get install -yq wget curl git build-essential vim sudo lsb-release locales bash-completion tzdata

# Run and install ros2:dashing stuff
RUN apt install -y curl gnupg lsb-release
RUN curl -Ls https://raw.githubusercontent.com/ros/rosdistro/master/ros.key | sudo apt-key add -
RUN sh -c 'echo "deb [arch=amd64,arm64] http://packages.ros.org/ros2/ubuntu $(lsb_release -cs) main" > /etc/apt/sources.list.d/ros2-latest.list'
RUN apt update
RUN apt install -y ros-dashing-desktop
RUN apt install -y python3-argcomplete
RUN apt install -y python-rosdep python3-vcstool # https://index.ros.org/doc/ros2/Installation/Linux-Development-Setup/
RUN grep -F "source /opt/ros/dashing/setup.bash" ~/.bashrc || echo "source /opt/ros/dashing/setup.bash" >> ~/.bashrc
RUN grep -F ". /opt/ros/dashing/setup.bash" ~/.bashrc || echo ". /opt/ros/dashing/setup.bash" >> ~/.bashrc
RUN set +u

# Source ros dashing setup-file
RUN /bin/bash -c "source /opt/ros/dashing/setup.bash"
RUN echo "Success installing ROS2 dashing"

# Install catkin library
WORKDIR /root
RUN git clone https://github.com/ros/catkin.git
RUN apt-get -y install cmake python-catkin-pkg python-empy python-nose python-setuptools libgtest-dev build-essential
WORKDIR /root/catkin
RUN mkdir -p build
RUN cmake -DCMAKE_BUILD_TYPE=Release .
RUN make
RUN make install
WORKDIR /root
RUN /bin/bash -c ". /usr/local/setup.bash"
RUN /bin/bash -c ". .bashrc"
RUN grep -F "source /usr/local/setup.bash" ~/.bashrc || echo "source /usr/local/setup.bash" >> ~/.bashrc
RUN grep -F ". /usr/local/setup.bash" ~/.bashrc || echo ". /usr/local/setup.bash" >> ~/.bashrc

RUN cd ~
RUN git clone https://github.com/AndreasZachariae/PeTRA.git
RUN cd PeTRA
RUN ls -altr /opt/ros/dashing
RUN /bin/bash -c "source /opt/ros/dashing/setup.bash" 
RUN chmod +x /opt/ros/dashing/setup.sh 

RUN . /opt/ros/dashing/setup.sh \
&& colcon build \
&& source ~/PeTRA/install/setup.bash

RUN cd ~

#CMD ros2 run petra_output_nodes Screen

# PeTRA
Erste funktionierende Version mit minimalem Funktionsumfang

How to run:

colcon build

source ~/[ws]/install/setup.bash

ros2 run petra_output_nodes Screen

ros2 run petra_input_nodes Keyboard

ros2 run petra_service_nodes Communication

ros2 run petra_central_control CentralControlUnit

# SAP
This Repository contains the necessary launch files to use the UOS Active Perception stack on the Sedna Robot.

## sedna_active_perception
This Folder contains all the necessary config and description files to launch the Sedna Robot with added Kinect support.
It also contains the configuration and map files to launch active perception in our test arena.

## uos_active_perception
This is a modified version of the uos_active_perception stack which is now compatible with ROS-kinetic. 
It also contains additional launch files to start race_object_search on the Sedna Robot.

## Build
This package depends on ROS-kinetic, uos_tools and the [sedna_robot](https://github.com/cebremer/sedna_robot "GitHub:sedna_robot Repo") repository.
## Execution
To run the Sedna Robot with Kinect, map_server and amcl:
```
roslaunch sedna_active_perception sedna_sap.launch
roslaunch sedna_active_perception xtion.launch
```
To run the uos_active_perception stack with Sedna:
`roslaunch race_object_search race_object_search_sedna.launch`

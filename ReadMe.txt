ReadMe file:

MAPPING TASK:
For mapping task we have use slam_toolbox: 

Launch files names:

 -- With /scan data: slam_toolbox2D.launch
 -- With /velodyne_points: slam_toolbox3D.launch
 
 The maps have been generated with first.bag and second.bag.
 
 To save a new map run the following command in the terminal: rosrun map_server map_saver "name_map_desired".
 
NAVIGATION TASK:
 
Launch file name: 
 
 navigation.launch
 
To simulate the navigation task we have use stage_ros, the navigation is done with move_base, the localization is done with amcl.
 
 The global planner is: planner  navfn/NavfnROS or carrot_planner/CarrotPlanner
 The local planner is: teb_local_planner/TebLocalPlannerROS
 
 The map use for the navigation is: map_bag1.pgm which is the one generated with \scan data and first.bag. It has been slightly post-processed with Gimp. It is located in stage folder.
 
 The waypoints are in waypoints/waypoints.cvs, the values are:
 
 x y z
 0 8 0.3
 -6 15 -0.7
 7  3.5 0.6
 -5 1 0.5
 
 With z orientation angle. 
 
 A .png file that shows where the waypoints are located is in the main folder as ref_waypoints.png

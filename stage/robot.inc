define kinect ranger
(
  sensor
  (
    pose [ -0.1 0.0 -0.11 0.0 ]
    size [0.1 0.1 0.1 ]
    range  [0 3]
    fov 360.0
    samples 640
  )
  # generic model properties
  color "black"
  size [ 0.06 0.15 0.03 ]
)

define robot position
(
  pose [ 0.0 0.0 0.0 0.0  ]
  
  localization "odom"


  odom_error [0.1 0.1 0.1 0.1 ]

  size [ 0.6 0.4 0.40 ]
  origin [ 0.0 0.0 0.0 0.0 ]
  gui_nose 1
  drive "diff"
  color "grey"
  
  kinect()
)

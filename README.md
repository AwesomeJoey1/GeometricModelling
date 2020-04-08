# GeometricModelling
Lecture tutorial about geometric modelling. Includes Quaternion rotations, interpolation, bezier curves and b-splines.

## 1. Quaternions
Given a world and view coordinate system, quaternion based transformations are implemented. These include translation of the view coordinate system in drection of the axis of the world coordinate system, rotation of the view coordinate system  the x,y,z-axis of the world coordinate system and rotation of the view system around the x,y,z-axis of the view coordinate system.

### Translation:
<p align="center"> 
  <img src="media/GM_translation.gif">
</p>

### Rotating the view around world axis
<p>
  <img src="media/x_World.gif" width=288px>
  <img src="media/y_World.gif" width=288px>
  <img src="media/z_World.gif" width=288px>
</p>
The bottom left corner of the cube is set to be the origin. The edge to the right, up and inward direction represent the world axis. This is nicely shown by the fact, that rotating around a world axis leaves the corresponding edge unaltered.

Note that after initialization the world and view coordinate system coincide, which is why the first rotation around world or view look the same. In the video captures of the view around world system and view around view system, the view system is translated equally in x,y,z world direction to clearly show the rotations.

## 2. Bezier Curves

## 3. B-Splines

Code Sample Name: tut03_matrices

Feature Area: Direct 3D Mobile

Description: 
	Now that we know how to create a device and render some 2D vertices,
       this tutorial goes the next step and renders 3D geometry. To deal with
       3D geometry we need to introduce the use of 4x4 matrices to transform
       the geometry with translations, rotations, scaling, and setting up our
       camera.

       Geometry is defined in model space. We can move it (translation),
       rotate it (rotation), or stretch it (scaling) using a world transform.
       The geometry is then said to be in world space. Next, we need to
       position the camera, or eye point, somewhere to look at the geometry.
       Another transform, via the view matrix, is used, to position and
       rotate our view. With the geometry then in view space, our last
       transform is the projection transform, which "projects" the 3D scene
       into our 2D viewport.


Usage: 
	Build and run

Relevant APIs/Associated Help Topics: Direct 3D Mobile, SetTransform

Assumptions: 	Direct 3D Mobile support

Requirements: 
    Visual Studio 2005, 
    Windows Mobile 6 Professional SDK,
    Activesync 4.5.

** For more information about this code sample, please see the Windows Mobile SDK help system. **
 

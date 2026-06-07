Code Sample Name: tut04_lights

Feature Area: Direct 3D Mobile

Description: 
	Rendering 3D geometry is much more interesting when dynamic lighting
       is added to the scene. To use lighting in D3DM, you must create one or
       lights, setup a material, and make sure your geometry contains surface
       normals. Lights may have a position, a color, and be of a certain type
       such as directional (light comes from one direction) or point (light
       comes from a specific x,y,z coordinate and radiates in all directions).
       Materials describe the surface of your geometry, specifically, how it 
       gets lit (diffuse color, ambient color, etc.).  Surface normals are
       part of a vertex, and are needed for the D3DM's internal lighting 
       calculations.


Usage: Build and run

Relevant APIs/Associated Help Topics: 
	Direct 3D Mobile, D3DMLIGHT, SetLight, LightEnable

Assumptions: Direct 3D Mobile support

Requirements: 
    Visual Studio 2005, 
    Windows Mobile 6 Professional SDK,
    Activesync 4.5.

** For more information about this code sample, please see the Windows Mobile SDK help system. **
 

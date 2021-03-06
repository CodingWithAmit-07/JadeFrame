#include <glad/glad.h>

#include "BaseApp.h"


/*
List of various (open source) source codes which can be taken for inspiration

	Blender, Godot, Unreal Engine, 
	Ogre, SFML, Cell, MagnumEngine, 
	Hazel/Spark, raylib, Urho3D, 
	Handmade Hero, CrystalSpace3D, 
	Juce, Banshee Engine, NoahGameFrame, 
	olcConsoleGameEngine


Orthographical convention:
	variables and functions in snake case (my_variable, my_function())
	Classes and structs are written in pascal case (MyClass, MyStruct). 
	Maybe (certain) classes will be also in snake case, if it's sufficiently low-level.

	Probably, more client oriented code will have variables and functions with camel case.

	Trailing return type should be the default way.
		Pros:
			- function name is better readable if the return type is long
			- better searchability, since -> type will mostly be the return type
			- better "eye flow"
			- one can indentify functions much better
		Cons:
			- one has to type more
			- functions with short names will be unneccsarily longer
			- VS2019 doesn't show the trailing return type if the function is collapsed


TODO:
	
	- expend the math library especially the various vector classes to support more operations
	- add functions which create random numbers
	- create a general mesh class
		- it should have transformation/model matrix
		- should only update when it is "dirty", to increase performance
		- consider whether classes/structs for specific shapes (e.g. square, circle, cube, etc)
			is worth creating. That would have the added bonus that one could change the properties 
			relatively easy, like size etc.
	- Rendering
		- the BatchRenderer should only send the vertices to the GPU if vertices are "dirty"
			- consider whether it is better to always resend the whole vertex buffer if something changes
				or whether it is better to only resend what changed. Probably one could create a system
				which dynamically decides what to do
		- add textures
		- add Camera
			- should be able to switch between orthographic and perspective mode
		- add some sort of axis grid for better orientation in the 3D space. Can be toggled on and off

	- add ways to render text
	- add a logging system
	- add maybe own GUI system
	- add possible debug mode, so that one can see various performance data on screen

	- create a graphics layer which could potential could be dynamically switched out between software rendering, OpenGL, Vulkan, Direct3D11 and Direct3D12 

*/

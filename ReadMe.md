# Metamorphic
Metamorphic is an engine designed specifically for performance, portability, and conciseness.
The engine may be configured and manipulated in ways where you may milk as much performance as possible
For example, you may compile the engine to not have any physics engine incase you would like to have your own custom physics.
You may also do things such as create meshes with custom integer/floating-point vertex or index types.
Metamorphic is designed to be very flexible with efficiency.

# CMake required build setting definitions
MetamorphicGameType - Type type of game to build the engine for. Supported Values [3D, 2D]

# CMake optional build settings definitions
MetamorphicNoPhysics - if defined, Metamorhpic will be compiled without any physics.  
MetamorphicLibraryType - the type of library to compile metamorphic as. currently only supports static  
MetamorphicReleaseType - Type type of application you are building. Supported Valuer [Release, Dist].  Defaults to Release if not specified

# Metamorphic Game Type
3D and 2D are completely different. Depending on the game type
3D and 2D indicate what kind of vectors comprise the transform components of objects.

# Release Types
Release - For developing/debugging
Dist - The final product. Disables logging and other debugging capabilities
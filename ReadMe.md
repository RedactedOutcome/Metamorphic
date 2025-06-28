# Metamorphic
Metamorphic is an engine designed specifically for performance and portability.
The engine may be configured and manipulated in ways where you may milk as much performance or remove unnecessary features.
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

# CMake project building
Building for cmake via add_subdirectory or Fetch  
1 - Have Required Metamorphic CMake build setting definitions specified before including project  
2 - Link the project. This may be done via   
target_link_libraries(MY_PROJECT PUBLIC Metamorphic)    
Metamorphic already has include directories specified that get propagated to projects that depend on it    

# Building a library for outside of CMake development
Possible but I wont be documentating it for now. Just look at all necessary CMake project definitions needed through the CMakeLists.txt
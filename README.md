OculusCoin
==========

Example implementation for rendering Open Inventor/Coin3D scenes in the Oculus Rift.


Prerequisites
------------

- [Qt5](http://qt-project.org/)
- [Coin](https://bitbucket.org/Coin3D/coin/wiki/Home)
- [Quarter](https://bitbucket.org/Coin3D/quarter)


Build
-----

1. Edit the paths in `src\OculusCoin.pro` or `CMakeLists.txt`.
2. Run `qmake` or `CMake` to generate the files.

If you build using QtCreator, you may need to

1. Add a definition for `COINDIR` to the build environment in the *build settings*.
2. Add the `bin` dir of your Coin installation to the `PATH` variable in the *run settings*.
 
Or

1. Copy `coin3.dll` and `coin3d.dll` to your `build/Debug` folder.
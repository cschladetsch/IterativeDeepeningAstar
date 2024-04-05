# CMake/SDL2/Boost

This is a skeleton project that uses:

* CMake. 3.29
* Boost. 1.88
* SDL2. 2.30
* C++20

To render a 800x800 window for 5 seconds then quit.

## Motivation

Of course, you can also use it to just use either Boost or SDL2.

I found it annoying to start from scratch every time I wanted to start a new project using either or.

If you just want `boost`, delete all the references to `boost` from the `CMakeLists.txt` file, and similarly for `SDL2`.

I made this mostly for myself because I do a lot of cross-platform development including SDL2 for the Raspberry Pi. That's a whole separate issue. For reference you can see my [ChessClock for Pi](https://github.com/cschladetsch/chessclock) repo.

## Building

```bash
$ git clone git@github.com:cschladetsch/CMakeSDLBOOST.git Project
$ cd Project
$ mkdir -p build && cd build
$ cmake ..
$ # Depending on your environment, run make or Visual Studio or whatever
```

## Running

There are two ways to acess SDL2 at runtime. Dynamically linking and statically linking. I made the choice up to you. That adds some complexity, but makes fewest assumptions of usage.

### Dynamically linking SDL2

The application requires `SDL2.dll` to be available for loading at runtime. 

* There are various ways to do this.
* You can try adding your `$SDL2/lib` to your PATH.
* Simplest is to just copy `SDL2.dll` to the root of the project, and run it from there.
* There are better ways, but it's so dependant on your development environment and platform that you'll have to figure it out. On Linux systems look at `LD_LIBRARY_PATH`.


### Statically linking SDL2

Just add `SDL2.lib` as a target link library to the `CMakeLists.txt` file:

```
target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES} SDL2.lib ${Boost_LIBRARIES})
```


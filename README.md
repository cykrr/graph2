# Yet Another Game Engine

Some glue around créme de la créme

## Dependencies

It relies heavily on:

- [glfw](https://github.com/glfw/glfw) (OS) as a Multi-Platform window manager
- [entt](https://github.com/skypjack/entt) (OS) as an Entity Component System
- [glm](https://github.com/g-truck/glm) (OS) as OpenGL math library
- [ImGUI](https://github.com/ocornut/imgui) (submodule) as an Immediate Mode GUI
- [meson](https://mesonbuild.com) (OS) as build system
- [ninja](https://ninja-build.com) (OS) as incremental builder
- [glad](https://github.com/dav1dde/glad) (embedded) as OpenGL bindings for linux



### Arch Linux:

```
# Whatever suits u best
pacman -S glfw-{x11, wayland} glm meson ninja
paru -S entt # Whoops
```
### Windows: 

idk i don't speak spanish


## Building

```
git submodule init
git submodule update
meson build
ninja -C build
./build/fonts # for some reason
```


project(
  'fonts', ['c', 'cpp'],
  version: '0.0.1',
  default_options: ['cpp_std=c++1z']
)


fonts_files = files(
  'src/glad.c',
  'src/util/color.cpp',
  'src/gui/window.cpp',
  'src/gui/program.cpp',
  'src/gui/renderer.cpp',
  'src/gui/input.cpp',
  'src/gui/cam.cpp',
  'src/gui/element.cpp',
  'src/gui/views/rectangle.cpp',
  'src/gui/views/cube.cpp',
  'src/util.cpp',
  'src/gui/views/3drect.cpp',
  'src/gui/views/plane.cpp',
  'src/VAO.cpp',
  'src/VBO.cpp',
  'src/shaders.cpp',
  'src/gui/views/triangle.cpp',
  'src/gui/drawable.cpp',
  'src/instance_drawer.cpp',
  'src/gui.cpp',
  'src/wrappers/gl.cpp',

  './lib/imgui/imgui_impl_glfw.cpp',
  './lib/imgui/imgui_impl_opengl3.cpp',

)


fonts = executable(
  'fonts',
  [ fonts_files + 'src/main.cpp'],
  dependencies:[
    dependency('glfw3'),
    dependency('freetype2'),
    dependency('imgui')
    ],
  include_directories: [
    include_directories('include'),
    include_directories('lib')
    ]
  )

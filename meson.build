
project(
  'fonts', ['c', 'cpp'],
  version: '0.0.1',
  default_options: ['cpp_std=c++1z']
)


fonts_files = files(
  'src/glad.c',
  'src/gui/color.cpp',
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
  'src/menu.cpp',

  './src/imgui_impl_glfw.cpp',
  './src/imgui_impl_opengl3.cpp',

)
vkfw_include = include_directories('lib/vkfw/include')

fonts2 = executable(
  'fonts2',
  [ fonts_files + 'src/main.cpp'],
  dependencies:[
    dependency('glfw3'),
    dependency('freetype2'),
    dependency('imgui')
    ],
  include_directories: [
    include_directories('include'),
    vkfw_include
    ]
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
    vkfw_include
    ]
  )


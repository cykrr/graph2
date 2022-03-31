
project(
  'fonts', ['c', 'cpp'],
  version: '0.0.1',
  default_options: ['cpp_std=c++1z']
)


fonts_files = files(
  'src/main.cpp',
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

)
vkfw_include = include_directories('lib/vkfw/include')

fonts = executable(
  'fonts',
  [ fonts_files],
  dependencies:[
    dependency('glfw3'),
    dependency('freetype2')
    ],
  include_directories: [
    include_directories('include'),
    vkfw_include
    ]
  )

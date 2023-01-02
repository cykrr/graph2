
project(
  'fonts', ['c', 'cpp'],
  version: '0.0.1',
  default_options: ['cpp_std=c++1z']
)


fonts_files = files(
  'main.cpp',
  'src/glad.c',
  'src/util/color.cpp',
  'src/window.cpp',
  'src/program.cpp',
  'src/renderer.cpp',
  'src/input.cpp',
  'src/cam.cpp',
  'src/element.cpp',
  'src/views/rectangle.cpp',
  'src/views/cube.cpp',
  'src/util.cpp',
  'src/views/3drect.cpp',
  'src/views/plane.cpp',
  'src/VAO.cpp',
  'src/VBO.cpp',
  'src/shaders.cpp',
  'src/views/triangle.cpp',
  'src/drawable.cpp',
  'src/instance_drawer.cpp',

  'src/wrappers/gl.cpp',
  'src/wrappers/glfw.cpp',

  'src/scene.cpp',
  'src/entity.cpp',
  'src/entities/cube.cpp',
  'src/entities/triangle.cpp',

  'src/components/rotate.cpp',
  'src/components/scale.cpp',
  'src/components/translate.cpp',
  'src/components/mesh.cpp',

  'src/gui.cpp',

  'src/gui/dock.cpp',
  'src/gui/viewport_window.cpp',

  'src/gui/views/entity/create.cpp',
  'src/gui/views/entity/picker.cpp',
  'src/gui/views/entity/view.cpp',

)

subdir('lib/imgui')


fonts = executable(
  'fonts',
  [ fonts_files, imgui_files ],
  dependencies:[
    dependency('glfw3'),
    dependency('freetype2'),
    ],
  include_directories: [
    include_directories('include'),
    include_directories('lib'),
    imgui_include
    ]
  )

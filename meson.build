
project(
  'fonts', ['c', 'cpp'],
  version: '0.0.1',
  default_options: ['cpp_std=c++1z']
)

subdir('lib/ft2mm')

fonts_files = files(
  'src/main.cpp'
)

fonts = executable(
  'fonts',
  [ fonts_files, ft2mm_files ],
  dependencies:[
    ft2mm_deps,
    dependency('glfw3'),
    dependency('freetype2')
    ],
  include_directories: [
    include_directories('include'),
    ft2mm_include
    ]
  )

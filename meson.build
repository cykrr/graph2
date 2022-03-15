
project(
  'fonts', ['c', 'cpp'],
  version: '0.0.1',
  default_options: ['cpp_std=c++1z']
)

vfiles = files(
  'src/main.cpp'
)

fonts = executable(
  'fonts',
  vfiles,
  dependencies:[
    dependency('glfw3'),
    dependency('freetype2')
    ]
  )

# https://github.com/Karsteski/imgui-meson-project/blob/master/subprojects/imgui-1.81/meson.build

project('imgui', 'cpp',
    version: 'docking',
    license: 'MIT',
)

include_dirs = include_directories('.', 'backends')
sources = ['imgui_demo.cpp', 'imgui_draw.cpp', 'imgui_tables.cpp', 'imgui_widgets.cpp', 'imgui.cpp']

cpp = meson.get_compiler('cpp')
dependencies = []

#We don't need to find any libraries (for now), since they are not used in the cpp file
sources += 'backends/imgui_impl_opengl3.cpp'


glfw_dep = dependency('glfw3')
if glfw_dep.found()
  sources += 'backends/imgui_impl_glfw.cpp'
  dependencies += glfw_dep
endif


imgui = library('imgui',
    sources,
    dependencies: dependencies,
    include_directories: include_dirs,
)

imgui_dep = declare_dependency(include_directories: include_dirs, link_with: imgui)

# https://github.com/Karsteski/imgui-meson-project/blob/master/subprojects/imgui-1.81/meson.build

imgui_include = include_directories('.', 'backends')
imgui_files = ['lib/imgui/imgui_demo.cpp',
               'lib/imgui/imgui_draw.cpp',
               'lib/imgui/imgui_tables.cpp',
               'lib/imgui/imgui_widgets.cpp',
               'lib/imgui/imgui.cpp'
               ]

cpp = meson.get_compiler('cpp')
dependencies = []

#We don't need to find any libraries (for now), since they are not used in the cpp file
imgui_files += 'lib/imgui/backends/imgui_impl_opengl3.cpp'


glfw_dep = dependency('glfw3')
if glfw_dep.found()
  imgui_files += 'lib/imgui/backends/imgui_impl_glfw.cpp'
  dependencies += glfw_dep
endif


imgui = declare_dependency(include_directories: imgui_include)

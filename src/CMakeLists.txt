# CMakeList.txt : projet CMake pour fusee, incluez la source et définissez
# la logique spécifique au projet ici.
#
cmake_minimum_required (VERSION 3.8)

#Set CMAKE options
set(CMAKE_PREFIX_PATH "../librairies/share")

# makes sure we have dependencies on our machine. sets variables for us to be able to pass to the linker
find_package(OpenGL REQUIRED)
find_package(glbinding CONFIG REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
find_package(glm REQUIRED)
find_package(fmt CONFIG REQUIRED)

# Ajoutez une source à l'exécutable de ce projet.
add_executable (fusee "main.cpp" "main.h")

# tells the compiler to use c++ 11 
set_property(GLOBAL PROPERTY CXX_STANDARD 11)

# create a variable which will be the libraries that we want the c++ compiler to link to
set(LIBRARIES fmt::fmt
    fmt::fmt-header-only
    glfw
    ${OPENGL_LIBRARIES}
    glbinding::glbinding
    glbinding::glbinding-aux
    ${STB_INCLUDE_DIRS}
    )
# which libraries our program must link against using the variable we previously set
target_link_libraries(fusee PRIVATE ${LIBRARIES})

# TODO: Ajoutez des tests et installez des cibles si nécessaire.

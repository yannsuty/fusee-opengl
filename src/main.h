// fusee.h�: fichier Include pour les fichiers Include syst�me standard,
// ou les fichiers Include sp�cifiques aux projets.

#pragma once

#include <iostream>
#include <chrono> // current time
#include <cmath> // sin & cos
#include <array>
#include <cstdlib>    // for std::exit()
#include <fmt/core.h> // for fmt::print(). implements c++20 std::format
// this is really important to make sure that glbindings does not clash with
// glfw's opengl includes. otherwise we get ambigous overloads.
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glbinding/glbinding.h>
#include <glbinding/gl/gl.h>


// TODO: R�f�rencez ici les en-t�tes suppl�mentaires n�cessaires � votre programme.

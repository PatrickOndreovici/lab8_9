cmake_minimum_required(VERSION 3.26)
project(lab6)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -Werror")
add_executable(lab6 main.cpp
        Medicament.cpp
        Medicament.h
        MedicamentRepo.cpp
        MedicamentRepo.h
        MedicamentService.cpp
        MedicamentService.h
        MedicamentUI.cpp
        MedicamentUI.h
        MedicamentException.h
        MedicamentServiceTest.cpp
        MedicamentServiceTest.h
        Reteta.h
        Undo.cpp
        Undo.h
)

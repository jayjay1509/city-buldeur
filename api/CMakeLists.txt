cmake_minimum_required(VERSION 3.10)

# Nom du projet
project(MyProject)

# Trouver les packages requis
find_package(SFML 2.5 COMPONENTS system network graphics window audio REQUIRED)

# Rechercher tous les fichiers .cc et .h dans les répertoires src et include
file(GLOB_RECURSE SRC_FILES src/*.cc)
file(GLOB_RECURSE HEADER_FILES include/*.h)

# Ajouter la bibliothèque
add_library(api ${SRC_FILES} ${HEADER_FILES})

# Définir les répertoires d'inclusion pour la bibliothèque
target_include_directories(api PUBLIC include/)

if(ENABLE_PROFILING)
   target_link_libraries(api PRIVATE Tracy::TracyClient)
target_compile_definitions(api PUBLIC TRACY_ENABLE=1)
endif(ENABLE_PROFILING)

# Lier les bibliothèques SFML
target_link_libraries(api PRIVATE sfml-system sfml-network sfml-graphics sfml-window sfml-audio)
cmake_minimum_required(VERSION 3.18)
project(CityBuilder)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


option(ENABLE_PROFILING "Enable Tracy Profiling" OFF)


# Ajouter cette ligne pour utiliser vcpkg
set(CMAKE_TOOLCHAIN_FILE "${CMAKE_CURRENT_SOURCE_DIR}/vcpkg/scripts/buildsystems/vcpkg.cmake" CACHE STRING "Vcpkg toolchain file")

enable_testing()

find_package(GTest CONFIG REQUIRED)
find_package(SFML COMPONENTS system window graphics audio CONFIG REQUIRED)
 find_package(nlohmann_json CONFIG REQUIRED)

if(ENABLE_PROFILING)
   find_package(Tracy CONFIG REQUIRED)
endif(ENABLE_PROFILING)


add_subdirectory(core/)
add_subdirectory(api/)

add_executable(main main.cc)
target_link_libraries(main PRIVATE core api sfml-system sfml-network sfml-graphics sfml-window sfml-audio nlohmann_json::nlohmann_json )


if(ENABLE_PROFILING)
   target_link_libraries(main PRIVATE Tracy::TracyClient)
target_compile_definitions(main PUBLIC TRACY_ENABLE=1)
endif(ENABLE_PROFILING)

#Tracy::TracyClient

# Copy resource files to the build directory
file(COPY ${CMAKE_SOURCE_DIR}/resources DESTINATION ${CMAKE_BINARY_DIR})

set_target_properties(main PROPERTIES LINK_FLAGS "/SUBSYSTEM:WINDOWS")

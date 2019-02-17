cmake_minimum_required(VERSION 3.0)

# Required for YCM to work
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(
	predator_and_prey_sfml
	VERSION 0.0.2
	LANGUAGES CXX
)

add_executable(
	${PROJECT_NAME}
	./src/main.cpp
	./src/predator_and_prey.cpp
)

# SFML
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake/modules" ${CMAKE_MODULE_PATH})
find_package(SFML 2 REQUIRED graphics window system)
find_package(CAVIS 1.2.0 CONFIG REQUIRED)
find_package(flat_matrix 1.2.0 CONFIG REQUIRED)

target_link_libraries(
	${PROJECT_NAME}
	${SFML_LIBRARIES}
	${SFML_DEPENDENCIES}
	CAVIS::CAVIS
)

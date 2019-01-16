cmake_minimum_required(VERSION 3.0)

# Required for YCM to work
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

project(
	preditor_and_prey_sfml
	VERSION 0.0.1
	LANGUAGES CXX
)

add_executable(
	${PROJECT_NAME}
	./src/main.cpp
)

# SFML
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake/modules" ${CMAKE_MODULE_PATH})
find_package(SFML 2 REQUIRED graphics window system)
find_package(CAVIS 0.0.1 CONFIG REQUIRED)

target_link_libraries(
	${PROJECT_NAME}
	${SFML_LIBRARIES}
	${SFML_DEPENDENCIES}
	CAVIS::CAVIS
)

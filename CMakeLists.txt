cmake_minimum_required(VERSION 3.0)

project(
	predator_and_prey_sfml
	VERSION 0.0.2
	LANGUAGES CXX
)

# Dependencies {{{

list(APPEND CMAKE_MODULE_PATH
	"${CMAKE_SOURCE_DIR}/cmake/modules"
)

# SFML
find_package(
	SFML 2 REQUIRED
	graphics window system
)

find_package(CAVIS 1.3.0 CONFIG REQUIRED)
find_package(flat_matrix 1.2.0 CONFIG REQUIRED)

# }}}

# Targets {{{

add_executable(
	${PROJECT_NAME}
	./src/main.cpp
	./src/predator_and_prey.cpp
)

target_link_libraries(
	${PROJECT_NAME}
	PRIVATE
		${SFML_LIBRARIES}
		${SFML_DEPENDENCIES}
		CAVIS::CAVIS
)

# }}}

# Installation {{{

install(
	TARGETS ${PROJECT_NAME}
	RUNTIME DESTINATION bin COMPONENT Runtime
)

# }}}

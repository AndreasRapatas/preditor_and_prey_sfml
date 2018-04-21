
cmake_minimum_required(VERSION 3.0)

# Required for YCM to work
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)


set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)


project(
	preditor_and_prey_sfml
	VERSION 0.0.0
	LANGUAGES CXX
)

# ===========
# Definitions
#============


add_executable(
	${PROJECT_NAME}
	./source/main.cpp
)


# SFML
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake" ${CMAKE_MODULE_PATH})
find_package(SFML 2 REQUIRED network audio graphics window system)
target_link_libraries(
	${PROJECT_NAME} 


	${SFML_LIBRARIES} 
	${SFML_DEPENDENCIES}
)


target_include_directories(
	${PROJECT_NAME}
	INTERFACE
		$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
		$<INSTALL_INTERFACE:include>
)

# =========
# Packaging
# =========

include(CMakePackageConfigHelpers)

write_basic_package_version_file(
	"${PROJECT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake"
	VERSION ${PROJECT_VERSION}
	COMPATIBILITY AnyNewerVersion
)

configure_package_config_file(
	"${PROJECT_SOURCE_DIR}/cmake/${PROJECT_NAME}Config.cmake.in"
	"${PROJECT_BINARY_DIR}/${PROJECT_NAME}Config.cmake"
	INSTALL_DESTINATION lib/cmake/${PROJECT_NAME}
)

install(
	FILES
		"${PROJECT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake"
		"${PROJECT_BINARY_DIR}/${PROJECT_NAME}Config.cmake"
	DESTINATION lib/cmake/${PROJECT_NAME}
)

install(
	TARGETS       ${PROJECT_NAME}
	EXPORT        ${PROJECT_NAME}Targets

	LIBRARY       DESTINATION lib                     COMPONENT Runtime
	RUNTIME       DESTINATION bin                     COMPONENT Runtime
	BUNDLE        DESTINATION bin                     COMPONENT Runtime

	ARCHIVE       DESTINATION lib                     COMPONENT Development
	# INCLUDES      DESTINATION include/${PROJECT_NAME} COMPONENT Development
	PUBLIC_HEADER DESTINATION include/${PROJECT_NAME} COMPONENT Development
)

install(
	EXPORT      ${PROJECT_NAME}Targets
	FILE        ${PROJECT_NAME}Targets.cmake
	NAMESPACE   ${PROJECT_NAME}::
	DESTINATION lib/cmake/${PROJECT_NAME}
)

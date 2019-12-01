cmake_minimum_required(VERSION 3.5)
PROJECT(bomberman)
set(CMAKE_CXX_STANDARD 14)
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")

set(OpenGL_GL_PREFERENCE LEGACY)

FIND_PACKAGE(X11 REQUIRED)
FIND_PACKAGE(OpenGL REQUIRED)

FIND_PATH(IRRLICHT_INCLUDE_DIR irrlicht.h
        PATHS $ENV{IRRDIR}/include
        ${PROJECT_SOURCE_DIR}/irrlicht/include
        )
if (UNIX)
    FIND_PATH(IRRLICHT_LIBRARY_DIR libIrrlicht.a
            PATHS $ENV{IRRDIR}/lib/Linux
            ${PROJECT_SOURCE_DIR}/irrlicht/lib/Linux
            )
			SET(IRRLICHT_LIB "${IRRLICHT_LIBRARY_DIR}/libIrrlicht.a")
			add_definitions( -DSYSTEM="UNIX")
endif (UNIX)
if (WIN32)
	FIND_PATH(IRRLICHT_LIBRARY_DIR Irrlicht.lib
            PATHS $ENV{IRRDIR}/lib/Win32-visualstudio
            ${PROJECT_SOURCE_DIR}/irrlicht/lib/visualstudio
            )
			SET(IRRLICHT_LIB "${IRRLICHT_LIBRARY_DIR}/Irrlicht.lib")
			add_definitions( -DSYSTEM="WIN")
			file(COPY ${PROJECT_SOURCE_DIR}/irrlicht/bin/Win32-VisualStudio/Irrlicht.dll
			DESTINATION ${PROJECT_SOURCE_DIR}
		)
endif (WIN32)

if (CMAKE_BUILD_TYPE MATCHES "^Debug$")
	message(STATUS "Debug mode")
    message(STATUS "${IRRLICHT_LIB}")
	message(STATUS "${IRRLICHT_LIBRARY_DIR}")
	message(STATUS "${PROJECT_SOURCE_DIR}")
endif (CMAKE_BUILD_TYPE MATCHES "^Debug$")

if (CMAKE_BUILD_TYPE MATCHES "^RelWithDebInfo")
	message(STATUS "Release Mode")
endif (CMAKE_BUILD_TYPE MATCHES "^RelWithDebInfo")

INCLUDE_DIRECTORIES(
        ${PROJECT_SOURCE_DIR}/include
        ${X11_INCLUDE_DIR}
        ${OPENGL_INCLUDE_DIR}
        ${IRRLICHT_INCLUDE_DIR}
            )

FILE(GLOB SRCS sources/*.cpp)
ADD_EXECUTABLE(bomberman ${SRCS})
target_link_libraries(bomberman
        ${X11_LIBRARIES}
        ${OPENGL_LIBRARIES}
        ${IRRLICHT_LIB}
        )
if (UNIX)
target_link_libraries(bomberman X11 Xxf86vm Xext GL)
endif(UNIX)
install(
    TARGETS bomberman 
    RUNTIME DESTINATION "${PROJECT_SOURCE_DIR}"
)
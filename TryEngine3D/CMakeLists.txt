SET(CMAKE_MFC_FLAG 6)

CMAKE_MINIMUM_REQUIRED(VERSION 1.6)

PROJECT(TryEngine3D)

IF(WIN32)
  # Remove all the warnings about depreceated stuff from VS2005
  ADD_DEFINITIONS(-D_CRT_SECURE_NO_WARNINGS)
  # Needed by GEL due to its fancy iterator work
  ADD_DEFINITIONS(-D_SECURE_SCL=0)
  ADD_DEFINITIONS(-D_HAS_ITERATOR_DEBUGGING=0)
ENDIF(WIN32)

  macro( cache_set var )
    set ( ${var} ${ARGN} CACHE INTERNAL "" )  
    set ( ${var} ${ARGN} CACHE INTERNAL "" )  
  endmacro()
  
  macro( cache_get var )
    set ( ${var} )  
  endmacro()
    # adds elements to an internal cached list  
  macro( add_to_cached_list listname )
    cache_get ( ${listname} )
    set( _ATC_${listname}_tmp  ${${listname}} )
    if ( NOT "${ARGN}" STREQUAL "" )
      list( APPEND _ATC_${listname}_tmp ${ARGN} )
    endif()
    cache_set ( ${listname} ${_ATC_${listname}_tmp} )
  endmacro()

cache_set(3RD_PARTY_INCLUDE_DIRS   "" )
cache_set(3RD_PARTY_LIBRARIES      "" )
cache_set(3RD_PARTY_LIBRARIES_DIRS "" ) 

include(SetupBoost.cmake)

FIND_PACKAGE(OpenGL)
IF (OPENGL_FOUND)
MESSAGE("OPENGL FOUND")
MESSAGE(${OPENGL_LIBRARIES})
ELSE (OPENGL_FOUND)
MESSAGE("OPENGL NOT FOUND")
SET(OPENGL_gl_LIBRARY opengl32)
SET(OPENGL_glu_LIBRARY glu32)
ENDIF (OPENGL_FOUND)
FIND_LIBRARY( GLEW_LIBRARY glew32)

add_to_cached_list( 3RD_PARTY_LIBRARIES_DIRS
${TryEngine3D_BINARY_DIR}/../include/GEL/lib
)
add_to_cached_list( 3RD_PARTY_INCLUDE_DIRS
${TryEngine3D_BINARY_DIR}/../include/GEL/include
)
add_to_cached_list( 3RD_PARTY_LIBRARIES_DIRS
${TryEngine3D_BINARY_DIR}/../include/SDL-1.3/lib
)
add_to_cached_list( 3RD_PARTY_INCLUDE_DIRS
${TryEngine3D_BINARY_DIR}/../include/SDL-1.3/include
)

add_to_cached_list(3RD_PARTY_INCLUDE_DIRS
${TryEngine3D_BINARY_DIR}/../include
)
add_to_cached_list(3RD_PARTY_LIBRARIES  
	CGLA
	Geometry
	${OPENGL_gl_LIBRARY}
	${OPENGL_glu_LIBRARY}
	${OPENGL_glew_LIBRARY}
	${GLEW_LIBRARY}
	SDL
	SDL_image
    SDLmain # Sadly not included in SDL_LIBRARY variable
)


SET(LIBRARY_OUTPUT_PATH ${TryEngine3D_BINARY_DIR}/lib)
SET(EXECUTABLE_OUTPUT_PATH ${TryEngine3D_BINARY_DIR}/bin)

add_subdirectory (src)
add_subdirectory (test) 


 
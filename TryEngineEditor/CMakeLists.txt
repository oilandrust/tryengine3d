# add stuff to use MFC in this executable
SET(CMAKE_MFC_FLAG 6)

CMAKE_MINIMUM_REQUIRED(VERSION 1.6)

PROJECT(TryEngineEditor)
SET(EXECUTABLE_OUTPUT_PATH ${TryEngineEditor_BINARY_DIR}/bin)


#########################SET THE CACHES
  macro( cache_set var )
    set ( ${var} ${ARGN} CACHE INTERNAL "" )  
    set ( ${var} ${ARGN} CACHE INTERNAL "" )  
  endmacro()
cache_set(3RD_PARTY_INCLUDE_DIRS   "" )
cache_set(3RD_PARTY_LIBRARIES      "" )
cache_set(3RD_PARTY_LIBRARIES_DIRS "" ) 
include(SetupBoost.cmake)

##############REMOVE GEL WARNING
IF(WIN32)
  OPTION(DISABLE_VS2005DEPRECATED "Disable the depreceated warnings in VS2005" ON)
  IF(DISABLE_VS2005DEPRECATED)
    ADD_DEFINITIONS(-D_CRT_SECURE_NO_WARNINGS)
    ADD_DEFINITIONS(-D_SCL_SECURE_NO_WARNINGS)
  ENDIF(DISABLE_VS2005DEPRECATED)
ENDIF(WIN32)
ADD_DEFINITIONS(-D_SECURE_SCL=0)
ADD_DEFINITIONS(-D_HAS_ITERATOR_DEBUGGING=0)
##############REMOVE GEL WARNING

#################################################################
##############             CACHE DEPENDENCIES
##TRYENGINE
set( TRYENGINE3D_LIBRARY ../TryEngine3D/lib/Release/TryEngine3D )
set( TRYENGINE3D_INCLUDE_DIR ../TryEngine3D/src )


#QT
FIND_PACKAGE(Qt4)
INCLUDE(${QT_USE_FILE})
set(QT_USE_QTOPENGL TRUE)
set(QT_USE_QGLWIDGET TRUE)
set( QT_USE_QTXML    TRUE )
set( QT_USE_QTMAIN   TRUE )
set( QT_USE_QTSCRIPT  TRUE )
set( QT_USE_QTOPENGL  TRUE )
find_package(Qt4)
ADD_DEFINITIONS(${QT_DEFINITIONS})
INCLUDE( ${QT_USE_FILE} )

#OPENGL
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

#SDL
# REQUIRED does not work in CMake <=2.4.6 for SDL
Find_Package ( SDL REQUIRED )
Find_Package ( SDL_image REQUIRED ) # if using SDL_image
if ( NOT SDL_FOUND )
   message ( FATAL_ERROR "SDL not found!" )
endif ( NOT SDL_FOUND )

FIND_PACKAGE(GEL)
IF(GEL_FOUND)
  INCLUDE(${GEL_USE_FILE})
ENDIF(GEL_FOUND)


add_to_cached_list(3RD_PARTY_LIBRARIES  
	GLGraphics
	CGLA
	Geometry
	${OPENGL_gl_LIBRARY}
	${OPENGL_glu_LIBRARY}
	${OPENGL_glew_LIBRARY}
	${GLEW_LIBRARY}
	${SDL_LIBRARY}
    ${SDLIMAGE_LIBRARY} # if using SDL_image, obviously
    SDLmain # Sadly not included in SDL_LIBRARY variable
)
#################################################################
##############             CACHE DEPENDENCIES




#################################################################
##############             GENERATE QT MOC AND UIS
SET(foo_SRCS
glwidget.cpp
window.cpp
GOInspector.cpp
treemodel.cpp
TransformInspector.cpp
MeshRendererInspector.cpp
)
SET(foo_MOC_HDRS
glwidget.h
window.h
GOInspector.h
Application.h
treemodel.h
TransformInspector.h
MeshRendererInspector.h
)
SET( UIS
   TransformInspector.ui
   TextureInspector.ui
   MeshRendererInspector.ui
   MaterialInspector.ui
)

QT4_WRAP_CPP(foo_MOC_SRCS ${foo_MOC_HDRS})
QT4_WRAP_UI(UI_HDRS ${UIS})
#################################################################
##############             GENERATE QT MOC AND UIS


#################################################################
##############             LINK INCLUDE AND BUILD


include_directories( 
	${GEL_INCLUDE_DIR}
	${SDL_INCLUDE_DIR}
	${TRYENGINE3D_INCLUDE_DIR}
	${3RD_PARTY_INCLUDE_DIRS}
)
link_libraries (
   ${3RD_PARTY_LIBRARIES}
)

#make an executable target, and associate its sources, and declare what
#external libraries its depends on
ADD_EXECUTABLE( TryEngineEditor 
glwidget.h
glwidget.cpp
window.cpp
window.h
trackballcameraQT.h
trackballcameraQT.cpp
${foo_MOC_SRCS}
${foo_SRCS}
${UI_HDRS}
${foo_MOC_HDRS}
TryEngineEditor
GOInspector.cpp
GOInspector.h
Application.h
treemodel.cpp
treemodel.h
GOHierarchyItem.cpp
GOHierarchyItem.h
)

TARGET_LINK_LIBRARIES(TryEngineEditor ${QT_LIBRARIES}
${3RD_PARTY_LIBRARIES}
${TRYENGINE3D_LIBRARY}
)




 
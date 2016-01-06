
#Remove GEL Warning
IF(WIN32)
  OPTION(DISABLE_VS2005DEPRECATED "Disable the depreceated warnings in VS2005" ON)
  IF(DISABLE_VS2005DEPRECATED)
    ADD_DEFINITIONS(-D_CRT_SECURE_NO_WARNINGS)
    ADD_DEFINITIONS(-D_SCL_SECURE_NO_WARNINGS)
  ENDIF(DISABLE_VS2005DEPRECATED)
ENDIF(WIN32)

ADD_DEFINITIONS(-D_SECURE_SCL=0)
ADD_DEFINITIONS(-D_HAS_ITERATOR_DEBUGGING=0)

#Include and link TryEngine3D
include_directories (${TryEngine3D_SOURCE_DIR}/src)
link_directories (${TryEngine3D_BINARY_DIR}/lib)
#Include and link external dependencies
include_directories( 
	${GEL_INCLUDE_DIR}
	${SDL_INCLUDE_DIR}
	${3RD_PARTY_INCLUDE_DIRS}
)
link_libraries (
   ${3RD_PARTY_LIBRARIES}
)

add_executable (ScreenRaycast 
ScreenRaycast)

target_link_libraries (ScreenRaycast 
   CGLA
   Geometry
   TryEngine3D
   GLGraphics
)


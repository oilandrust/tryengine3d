if ( NOT Boost_Setup )

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
  
  
  set(Boost_FIND_VERSION 1.33.1 )
  set(Boost_FIND_VERSION_MAJOR 1 )
  set(Boost_FIND_VERSION_MINOR 33 )
  set(Boost_FIND_VERSION_PATCH 1 )
  
  find_package( Boost)
  
  message( STATUS "Boost include:     ${Boost_INCLUDE_DIRS}" )
  message( STATUS "Boost libraries:   ${Boost_LIBRARIES}" )
  message( STATUS "Boost definitions: ${Boost_DEFINITIONS}" )
      
  add_to_cached_list(3RD_PARTY_INCLUDE_DIRS   ${Boost_INCLUDE_DIRS} )
  add_to_cached_list(3RD_PARTY_LIBRARIES_DIRS ${Boost_LIBRARY_DIRS} )
  add_to_cached_list(3RD_PARTY_DEFINITIONS    ${Boost_DEFINITIONS}  )
  add_to_cached_list(3RD_PARTY_LIBRARIES      ${Boost_LIBRARIES}    )
  
  
  message( STATUS "USING BOOST_VERSION = '${Boost_MAJOR_VERSION}.${Boost_MINOR_VERSION}.${Boost_SUBMINOR_VERSION}'" )
  
endif()
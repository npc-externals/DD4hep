cmake_minimum_required(VERSION 2.8.3 FATAL_ERROR)

include_directories( ${CMAKE_CURRENT_SOURCE_DIR}/include 
                     ${CMAKE_SOURCE_DIR}/DDCore/include 
                     ${ROOT_INCLUDE_DIR})

file(GLOB sources src/*.cpp)
include(DD4hep_XML_setup)

add_library(DDSegmentation SHARED ${sources})
target_link_libraries(DDSegmentation ${DD4hep_LIBRARIES} ${ROOT_LIBRARIES})

SET_TARGET_PROPERTIES( DDSegmentation PROPERTIES VERSION ${DD4hep_VERSION} SOVERSION ${DD4hep_SOVERSION})

#---Rootmap generation--------------------------------------------------------------
if(APPLE)
  dd4hep_generate_rootmap_apple(DDSegmentation)
else()
  dd4hep_generate_rootmap(DDSegmentation)
endif()
#--- install target-------------------------------------

install(DIRECTORY include/DDSegmentation
  DESTINATION include
  PATTERN ".svn" EXCLUDE )

install(TARGETS DDSegmentation
  RUNTIME DESTINATION bin
  LIBRARY DESTINATION lib
  )
# to do: add corresponding uninstall...
#-------------------------------------------------------
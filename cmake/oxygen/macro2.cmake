MACRO(GENERATE_DOCUMENTATION DOXYGEN_CONFIG_FILE)
  FIND_PACKAGE(Doxygen)
  SET(DOXYFILE_FOUND false)
  IF(EXISTS ${PROJECT_SOURCE_DIR}/${DOXYGEN_CONFIG_FILE})
    SET(DOXYFILE_FOUND true)
  ENDIF(EXISTS ${PROJECT_SOURCE_DIR}/${DOXYGEN_CONFIG_FILE})

  IF( DOXYGEN_FOUND )
    IF( DOXYFILE_FOUND )
	  # Add target
        ADD_CUSTOM_TARGET(doc ALL ${DOXYGEN_EXECUTABLE} "${PROJECT_SOURCE_DIR}/${DOXYGEN_CONFIG_FILE}" )

	  # Add .tag file and generated documentation to the list of files we must erase when distcleaning

	  # Read doxygen configuration file
	  FILE( READ ${PROJECT_SOURCE_DIR}/${DOXYGEN_CONFIG_FILE} DOXYFILE_CONTENTS )
	  STRING( REGEX REPLACE "\n" ";" DOXYFILE_LINES ${DOXYFILE_CONTENTS} )

	  # Parse .tag filename and add to list of files to delete if it exists
	  FOREACH( DOXYLINE ${DOXYFILE_CONTENTS} )
  	    STRING( REGEX REPLACE ".*GENERATE_TAGFILE *= *([^ ^\n]+).*" "\\1" DOXYGEN_TAG_FILE ${DOXYLINE} )
	  ENDFOREACH( DOXYLINE )
	  # ADD_TO_DISTCLEAN( ${PROJECT_BINARY_DIR}/${DOXYGEN_TAG_FILE} )

	  # Parse doxygen output doc dir and add to list of files to delete if it exists
	  FOREACH( DOXYLINE ${DOXYFILE_CONTENTS} )
	    STRING( REGEX REPLACE ".*OUTPUT_DIRECTORY *= *([^ ^\n]+).*" "\\1" DOXYGEN_DOC_DIR ${DOXYLINE} )
	  ENDFOREACH( DOXYLINE )
	  # ADD_TO_DISTCLEAN( ${PROJECT_BINARY_DIR}/${DOXYGEN_DOC_DIR} )
	  # ADD_TO_DISTCLEAN( ${PROJECT_BINARY_DIR}/${DOXYGEN_DOC_DIR}.dir )

     ELSE( DOXYFILE_FOUND )
	MESSAGE( STATUS "Doxygen configuration file not found - Documentation will not be generated" )
     ENDIF( DOXYFILE_FOUND )
  ELSE(DOXYGEN_FOUND)
    MESSAGE(STATUS "Doxygen not found - Documentation will not be generated")
  ENDIF(DOXYGEN_FOUND)
ENDMACRO(GENERATE_DOCUMENTATION)
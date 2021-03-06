# The MIT License (MIT)
# 
# Copyright (c) 2013-2015 Tino Bog
# 
# Permission is hereby granted, free of charge, to any person obtaining a copy of
# this software and associated documentation files (the "Software"), to deal in
# the Software without restriction, including without limitation the rights to
# use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
# the Software, and to permit persons to whom the Software is furnished to do so,
# subject to the following conditions:
# 
# The above copyright notice and this permission notice shall be included in all
# copies or substantial portions of the Software.
# 
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
# FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
# COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
# IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
# CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

CMAKE_MINIMUM_REQUIRED (VERSION 2.8)

#------------------------------------------------------------------------------
# NAME THE PROJECT -->	ROOT SOURCE: ${($PROJECT)_SOURCE_DIR} 
#						ROOT BINARY: ${($PROJECT)_BINARY_DIR}
#------------------------------------------------------------------------------
PROJECT ( autoargs CXX )

#------------------------------------------------------------------------------
# SET OPTIONS
#------------------------------------------------------------------------------
OPTION ( AUTOARGS_ENABLE_TESTING "Enable tests for AutoArgs library" ON )
OPTION ( AUTOARGS_ADD_CXX11_FLAG "Add -std=c++11 to CMAKE_CXX_FLAGS" ON )
OPTION ( AUTOARGS_HEADER_ONLY "Use AutoArgs as header only library" ON )
OPTION ( AUTOARGS_BUILD_EXAMPLES "Compile the accompanying examples" ON )

IF ( ${AUTOARGS_ADD_CXX11_FLAG} )
  
  	SET( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11" )

ENDIF ( ${AUTOARGS_ADD_CXX11_FLAG} )

IF ( ${AUTOARGS_HEADER_ONLY} )

	ADD_DEFINITIONS( -DAUTOARGS_HEADER_ONLY )

ELSE ( ${AUTOARGS_HEADER_ONLY} )


	ADD_LIBRARY ( ${PROJECT_NAME} 
				  SHARED
			      source/autoargs.cpp
				)
	
ENDIF ( ${AUTOARGS_HEADER_ONLY} )


#------------------------------------------------------------------------------
# INCLUDE DIRECTORY
#------------------------------------------------------------------------------
INCLUDE_DIRECTORIES ( . )	

#------------------------------------------------------------------------------
# CREATE TARGETS THAT BUILD AND START THE TEST RUNNER
#------------------------------------------------------------------------------

IF ( ${AUTOARGS_ENABLE_TESTING} )

    FILE ( GLOB TESTSOURCES test/*.cpp )	

    FILE ( COPY
           ${CMAKE_CURRENT_SOURCE_DIR}/test/defaultInputFileReaderData.in
           DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/)

    ADD_EXECUTABLE ( ${PROJECT_NAME}_testrunner ${TESTSOURCES} )
    
	IF ( NOT ${AUTOARGS_HEADER_ONLY} )
    	TARGET_LINK_LIBRARIES ( ${PROJECT_NAME}_testrunner ${PROJECT_NAME} )	
	ENDIF ( NOT ${AUTOARGS_HEADER_ONLY} )
       
  	# build target to run tests contained in the runner
	ADD_CUSTOM_TARGET ( 
    run_${PROJECT_NAME}_tests 
    ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}_testrunner
    COMMENT "Running tests for ${PROJECT_NAME}" VERBATIM 
	)
  
  	# build runner before execution if changes have been made to sources
	ADD_DEPENDENCIES ( run_${PROJECT_NAME}_tests 
	                   ${PROJECT_NAME}_testrunner )

ENDIF ( ${AUTOARGS_ENABLE_TESTING} )

#------------------------------------------------------------------------------
# CREATE EXAMPLES
#------------------------------------------------------------------------------

IF ( ${AUTOARGS_BUILD_EXAMPLES} )

    ADD_EXECUTABLE ( hello1 examples/hello1.cpp)
    ADD_EXECUTABLE ( hello2 examples/hello2.cpp)
    ADD_EXECUTABLE ( hello3 examples/hello3.cpp)

	IF ( NOT ${AUTOARGS_HEADER_ONLY} )
    	TARGET_LINK_LIBRARIES ( hello3 ${PROJECT_NAME} )
	ENDIF ( NOT ${AUTOARGS_HEADER_ONLY} )

ENDIF ( ${AUTOARGS_BUILD_EXAMPLES} )

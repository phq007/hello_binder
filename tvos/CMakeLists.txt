#################################################
# Main CMakeLists               		 #
#
# Ddate:
#                             #
# Author : phq@tcl.com                       #
##################################################
project(BINDER_SERVICE C CXX)
SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
SET(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin/lib)

cmake_minimum_required(VERSION 2.6)

if(WIN32)
	SET(platform win32)
elseif(MIPS)
	SET(platform mips)
elseif(ARM)
	SET(platform arm)
else()
	SET(platform linux)
endif()

INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/include/mdroid)
INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/binder_interface)
INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/lib/${platform}/include)
LINK_DIRECTORIES(${PROJECT_SOURCE_DIR}/lib/${platform}/lib)
LINK_DIRECTORIES(${PROJECT_SOURCE_DIR}/lib/mdroid/lib/${platform})

if(WIN32)
	MESSAGE("WIN32 BUILD")
	SET(CompilerFlags
	    CMAKE_CXX_FLAGS
	    CMAKE_CXX_FLAGS_DEBUG
	    CMAKE_CXX_FLAGS_RELEASE
	    CMAKE_C_FLAGS
	    CMAKE_C_FLAGS_DEBUG
	    CMAKE_C_FLAGS_RELEASE
        )
	foreach(CompilerFlag ${CompilerFlags})
	  STRING(REPLACE "/MD" "/MT" ${CompilerFlag} "${${CompilerFlag}}")
	endforeach()
	INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/lib/${platform}/include/glib-2.0)
elseif(ARM)
	MESSAGE("ARM BUILD")
	SET(CMAKE_SYSTEM_NAME "linux")
	set(CMAKE_C_COMPILER "arm-none-linux-gnueabi-gcc")#arm-none-linux-gnueabi // arm-linux-androideabi
	set(CMAKE_CXX_COMPILER "arm-none-linux-gnueabi-g++")
	set(CMAKE_LD "arm-none-linux-gnueabi-ld")
	add_definitions("-DARM_BUILD=1")
	add_definitions("-DENABLE_TCL_FACTORY_MENU=1")	

	################# for MS6308  ####################
	#set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -EL -mhard-float")
	#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -EL -mhard-float")
	set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g -O2 -Wall")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -O2 -Wall")
	################# end for MS6308  ####################	
	INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/lib/${platform}/include/tvos)
	INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/lib/${platform}/include/apm)
	INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/lib/${platform}/include/mstarsdk)
	INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/lib/${platform}/include/dfb/target/directfb)
	LINK_DIRECTORIES(${PROJECT_SOURCE_DIR}/lib/${platform}/lib/utopia)
elseif(MIPS)
	MESSAGE("MIPS BUILD")
	SET(CMAKE_SYSTEM_NAME "linux")
	set(CMAKE_C_COMPILER "mips-linux-gnu-gcc")
	set(CMAKE_CXX_COMPILER "mips-linux-gnu-g++")
	set(CMAKE_LD "mips-linux-gnu-ld")
	add_definitions("-DGOLIVE_MIPS=1")

	################# for MS6308  ####################
	set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -EL -mhard-float")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -EL -mhard-float")
	set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g -O2 -Wall")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -O2 -Wall")
	INCLUDE_DIRECTORIES("${PROJECT_SOURCE_DIR}/lib/${platform}/include/dfb/target/directfb")
	INCLUDE_DIRECTORIES("${PROJECT_SOURCE_DIR}/lib/${platform}/include/cairo")
	INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/lib/${platform}/include/glib)
	INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/lib/${platform}/include/freetype2)
	INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/lib/${platform}/include/glib/glib-2.0)
	LINK_DIRECTORIES(${PROJECT_SOURCE_DIR}/lib/${platform}/lib/utopia)
	################# end for MS6308  ####################
else()
	MESSAGE("LINUX BUILD")

	SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g -O2 -Wall")
	SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -O2 -Wall")
	EXECUTE_PROCESS(COMMAND getconf LONG_BIT OUTPUT_VARIABLE bit)
	if(${bit} STREQUAL "32\n" OR ${bit} STREQUAL "32")
		SET(bit "32")
	else()
		SET(bit "64")
	endif()
	MESSAGE(${bit})
	LINK_DIRECTORIES(${PROJECT_SOURCE_DIR}/mdroid/lib/${platform}/${bit})    
endif()

add_definitions("-DSERVICE_BUILD=0")
SET(SERVICE_BUILD 0)

#ADD_SUBDIRECTORY(tvos_interface)
#ADD_SUBDIRECTORY(binder_interface)
#ADD_SUBDIRECTORY(binder_client)
ADD_SUBDIRECTORY(service)
#ADD_SUBDIRECTORY(src)






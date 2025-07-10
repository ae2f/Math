cmake_minimum_required(VERSION 3.20)

enable_testing()
include(cmake/Core.cmake)

project(Math VERSION 0.0.0 LANGUAGES C CXX)

if(NOT TARGET ae2f::${PROJECT_NAME})
	ae2f_CoreLibFetch(ae2f Core main)
	ae2f_CoreLibFetch(ae2f Macro main)
	
	ae2f_Macro_init(0, 60, 100)

	file(GLOB tars ${PROJECT_SOURCE_DIR}/ainc/*)
	foreach(tar ${tars})
		message("got ${tar}")
		get_filename_component(tar_name "${tar}" NAME_WE)
		message("got ${tar_name}")
		ae2f_Macro_one(${tar} ${PROJECT_SOURCE_DIR}/include/ae2f/Math/${tar_name}.auto.h)
	endforeach()

	ae2f_CoreLibTent(
		${PROJECT_NAME}
		INTERFACE 
		include 
		ae2f

		include/ae2f/Math/Util.auto.h
		include/ae2f/Math/Mem.h
		include/ae2f/Math/int.h
		include/ae2f/Math/int.auto.h
		include/ae2f/Math/float.h
		include/ae2f/Math/float.auto.h
	)

	target_link_libraries(ae2f-${PROJECT_NAME} INTERFACE ae2f::Core)
	target_link_libraries(ae2f-${PROJECT_NAME} INTERFACE ae2f::Macro)
	ae2f_CoreTestTent(ae2f-${PROJECT_NAME} ${PROJECT_SOURCE_DIR}/test/src)
	ae2f_Macro_autoname(${PROJECT_SOURCE_DIR}/test/__float.h)
endif()

# This is a fake library for debugging
if(NOT TARGET ae2f::${PROJECT_NAME}::devel AND ae2f_DEVEL)
	file(GLOB src ${PROJECT_SOURCE_DIR}/ainc/*)
	add_library(ae2f-${PROJECT_NAME}-devel ${src})
	add_library(ae2f::${PROJECT_NAME}::devel ALIAS ae2f-${PROJECT_NAME}-devel)
	target_link_libraries(ae2f-${PROJECT_NAME}-devel PUBLIC ae2f::${PROJECT_NAME})
endif()

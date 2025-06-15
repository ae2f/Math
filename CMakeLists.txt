cmake_minimum_required(VERSION 3.20)

enable_testing()
include(cmake/Core.cmake)

project(Math VERSION 0.0.0 LANGUAGES C CXX)



if(NOT TARGET ${PROJECT_NAME})
	ae2f_CoreLibFetch(ae2f Core main)
	ae2f_CoreLibFetch(ae2f Macro main)

	ae2f_Macro_init(0, 60, 100)

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

	target_link_libraries(${PROJECT_NAME} INTERFACE ${ae2f__Core__FETCHED})
	target_link_libraries(${PROJECT_NAME} INTERFACE ${ae2f__Macro__FETCHED})
	ae2f_CoreTestTent(${PROJECT_NAME} ${PROJECT_SOURCE_DIR}/test)

	ae2f_Macro_autoname(${PROJECT_SOURCE_DIR}/include/ae2f/Math/Util.h)
	ae2f_Macro_autoname(${PROJECT_SOURCE_DIR}/include/ae2f/Math/int.imp.h)
	ae2f_Macro_autoname(${PROJECT_SOURCE_DIR}/include/ae2f/Math/float.imp.h)
endif()

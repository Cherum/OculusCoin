cmake_minimum_required(VERSION 2.8)

project(OculusCoinVeelo)

set(CMAKE_AUTOMOC ON)

SET(CMAKE_PREFIX_PATH C:/Qt/5.2.1/5.2.1/msvc2010_opengl)	
find_package(Qt5 REQUIRED Core Gui OpenGL)


if(WIN32)
set(COIN3D_LIBRARIES optimized ${CMAKE_SOURCE_DIR}/Coin_3.1.3_vs10/lib/coin3.lib
                     debug     ${CMAKE_SOURCE_DIR}/Coin_3.1.3_vs10/lib/coin3d.lib)
else(WIN32)
set(COIN3D_LIBRARIES Coin)
endif(WIN32)

SET(INVENTOR_DEFS -DCOIN_DLL -DQUARTER_NOT_DLL)

INCLUDE_DIRECTORIES(
	${CMAKE_CURRENT_BINARY_DIR}

	${CMAKE_SOURCE_DIR}/Coin_3.1.3_vs10/include

	${CMAKE_SOURCE_DIR}/OculusSDK_0.3.1/LibOVR/Include
	${CMAKE_SOURCE_DIR}/OculusSDK_0.3.1/3rdParty/glext
)
		
ADD_DEFINITIONS(
	${INVENTOR_DEFS}
)
	
SET(PROJECT_HEADERS
	src/CoinRiftWidget.h
)
SET(PROJECT_SOURCES
	src/CoinRiftWidget.cpp
)

ADD_EXECUTABLE(OculusCoinVeelo src/main.cpp ${PROJECT_HEADERS} ${PROJECT_SOURCES})
TARGET_LINK_LIBRARIES(OculusCoinVeelo  
	Qt5::Core
	Qt5::Gui
	Qt5::OpenGL
	
	${COIN3D_LIBRARIES}
	
	opengl32 
	${CMAKE_SOURCE_DIR}/build/OculusSDK_0.3.1/LibOVR/Debug/OculusVR.lib

	Winmm.lib
	Shell32.lib
	Setupapi.lib
)
set(CMAKE_MODULE_PATH
	${CMAKE_SOURCE_DIR}/OculusSDK_0.3.1/CMake/Modules
)
add_subdirectory(
	${CMAKE_SOURCE_DIR}/OculusSDK_0.3.1
)
cmake_minimum_required(VERSION 2.8)

project(OculusCoinVeelo)

set(CMAKE_AUTOMOC ON)

#SET(CMAKE_PREFIX_PATH C:/Qt/5.1.1/msvc2010_opengl)	
SET(CMAKE_PREFIX_PATH C:/Qt/5.2.1/5.2.1/msvc2010_opengl)	
find_package(Qt5 REQUIRED Core Gui OpenGL)
#find_package(OpenGL)

# find_package(Coin3D)
if(WIN32)
set(INVENTOR_INCLUDES ${CMAKE_SOURCE_DIR}/Coin_3.1.3_vs10/include)
set(COIN3D_LIBRARIES optimized ${CMAKE_SOURCE_DIR}/Coin_3.1.3_vs10/lib/coin3.lib
                     debug     ${CMAKE_SOURCE_DIR}/Coin_3.1.3_vs10/lib/coin3d.lib)
else(WIN32)
set(COIN3D_LIBRARIES Coin)
endif(WIN32)

SET(INVENTOR_DEFS -DCOIN_DLL -DQUARTER_NOT_DLL)

INCLUDE_DIRECTORIES(
	${INVENTOR_INCLUDES}

	${CMAKE_CURRENT_BINARY_DIR}

	${CMAKE_SOURCE_DIR}/OculusSDK_0.3.1/LibOVR/Include
	${CMAKE_SOURCE_DIR}/OculusSDK_0.3.2/3rdParty/glext
)
		
ADD_DEFINITIONS(
	${INVENTOR_DEFS}
)

LINK_DIRECTORIES(
	${CMAKE_SOURCE_DIR}/OculusSDK_0.3.1/LibOVR/Lib/Win32/VS2010
)
	
ADD_EXECUTABLE(OculusCoinVeelo src/main.cpp)
TARGET_LINK_LIBRARIES(OculusCoinVeelo  
	Qt5::Core
	Qt5::Gui
	Qt5::OpenGL
	
	${COIN3D_LIBRARIES}
	
	opengl32 
	${CMAKE_SOURCE_DIR}/OculusSDK_0.3.1/LibOVR/Lib/Win32/VS2010/libovrd.lib
	###
	Winmm.lib
	Shell32.lib
	Setupapi.lib
)
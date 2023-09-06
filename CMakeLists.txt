cmake_minimum_required( VERSION 3.1 )

project(ManulEngine)

find_package( OpenGL REQUIRED )

include_directories( ${OPENGL_INCLUDE_DIRS} )

set( GLFW_BUILD_DOCS OFF CACHE BOOL  "GLFW lib only" )
set( GLFW_INSTALL OFF CACHE BOOL  "GLFW lib only" )

add_subdirectory( glfw )

if( MSVC )
    SET( CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /ENTRY:mainCRTStartup" )
endif()

#VULKAN

message(STATUS "Attempting to locate Vulkan SDK using manual path......")
	set(VULKAN_SDK "D:/VulkanSDK")
	set(VULKAN_PATH "${VULKAN_SDK}")
	message(STATUS "Using manual specified path: ${VULKAN_PATH}")

	# Check if manual set path exists
	if(NOT EXISTS "${VULKAN_PATH}")
		message("Error: Unable to locate this Vulkan SDK path VULKAN_PATH: ${VULKAN_PATH}, please specify correct path.
		For more information on correct installation process, please refer to subsection 'Getting started with Lunar-G SDK'
		and 'Setting up first project with CMake' in Chapter 3, 'Shaking hands with the device' in this book 'Learning Vulkan', ISBN - 9781786469809.")
	   return()
	endif()
#---------------------------
set(VULKAN_LIB_LIST "vulkan-1")

if(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
	# Include Vulkan header files from Vulkan SDK
	include_directories(AFTER ${VULKAN_PATH}/Include)

	# Link directory for vulkan-1
	link_directories(${VULKAN_PATH}/Bin;${VULKAN_PATH}/Lib;)
endif()

add_executable(ManulEngine WIN32 "ManulEngine/src/main.cpp" "ManulEngine/src/Window.cpp" "ManulEngine/src/Window.h" "ManulEngine/src/Renderer.cpp" "ManulEngine/src/Renderer.h" "ManulEngine/src/Logger.cpp" "ManulEngine/src/Logger.h" "ManulEngine/src/VK_Renderer/VulkanDebug.cpp" "ManulEngine/src/VK_Renderer/VulkanDebug.h" "ManulEngine/src/VK_Renderer/VulkanDevice.h" "ManulEngine/src/VK_Renderer/VulkanDevice.cpp" "ManulEngine/src/VK_Renderer/VulkanBackend.cpp" "ManulEngine/src/VK_Renderer/VulkanBackend.h")
set_target_properties(ManulEngine PROPERTIES LINKER_LANGUAGE CXX)
target_compile_features(ManulEngine PRIVATE cxx_std_17)
target_link_libraries(ManulEngine ${VULKAN_LIB_LIST} )
target_link_libraries(ManulEngine ${OPENGL_LIBRARIES} glfw )

if( MSVC )
    if(${CMAKE_VERSION} VERSION_LESS "3.6.0") 
        message( "\n\t[ WARNING ]\n\n\tCMake version lower than 3.6.\n\n\t - Please update CMake and rerun; OR\n\t - Manually set 'GLFW-CMake-starter' as StartUp Project in Visual Studio.\n" )
    else()
        set_property( DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ManulEngine)
    endif()
endif()

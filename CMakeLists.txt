cmake_minimum_required( VERSION 3.1 )

project(ManulEngine)

find_package( OpenGL REQUIRED )

include_directories( ${OPENGL_INCLUDE_DIRS} )

set( GLFW_BUILD_DOCS OFF CACHE BOOL  "GLFW lib only" )
set( GLFW_INSTALL OFF CACHE BOOL  "GLFW lib only" )


add_subdirectory( glfw )
#add_subdirectory( external/zlib-1.3 )

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

add_executable(ManulEngine WIN32 "ManulEngine/src/main.cpp"
		"ManulEngine/src/ManulEngine/Core/Window.cpp"
		"ManulEngine/src/ManulEngine/Core/Window.h"
		"ManulEngine/src/ManulEngine/Renderer/Renderer.cpp"
		"ManulEngine/src/ManulEngine/Renderer/Renderer.h"
		"ManulEngine/src/ManulEngine/Core/Logger.cpp"
		"ManulEngine/src/ManulEngine/Core/Logger.h"
		"ManulEngine/src/Platform/Vulkan/VulkanDebug.cpp"
		"ManulEngine/src/Platform/Vulkan/VulkanDebug.h"
		"ManulEngine/src/Platform/Vulkan/VulkanDevice.h"
		"ManulEngine/src/Platform/Vulkan/VulkanDevice.cpp"
		"ManulEngine/src/Platform/Vulkan/VulkanBackend.cpp"
		"ManulEngine/src/Platform/Vulkan/VulkanBackend.h"
		"ManulEngine/src/ManulEngine.h"
		"ManulEngine/src/Platform/Windows/WindowsWindow.cpp"
		"ManulEngine/src/Platform/Windows/WindowsWindow.h"
		"ManulEngine/src/ManulEngine/Math/Math.cpp"
		"ManulEngine/src/ManulEngine/Math/Math.h"
		"ManulEngine/src/ManulEngine/Physics/2D/Physics2D.cpp"
		"ManulEngine/src/ManulEngine/Physics/2D/Physics2D.h"
		"ManulEngine/src/ManulEngine/Core/Application.cpp"
		"ManulEngine/src/ManulEngine/Core/Application.h"
		ManulEngine/src/ManulEngine/Core/FileSystem.cpp
		ManulEngine/src/ManulEngine/Core/FileSystem.h
		ManulEngine/src/Platform/Vulkan/VulkanSurface.cpp
		ManulEngine/src/Platform/Vulkan/VulkanSurface.h
		ManulEngine/src/Platform/Vulkan/VulkanPipline.cpp
		ManulEngine/src/Platform/Vulkan/VulkanPipline.h
        ManulEngine/src/Platform/OpenGL/OpenGLBackend.cpp
        ManulEngine/src/Platform/OpenGL/OpenGLBackend.h
		ManulEngine/src/ManulEngine/ResourceManager/ResourcePacker.cpp
		ManulEngine/src/ManulEngine/ResourceManager/ResourcePacker.h
		ManulEngine/src/ManulEngine/ResourceManager/ResourceManager.cpp
		ManulEngine/src/ManulEngine/ResourceManager/ResourceManager.h
		ManulEngine/src/ManulEngine/ResourceManager/ResourceLoader.cpp
		ManulEngine/src/ManulEngine/ResourceManager/ResourceLoader.h
		ManulEngine/src/ManulEngine/ResourceManager/ResourcePacker.cpp
		ManulEngine/src/ManulEngine/ResourceManager/ResourcePacker.h
		ManulEngine/src/ManulEngine/ResourceManager/Resource.h
)

link_directories(ManulEngine external/zlib-1.3/MinSizeRel)
include_directories("ManulEngine/src/ManulEngine")
include_directories("ManulEngine/src")

add_library(gladLib STATIC
		external/glad/src/glad.c

)
include_directories("external/glad/include")
include_directories("external/zlib-1.3")

set_target_properties(ManulEngine PROPERTIES LINKER_LANGUAGE CXX)
target_compile_features(ManulEngine PRIVATE cxx_std_17)

target_link_libraries(ManulEngine ${VULKAN_LIB_LIST} )


target_link_libraries(ManulEngine ${OPENGL_LIBRARIES} glfw gladLib zlib)

target_precompile_headers(ManulEngine PRIVATE ManulEngine/src/mapch.h)
if( MSVC )
    if(${CMAKE_VERSION} VERSION_LESS "3.6.0") 
        message( "\n\t[ WARNING ]\n\n\tCMake version lower than 3.6.\n\n\t - Please update CMake and rerun; OR\n\t - Manually set 'GLFW-CMake-starter' as StartUp Project in Visual Studio.\n" )
    else()
        set_property( DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ManulEngine)
    endif()
endif()

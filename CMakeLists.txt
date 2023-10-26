cmake_minimum_required( VERSION 3.1)

project(ManulEngine)

if( MSVC )
    SET( CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /ENTRY:mainCRTStartup" )
endif()

find_package(Vulkan)

if(NOT Vulkan_FOUND)
	message(SEND_ERROR "Vulkan NOT found")
endif()
if (NOT ${Vulkan_INCLUDE_DIRS} STREQUAL "")
	set(VULKAN_PATH ${Vulkan_INCLUDE_DIRS})	
	STRING(REGEX REPLACE "/Include" "" VULKAN_PATH ${VULKAN_PATH})
	message(STATUS "Vulkan path is: " ${VULKAN_PATH})

	include_directories(AFTER ${VULKAN_PATH}/Include)
	link_directories(${VULKAN_PATH}/Bin;${VULKAN_PATH}/Lib;)
endif()

if(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
	link_directories(external/zlib-1.3/MinSizeRel)
	link_directories(external/glfw/bin/src/MinSizeRel)
endif()

add_library(glad STATIC external/glad/src/glad.c)

include_directories("ManulEngine/src"
					"external/spdlog/include"
					"external/glad/include"
					"external/zlib-1.3"
					"external/glfw/include"
					"external/stb-image"
					"external/glm"
)

add_executable(ManulEngine WIN32
		ManulEngine/src/main.cpp
		ManulEngine/src/ManulEngine/Core/Window.cpp
		ManulEngine/src/ManulEngine/Core/Window.h
		ManulEngine/src/ManulEngine/Renderer/Renderer.cpp
		ManulEngine/src/ManulEngine/Renderer/Renderer.h
		"ManulEngine/src/ManulEngine/Core/Log.cpp"
		"ManulEngine/src/ManulEngine/Core/Log.h"
		ManulEngine/src/Platform/Vulkan/VulkanDebug.cpp
		ManulEngine/src/Platform/Vulkan/VulkanDebug.h
		ManulEngine/src/Platform/Vulkan/VulkanDevice.h
		ManulEngine/src/Platform/Vulkan/VulkanDevice.cpp
		ManulEngine/src/Platform/Vulkan/VulkanBackend.cpp
		ManulEngine/src/Platform/Vulkan/VulkanBackend.h
		ManulEngine/src/ManulEngine.h
		ManulEngine/src/Platform/Windows/WindowsWindow.cpp
		ManulEngine/src/Platform/Windows/WindowsWindow.h
		ManulEngine/src/ManulEngine/Core/Math/Math.cpp
		ManulEngine/src/ManulEngine/Core/Math/Math.h
		ManulEngine/src/ManulEngine/Physics/2D/Physics2D.cpp
		ManulEngine/src/ManulEngine/Physics/2D/Physics2D.h
		ManulEngine/src/ManulEngine/Core/Application.cpp
		ManulEngine/src/ManulEngine/Core/Application.h
		ManulEngine/src/Platform/Vulkan/VulkanSurface.cpp
		ManulEngine/src/Platform/Vulkan/VulkanSurface.h
		ManulEngine/src/Platform/Vulkan/VulkanPipline.cpp
		ManulEngine/src/Platform/Vulkan/VulkanPipline.h
		ManulEngine/src/Platform/OpenGL/OpenGLBackend.cpp
		ManulEngine/src/Platform/OpenGL/OpenGLBackend.h
		#ManulEngine/src/ManulEngine/ResourceManager/ResourcePacker.cpp
		#ManulEngine/src/ManulEngine/ResourceManager/ResourcePacker.h
		ManulEngine/src/ManulEngine/ResourceManager/ResourceManager.cpp
		ManulEngine/src/ManulEngine/ResourceManager/ResourceManager.h
		ManulEngine/src/ManulEngine/ResourceManager/ResourceLoader.cpp
		ManulEngine/src/ManulEngine/ResourceManager/ResourceLoader.h
		ManulEngine/src/ManulEngine/ResourceManager/Resource.h
		ManulEngine/src/ManulEngine/Renderer/Renderer2D.cpp
		ManulEngine/src/ManulEngine/Renderer/Renderer2D.h
		ManulEngine/src/ManulEngine/Renderer/Camera.h
		ManulEngine/src/ManulEngine/Renderer/OrthographicCamera.cpp
		ManulEngine/src/ManulEngine/Renderer/OrthographicCamera.h
		ManulEngine/src/ManulEngine/Renderer/RendererBackend.cpp
		ManulEngine/src/ManulEngine/Renderer/RendererBackend.h
		ManulEngine/src/ManulEngine/Audio/AudioEngine.cpp
		ManulEngine/src/ManulEngine/Audio/AudioEngine.h
		"ManulEngine/src/Platform/OpenGL/OpenGLShader.h"
		"ManulEngine/src/Platform/OpenGL/OpenGLShader.cpp"
		"ManulEngine/src/Platform/OpenGL/OpenGLPrimitives.cpp" 
		"ManulEngine/src/Platform/OpenGL/OpenGLPrimitives.h" )

target_precompile_headers(ManulEngine PRIVATE ManulEngine/src/mapch.h)
#target_link_libraries(ManulEngine glfw3 glad zlib vulkan-1)
target_link_libraries(ManulEngine glfw3 glad vulkan-1)

set_target_properties(ManulEngine PROPERTIES LINKER_LANGUAGE CXX)
target_compile_features(ManulEngine PRIVATE cxx_std_17)

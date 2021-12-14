-- OpenGL-Sandbox
workspace "Golf-Sim"
	architecture "x64"
	startproject "Golf-Sim"

	configurations
	{
		"Debug",
		"Release"
	}
	
	flags
	{
		"MultiProcessorCompile"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Include directories relative to OpenGL-Core
IncludeDir = {}
IncludeDir["GLFW"] = "vendor/GLFW/include"
IncludeDir["Glad"] = "vendor/Glad/include"
IncludeDir["ImGui"] = "vendor/imgui"
IncludeDir["glm"] = "vendor/glm"
IncludeDir["stb_image"] = "vendor/stb_image"

-- Projects
group "Dependencies"
	include "OpenGL-Core/vendor/GLFW"
	include "OpenGL-Core/vendor/Glad"
	include "OpenGL-Core/vendor/imgui"
group ""

include "OpenGL-Core"
include "Golf-Sim"

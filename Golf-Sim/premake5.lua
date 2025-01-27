project "Golf-Sim"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("../bin/" .. outputdir .. "/%{prj.name}")
	objdir ("../bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"src/**.h",
		"src/**.cpp",
		"vendor/implot/**.cpp"
	}

	defines
	{
		"_CRT_SECURE_NO_WARNINGS"
	}

	includedirs
	{
		"../OpenGL-Core/vendor/spdlog/include",
		"../OpenGL-Core/src",
		"../OpenGL-Core/vendor",
		"../OpenGL-Core/%{IncludeDir.glm}",
		"../OpenGL-Core/%{IncludeDir.Glad}",
		"../OpenGL-Core/%{IncludeDir.ImGui}",
		"../OpenGL-Core/%{IncludeDir.GLFW}",
		"./src",
		"./vendor/reactphysics3d/include"
	}

	links
	{
		"OpenGL-Core",
		"reactphysics3d.lib"
	}

	filter "system:windows"
		systemversion "latest"

		defines
		{
			"GLCORE_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "GLCORE_DEBUG"
		runtime "Debug"
		symbols "on"

		libdirs 
		{
			"./vendor/reactphysics3d/debug"
		}


	filter "configurations:Release"
		defines "GLCORE_RELEASE"
		runtime "Release"
        optimize "on"

		libdirs 
		{
			"./vendor/reactphysics3d/release"
		}

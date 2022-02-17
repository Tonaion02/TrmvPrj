workspace "SDL_TEST_PREMAKE"
	architecture "x64"

    configurations { "Debug", "Release" }
	
    --platforms { "Windows" }

	filter "system:Windows"
		systemversion "10.0.17763.0"

	--location "build"

project "SDL_TEST_PREMAKE"
    kind "ConsoleApp"
    language "C++"

	includedirs 
	{ 
		"C:/SDL_Lib/SDL2/include",			--basic for SDL
		"C:/SDL_Lib/SDL2_image/include" ,	--basic for SDL
		"C:/SDL_Lib/SDL2_ttf/include",		--basic for SDL
		"$(ProjectDir)/src"					--Personal includes
	}
    
	libdirs --directory to link SDL library
	{ 		
		"C:/SDL_Lib/SDL2/lib/x64",	
		"C:/SDL_Lib/SDL2_image/lib/x64", 
		"C:/SDL_Lib/SDL2_ttf/lib/x64" 
	}

	links --SDL library to link
	{ 
		"SDL2.lib",
		"SDL2main.lib",
		"SDL2_image.lib",
		"SDL2_ttf.lib"
	}

	files { "src/**.h", "src/**.cpp" }
	removefiles { "src/ToDo.h" }

	objdir "output/obj"

    filter { "configurations:Debug" }
        defines { "DEBUG" }
        symbols "On"
		targetdir "output/bin/debug"

    filter { "configurations:Release" }
        defines { "NDEBUG" }
        optimize "On"
		targetdir "output/bin/release"
	
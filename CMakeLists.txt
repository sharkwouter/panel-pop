########################################
# General setup
#

cmake_minimum_required(VERSION 3.5.0)

project(panel-pop)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")

set(SRCS
        Main.cpp
        Game/GameEventHandler.cpp
        Game/Block.cpp
        Game/BoardController.cpp
        Game/Game.cpp
        Game/GarbageBlock.cpp
        Game/KeyboardController.cpp
        Game/Board.cpp
        Game/VsGame.cpp
        Game/EndlessGame.cpp
        Game/BoardEventHandler.cpp
        Config/ConfigHandler.cpp
        SDLContext.cpp
        Rendering/Popup.cpp
        Rendering/EndlessGameRenderer.cpp
        Rendering/ChainPopup.cpp
        Rendering/GameRenderer.cpp
        Rendering/TitleScreenRenderer.cpp
        Rendering/BoardRenderer.cpp
        Rendering/Particle.cpp
        Rendering/ComboPopup.cpp
        Rendering/GbQueueRenderer.cpp
        Rendering/VsGameRenderer.cpp
        Rendering/Renderer.cpp
        States/TitleScreen.cpp
        States/OptionsMenuState.cpp
        States/DemoGameState.cpp
        States/StateManager.cpp
        States/VsGameState.cpp
        States/AIGameState.cpp
        States/State.cpp
        States/EndlessGameState.cpp
        States/GameState.cpp
        States/FadeTransition.cpp
        AI/BoardScanner.cpp
        AI/AIBoardController.cpp
        InputManager.cpp
        Menus/KeyConfigMenu.cpp
        Menus/OptionsMenu.cpp
        Menus/MainMenu.cpp
        Menus/PauseMenu.cpp
        Menus/MenuItem.cpp
        Menus/Menu.cpp
        scale.h
        InputState.cpp InputState.h InputEvents/InputEvent.cpp InputEvents/InputEvent.h InputEvents/KeyboardKey.cpp InputEvents/KeyboardKey.h Config/InputConfig.cpp Config/InputConfig.h InputEvents/JoyButton.cpp InputEvents/JoyButton.h InputEvents/JoyHat.cpp InputEvents/JoyHat.h InputEvents/JoyAxisDirection.cpp InputEvents/JoyAxisDirection.h)

add_executable(panel-pop ${SRCS})

if (VITA)
	# DOLCESDK defines
	if(NOT DEFINED CMAKE_TOOLCHAIN_FILE)
		if(DEFINED ENV{DOLCESDK})
			set(CMAKE_TOOLCHAIN_FILE "$ENV{DOLCESDK}/share/dolce.toolchain.cmake" CACHE PATH "toolchain file")
		    else()
			message(FATAL_ERROR "Please define DOLCESDK to point to your SDK path!")
		    endif()
	endif()

	include("$ENV{DOLCESDK}/share/dolce.cmake" REQUIRED)

	# Project start
	set(VITA_APPNAME PanelPop)
	set(VITA_TITLEID "PPOP00001")
	set(VITA_VERSION "00.03")

	# Optional. You can specify more param.sfo flags this way.
	set(VITA_MKSFOEX_FLAGS "${VITA_MKSFOEX_FLAGS} -d PARENTAL_LEVEL=1")

	set(VITA_INCLUDE_DIR "$ENV{DOLCESDK}/arm-dolce-eabi/include/")
	set(SDL2_INCLUDE_DIR "$ENV{DOLCESDK}/arm-dolce-eabi/include/SDL2")
	set(JSON_INCLUDE_DIR "$ENV{DOLCESDK}/arm-dolce-eabi/include/jsoncpp")
	set(PNG_INCLUDE_DIR "$ENV{DOLCESDK}/arm-dolce-eabi/include/libpng16")
	set(FLAC_INCLUDE_DIR "$ENV{DOLCESDK}/arm-dolce-eabi/include/FLAC")

	include_directories(${INCLUDE_DIRECTORIES}
		    ${VITA_INCLUDE_DIR}
		    ${SDL2_INCLUDE_DIR}
		    ${JSON_INCLUDE_DIR}
		    ${PNG_INCLUDE_DIR}
		    ${FLAC_INCLUDE_DIR}
	)

	target_link_libraries(panel-pop
		SDL2_image
		SDL2_ttf
		SDL2_mixer
		SDL2
		jsoncpp
		stdc++
		pthread
		png16
		freetype
		vorbisfile
		vorbis
		ogg
		jpeg
		z
		m
		mikmod
		mpg123
		FLAC
		pib
		SceAppUtil_stub
		SceAudio_stub
		SceCommonDialog_stub
		SceCtrl_stub
		SceDisplay_stub
		SceDisplayUser_stub
		SceGxm_stub
		SceHid_stub
		SceSysmodule_stub
		SceTouch_stub
		SceMotion_stub
	)
	dolce_create_self(panel-pop.self panel-pop)

	dolce_create_vpk(panel-pop.vpk ${VITA_TITLEID} panel-pop.self
		    VERSION ${VITA_VERSION}
		    NAME ${VITA_APPNAME}
		    FILE platform/vita/sce_sys sce_sys
		    FILE platform/vita/panelpop.json panelpop.json
		    FILE assets/fonts assets/fonts
		    FILE assets/music assets/music
		    FILE assets/sfx assets/sfx
		    FILE assets/images/ assets/images/
	)
ELSEIF(PLATFORM_PSP)
	include_directories(
		${PSPDEV}/psp/include/SDL2
		${PSPDEV}/psp/include/jsoncpp
		${PSPDEV}/psp/include/libpng15
	)

	target_link_libraries(panel-pop PRIVATE
		SDL2_image
		SDL2_mixer
		SDL2
		SDL2_ttf
		SDL2main
		png
		jpeg
		pspvram
		GL
		pspvram
		pspvfpu
		pspgu
		pspctrl
		pspdebug
		pspdisplay
		pspge
		pspaudio
		psphprm
		jsoncpp
		vorbisfile
		vorbis
		ogg
		freetype
		z
	)

	create_pbp_file(
		TARGET panel-pop
		ICON_PATH NULL
		BACKGROUND_PATH NULL
		PREVIEW_PATH NULL
		TITLE panel-pop
		BUILD_PRX
	)

	file(COPY platform/psp/panelpop.json DESTINATION ${CMAKE_BINARY_DIR})
	file(COPY assets/fonts DESTINATION ${CMAKE_BINARY_DIR}/assets)
	file(COPY assets/music DESTINATION ${CMAKE_BINARY_DIR}/assets)
	file(COPY assets/sfx DESTINATION ${CMAKE_BINARY_DIR}/assets)
	file(COPY platform/psp/assets/images DESTINATION ${CMAKE_BINARY_DIR}/assets)
	file(COPY assets/images/popups.png DESTINATION ${CMAKE_BINARY_DIR}/assets/images)
	file(COPY assets/images/particle.png DESTINATION ${CMAKE_BINARY_DIR}/assets/images)
	file(COPY assets/images/garbagequeue.png DESTINATION ${CMAKE_BINARY_DIR}/assets/images)
ELSE()
	set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/CMake")

	find_package(SDL2 REQUIRED)
	find_package(SDL2_image REQUIRED)
	find_package(SDL2_ttf REQUIRED)
	find_package(SDL2_mixer REQUIRED)

	find_package(SDL2 REQUIRED)
	find_package(SDL2_image REQUIRED)
	find_package(SDL2_ttf REQUIRED)
	find_package(SDL2_mixer REQUIRED)
	find_package(jsoncpp REQUIRED)
	get_target_property(JSON_INC_PATH jsoncpp_lib INTERFACE_INCLUDE_DIRECTORIES)

	include_directories(${SDL2_INCLUDE_DIR}
		${SDL2_IMAGE_INCLUDE_DIR}
		${SDL2_TTF_INCLUDE_DIR}
		${SDL2_MIXER_INCLUDE_DIR}
		${JSON_INC_PATH}
	)

	target_link_libraries(panel-pop ${SDL2_LIBRARY}
		${SDL2_IMAGE_LIBRARIES}
		${SDL2_TTF_LIBRARIES}
		${SDL2_MIXER_LIBRARIES}
		jsoncpp
	)

	file(COPY panelpop.json DESTINATION ${CMAKE_BINARY_DIR})
	file(COPY assets/fonts DESTINATION ${CMAKE_BINARY_DIR}/assets)
	file(COPY assets/music DESTINATION ${CMAKE_BINARY_DIR}/assets)
	file(COPY assets/sfx DESTINATION ${CMAKE_BINARY_DIR}/assets)
	file(COPY assets/images DESTINATION ${CMAKE_BINARY_DIR}/assets)
ENDIF()

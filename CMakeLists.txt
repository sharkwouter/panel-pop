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

include(FindPkgConfig)
pkg_search_module(SDL2 REQUIRED sdl2)
pkg_search_module(SDL2_IMAGE REQUIRED SDL2_image)
pkg_search_module(SDL2_MIXER REQUIRED SDL2_mixer)
pkg_search_module(SDL2_TTF REQUIRED SDL2_ttf)
pkg_search_module(JSONCPP REQUIRED jsoncpp)

target_link_libraries(panel-pop PRIVATE
		${SDL2_LIBRARIES}
		${SDL2_IMAGE_LIBRARIES}
		${SDL2_MIXER_LIBRARIES}
		${SDL2_TTF_LIBRARIES}
		${JSONCPP_LIBRARIES}
)
include_directories(
		${SDL2_IMAGE_INCLUDE_DIRS}
		${SDL2_MIXER_INCLUDE_DIRS}
		${SDL2_TTF_INCLUDE_DIRS}
		${JSONCPP_INCLUDE_DIRS}
)

if (VITA)
	# VITASDK defines
	if(NOT DEFINED CMAKE_TOOLCHAIN_FILE)
		if(DEFINED ENV{VITASDK})
			set(CMAKE_TOOLCHAIN_FILE "$ENV{VITASDK}/share/vita.toolchain.cmake" CACHE PATH "toolchain file")
		    else()
			message(FATAL_ERROR "Please define VITASDK to point to your SDK path!")
		    endif()
	endif()

	include("$ENV{VITASDK}/share/vita.cmake" REQUIRED)

	# Project start
	set(VITA_APPNAME PanelPop)
	set(VITA_TITLEID "PPOP00001")
	set(VITA_VERSION "00.03")

	# Optional. You can specify more param.sfo flags this way.
	set(VITA_MKSFOEX_FLAGS "${VITA_MKSFOEX_FLAGS} -d PARENTAL_LEVEL=1")

	vita_create_self(panel-pop.self panel-pop)

	vita_create_vpk(panel-pop.vpk ${VITA_TITLEID} panel-pop.self
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
	create_pbp_file(
		TARGET panel-pop
		ICON_PATH ${CMAKE_SOURCE_DIR}/platform/psp/icon.png
		BACKGROUND_PATH NULL
		PREVIEW_PATH NULL
		TITLE Panel-Pop
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
	file(COPY panelpop.json DESTINATION ${CMAKE_BINARY_DIR})
	file(COPY assets/fonts DESTINATION ${CMAKE_BINARY_DIR}/assets)
	file(COPY assets/music DESTINATION ${CMAKE_BINARY_DIR}/assets)
	file(COPY assets/sfx DESTINATION ${CMAKE_BINARY_DIR}/assets)
	file(COPY assets/images DESTINATION ${CMAKE_BINARY_DIR}/assets)
ENDIF()

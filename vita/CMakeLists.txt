cmake_minimum_required(VERSION 3.5.0)

# VitaSDK defines
if(NOT DEFINED CMAKE_TOOLCHAIN_FILE)
  if(DEFINED ENV{VITASDK})
    set(CMAKE_TOOLCHAIN_FILE "$ENV{VITASDK}/share/vita.toolchain.cmake" CACHE PATH "toolchain file")
  else()
    message(FATAL_ERROR "Please define VITASDK to point to your SDK path!")
  endif()
endif()

project(panel-pop)

include("$ENV{VITASDK}/share/vita.cmake" REQUIRED)

# Project start
set(VITA_APPNAME panel-pop)
set(VITA_TITLEID "PPOP00001")
set(VITA_VERSION "01.00")

## Flags and includes for building
# Note that we make sure not to overwrite previous flags
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=gnu11")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

# Optional. You can specify more param.sfo flags this way.
set(VITA_MKSFOEX_FLAGS "${VITA_MKSFOEX_FLAGS} -d PARENTAL_LEVEL=1")

set(SRCS
        ../Main.cpp
        ../Game/GameEventHandler.cpp
        ../Game/Block.cpp
        ../Game/BoardController.cpp
        ../Game/Game.cpp
        ../Game/GarbageBlock.cpp
        ../Game/KeyboardController.cpp
        ../Game/Board.cpp
        ../Game/VsGame.cpp
        ../Game/EndlessGame.cpp
        ../Game/BoardEventHandler.cpp
        ../SDLContext.cpp
        ../Rendering/Popup.cpp
        ../Rendering/EndlessGameRenderer.cpp
        ../Rendering/ChainPopup.cpp
        ../Rendering/GameRenderer.cpp
        ../Rendering/TitleScreenRenderer.cpp
        ../Rendering/BoardRenderer.cpp
        ../Rendering/Particle.cpp
        ../Rendering/ComboPopup.cpp
        ../Rendering/GbQueueRenderer.cpp
        ../Rendering/VsGameRenderer.cpp
        ../Rendering/Renderer.cpp
        ../States/TitleScreen.cpp
        ../States/OptionsMenuState.cpp
        ../States/DemoGameState.cpp
        ../States/StateManager.cpp
        ../States/VsGameState.cpp
        ../States/AIGameState.cpp
        ../States/State.cpp
        ../States/EndlessGameState.cpp
        ../States/GameState.cpp
        ../States/FadeTransition.cpp
        ../AI/BoardScanner.cpp
        ../AI/AIBoardController.cpp
        ../InputManager.cpp
        ../Menus/KeyConfigMenu.cpp
        ../Menus/OptionsMenu.cpp
        ../Menus/MainMenu.cpp
        ../Menus/PauseMenu.cpp
        ../Menus/MenuItem.cpp
        ../Menus/Menu.cpp
        ../InputState.cpp ../InputState.h ../InputEvents/InputEvent.cpp ../InputEvents/InputEvent.h ../InputEvents/KeyboardKey.cpp ../InputEvents/KeyboardKey.h ../Config/InputConfig.cpp ../Config/InputConfig.h ../InputEvents/JoyButton.cpp ../InputEvents/JoyButton.h ../InputEvents/JoyHat.cpp ../InputEvents/JoyHat.h ../InputEvents/JoyAxisDirection.cpp ../InputEvents/JoyAxisDirection.h)

# Vita specific files
set(SRCS ${SRCS} Config/ConfigHandler.cpp Config/ConfigHandler.h)

add_executable(panel-pop ${SRCS})

target_link_libraries(panel-pop
        SDL2_mixer
        SDL2_ttf
        freetype
        png
        z
        mpg123
        vorbisfile
        vorbis
        ogg
        FLAC
        mikmod
        SDL2
        vita2d
        SceDisplay_stub
        SceCtrl_stub
        SceAudio_stub
        SceAppUtil_stub
        SceSysmodule_stub
        SceGxm_stub
        SceCommonDialog_stub
        SceTouch_stub
        SceHid_stub
        m
        )
vita_create_self(panel-pop.self panel-pop)

vita_create_vpk(panel-pop.vpk ${VITA_TITLEID} panel-pop.self
        VERSION ${VITA_VERSION}
        NAME ${VITA_APPNAME}
        FILE sce_sys sce_sys
        FILE ../assets/fonts assets/fonts
        FILE ../assets/music assets/music
        FILE ../assets/sfx assets/sfx
        FILE ../assets/1p.bmp assets/1p.bmp
        FILE ../assets/2p.bmp assets/2p.bmp
        FILE ../assets/bg1.bmp assets/bg1.bmp
        FILE ../assets/sprites.bmp assets/sprites.bmp
        FILE ../assets/title.bmp assets/title.bmp
        )

project(ActorKeyboardLayout)
cmake_minimum_required(VERSION 3.0)

find_package(Kumir2 REQUIRED)
kumir2_use_qt(Core Gui)

if(${USE_QT} GREATER 4 AND UNIX AND NOT APPLE)
        find_package(Qt5 5.3.0 COMPONENTS X11Extras REQUIRED)
        include_directories(${Qt5X11Extras_INCLUDE_DIRS})
        list(APPEND QT_LIBRARIES ${Qt5X11Extras_LIBRARIES})
endif()

set(EXTRA_LIBS)

if(UNIX AND NOT APPLE)
        find_package(X11 REQUIRED)
        set(EXTRA_LIBS ${X11_LIBRARIES})
endif()

add_definitions(-DQT_NONLATIN_SHORTCUTS_BUG)

if(APPLE)
        set(SOURCES ${SOURCES}
                mac-util.mm
        )
        find_library(COCOA_LIBRARY Cocoa)
        set(EXTRA_LIBS ${COCOA_LIBRARY})
endif(APPLE)


set(SOURCES
    keyboardlayoutmodule.cpp
)

set(MOC_HEADERS
    keyboardlayoutmodule.h
)

kumir2_wrap_cpp(MOC_SOURCES ${MOC_HEADERS})

kumir2_add_actor(
    NAME        KeyboardLayout
    SOURCES     ${SOURCES} ${MOC_SOURCES}
    LIBRARIES   ${QT_LIBRARIES} ${EXTRA_LIBS}
)

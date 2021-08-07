project(ActorKeyboardLayout)
cmake_minimum_required(VERSION 3.0)

find_package(Kumir2 REQUIRED)
kumir2_use_qt(Core Gui)


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
    LIBRARIES   ${QT_LIBRARIES}
)

project(ActorJAOS)
cmake_minimum_required(VERSION 3.0)

find_package(Kumir2 REQUIRED)
kumir2_use_qt(Core Gui WebSockets)


set(SOURCES
    echoclient.cpp
    jaosmodule.cpp
    jaosmodule_my.cpp
)

set(MOC_HEADERS
    echoclient.h
    jaosmodule_my.h
    jaosmodule.h
)

kumir2_wrap_cpp(MOC_SOURCES ${MOC_HEADERS})

kumir2_add_actor(
    NAME        JAOS
    SOURCES     ${SOURCES} ${MOC_SOURCES}
    LIBRARIES   ${QT_LIBRARIES}
)

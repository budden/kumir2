project(ActorVodoley)
cmake_minimum_required(VERSION 3.0)

find_package(Kumir2 REQUIRED)
kumir2_use_qt(Core Gui)


set(SOURCES
	otimer.cpp
	pult.cpp
	dialog.cpp
	vial.cpp
	vodoley.cpp
	vodoleymodule.cpp
)

set(MOC_HEADERS
	otimer.h
	pult.h
	dialog.h
	vial.h
	vodoley.h
	vodoleymodule.h
)

set(FORMS
	dialog.ui
	pult.ui
)

kumir2_wrap_cpp(MOC_SOURCES ${MOC_HEADERS})
kumir2_wrap_ui(UI_SOURCES ${FORMS})

kumir2_add_actor(
    NAME        Vodoley
    SOURCES     ${SOURCES} ${MOC_SOURCES} ${UI_SOURCES}
    LIBRARIES   ${QT_LIBRARIES}
)


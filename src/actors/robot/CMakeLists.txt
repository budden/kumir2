project(ActorRobot)
cmake_minimum_required(VERSION 3.0)

find_package(Kumir2 REQUIRED)
kumir2_use_qt(Core Gui)

set(SOURCES
	srobot.cpp
	editline.cpp
	cfield.cpp
	rfield.cpp
	robotview.cpp
	pult.cpp
	robotmodule.cpp
	robotmodulebase.cpp
	robotplugin.cpp
)

set(MOC_HEADERS
	srobot.h
	editline.h
	rfield.h
	robotview.h
	pult.h
	robotmodule.h
	robotmodulebase.h
	robotplugin.h
)

set(FORMS
	pult.ui
)

kumir2_wrap_cpp(MOC_SOURCES ${MOC_HEADERS})
kumir2_wrap_ui(UI_SOURCES ${FORMS})

kumir2_add_simple_actor(
	NAME        Robot
	SOURCES     ${SOURCES} ${MOC_SOURCES} ${UI_SOURCES}
	LIBRARIES   ${QT_LIBRARIES}
)

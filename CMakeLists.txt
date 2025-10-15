cmake_minimum_required(VERSION 4.0)
project(Aether-Engine)
set(CMAKE_PREFIX_PATH "C:/Qt/6.10.0/mingw_64")
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_AUTOUIC_SEARCH_PATHS ${CMAKE_SOURCE_DIR}/resources/ui)


find_package(Qt6 COMPONENTS
		Core
		Gui
		Widgets
		REQUIRED)

# find zeroMQ
set(ZeroMQ_DIR "C:/Users/DevAccount/.vcpkg-clion/vcp/installed/x64-mingw-dynamic/share/zeromq")
find_package(ZeroMQ CONFIG REQUIRED)
set(cppzmq_DIR "C:/Users/DevAccount/.vcpkg-clion/vcp/installed/x64-mingw-dynamic/share/cppzmq")
find_package(cppzmq CONFIG REQUIRED)



set(nlohmann_json_DIR "C:/Users/DevAccount/.vcpkg-clion/vcp/installed/x64-mingw-dynamic/share/nlohmann_json")
find_package(nlohmann_json REQUIRED)

set(SOURCES
		src/main.cpp
		src/ipc/zmq_listener.cpp
		src/UI/components/main_window.cpp
		src/UI/components/menu_bar.cpp
		src/UI/components/Docker/Docker.cpp
		src/UI/components/Docker/dockerPanel.cpp
		src/UI/components/Docker/dockerOverlay.cpp
		src/UI/components/Setting/SettingWindow.cpp
		"src/UI/components/Docker/FloatingPanel .cpp"



)
set(HEADERS
		include/PM.h
		include/ipc/zmq_listener.h
		include/UI/components/menu_bar.h
		include/UI/components/main_window.h
		include/UI/components/Docker/Docker.h
		include/UI/components/Docker/dockerPanel.h
		include/UI/components/Docker/dockerOverlay.h
		include/UI/components/Setting/SettingWindow.h
		"include/UI/components/Docker/FloatingPanel.h"

)

set (RESOURCES
		resources/ui/main_window.ui
		resources/ui/SettingWindow.ui
)

add_executable(Aether-Engine
		${SOURCES}
		${HEADERS}
		${RESOURCES}
		)

target_include_directories( Aether-Engine PRIVATE
		${CMAKE_SOURCE_DIR}/include
 )



target_link_libraries(Aether-Engine PRIVATE
		Qt6::Core
		Qt6::Gui
		Qt6::Widgets
		nlohmann_json::nlohmann_json
		cppzmq

)


if (WIN32 AND NOT DEFINED CMAKE_TOOLCHAIN_FILE)
	set(DEBUG_SUFFIX)
	if (MSVC AND CMAKE_BUILD_TYPE MATCHES "Debug")
		set(DEBUG_SUFFIX "d")
	endif ()
	set(QT_INSTALL_PATH "${CMAKE_PREFIX_PATH}")
	if (NOT EXISTS "${QT_INSTALL_PATH}/bin")
		set(QT_INSTALL_PATH "${QT_INSTALL_PATH}/..")
		if (NOT EXISTS "${QT_INSTALL_PATH}/bin")
			set(QT_INSTALL_PATH "${QT_INSTALL_PATH}/..")
		endif ()
	endif ()
	if (EXISTS "${QT_INSTALL_PATH}/plugins/platforms/qwindows${DEBUG_SUFFIX}.dll")
		add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
				COMMAND ${CMAKE_COMMAND} -E make_directory
				"$<TARGET_FILE_DIR:${PROJECT_NAME}>/plugins/platforms/")
		add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
				COMMAND ${CMAKE_COMMAND} -E copy
				"${QT_INSTALL_PATH}/plugins/platforms/qwindows${DEBUG_SUFFIX}.dll"
				"$<TARGET_FILE_DIR:${PROJECT_NAME}>/plugins/platforms/")
	endif ()
	foreach (QT_LIB Core Gui Widgets)
		add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
				COMMAND ${CMAKE_COMMAND} -E copy
				"${QT_INSTALL_PATH}/bin/Qt6${QT_LIB}${DEBUG_SUFFIX}.dll"
				"$<TARGET_FILE_DIR:${PROJECT_NAME}>")
	endforeach (QT_LIB)
endif ()
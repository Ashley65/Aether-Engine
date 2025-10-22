cmake_minimum_required(VERSION 3.18)
project(Aether-Engine VERSION 0.1.0 LANGUAGES CXX CUDA)
set(CMAKE_PREFIX_PATH "C:/Qt/6.10.0/msvc2022_64")
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CUDA_STANDARD 14)
set(CMAKE_CUDA_STANDARD_REQUIRED ON)


# Enable automatic MOC, UIC, RCC for Qt
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOUIC_SEARCH_PATHS ${CMAKE_SOURCE_DIR}/resources/ui)


find_package(Qt6 COMPONENTS
		Core
		Gui
		Widgets
		REQUIRED)



set(ZeroMQ_DIR "C:/Users/DevAccount/.vcpkg-clion/vcp/installed/x64-windows/share/zeromq")
find_package(ZeroMQ CONFIG REQUIRED)

set(cppzmq_DIR "C:/Users/DevAccount/.vcpkg-clion/vcp/installed/x64-windows/share/cppzmq")
find_package(cppzmq CONFIG REQUIRED)

set(nlohmann_json_DIR "C:/Users/DevAccount/.vcpkg-clion/vcp/installed/x64-windows/share/nlohmann_json")
find_package(nlohmann_json REQUIRED)



if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
	add_compile_options(-Wall -Wextra -Wpedantic)
endif()

set(SOURCES
		src/main.cpp
		src/ipc/zmq_listener.cpp
		src/UI/components/main_window.cpp
		src/UI/components/menu_bar.cpp
		src/UI/components/Docker/Docker.cpp
		src/UI/components/Docker/dockerPanel.cpp
		src/UI/components/Docker/dockerOverlay.cpp
		src/UI/components/Setting/SettingWindow.cpp
		src/UI/components/Setting/Tabs/simulationtab.cpp
		src/UI/components/Docker/FloatingPanel.cpp
		src/UI/components/Setting/utils/settingManager.cpp
		src/UI/components/Setting/Tabs/hardwaretab.cpp
		src/UI/components/Setting/Tabs/physicsenginetab.cpp
		src/UI/components/Setting/Tabs/aiagenttab.cpp
		src/UI/components/Setting/Tabs/communicationtab.cpp
		src/UI/components/Setting/Tabs/envtab.cpp
		src/UI/components/Setting/Tabs/dronetab.cpp
		src/UI/components/Setting/Tabs/advancedtab.cpp
		src/UI/components/Setting/Tabs/visualisationtab.cpp


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
		include/UI/components/Setting/Tabs/simulationtab.h
		include/UI/components/Docker/FloatingPanel.h
		include/UI/components/Setting/utils/settingManager.h
		include/UI/components/Setting/Tabs/physicsenginetab.h
		include/UI/components/Setting/Tabs/aiagenttab.h
		include/UI/components/Setting/Tabs/hardwaretab.h
		include/UI/components/Setting/Tabs/communicationtab.h
		include/UI/components/Setting/Tabs/envtab.h
		include/UI/components/Setting/Tabs/visualisationtab.h
		include/UI/components/Setting/Tabs/advancedtab.h
		include/UI/components/Setting/Tabs/dronetab.h
)

set (RESOURCES
		resources/ui/main_window.ui
		resources/ui/SettingWindow.ui
		resources/ui/simulationtab.ui
		resources/ui/physicsenginetab.ui
		resources/ui/aiagenttab.ui
		resources/ui/hardwaretab.ui
		resources/ui/communicationtab.ui
		resources/ui/envtab.ui
		resources/ui/visualisationtab.ui
		resources/ui/advancedtab.ui
		resources/ui/dronetab.ui


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




# Set CUDA properties
set_target_properties(Aether-Engine PROPERTIES
		CUDA_SEPARABLE_COMPILATION ON
		CUDA_RESOLVE_DEVICE_SYMBOLS ON
)



if (WIN32)
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
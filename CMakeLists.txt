cmake_minimum_required(VERSION 3.16)

project(untitled1 VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Quick QuickControls2 WebSockets Gui Qml Network Svg)

qt_standard_project_setup(REQUIRES 6.5)

qt_add_executable(appuntitled1
    main.cpp
)

target_include_directories(appuntitled1 PRIVATE ExternalLibs/qrgenerator)

qt_add_qml_module(appuntitled1
    URI untitled1
    VERSION 1.0
    QML_FILES
        Main.qml
        SOURCES backend.h backend.cpp
        SOURCES serverworker.h serverworker.cpp
        SOURCES mouse.h mouse.cpp
        SOURCES keyboard.h keyboard.cpp
        SOURCES webclientworker.h webclientworker.cpp
        SOURCES ExternalLibs/qrgenerator/qrcodegen.cpp ExternalLibs/qrgenerator/qrcodegen.hpp
        SOURCES qrgenerator.h qrgenerator.cpp
        SOURCES svgelement.h svgelement.cpp
        SOURCES Capture/capture.h Capture/capture.cpp
        QML_FILES Service_Status.qml
)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
set_target_properties(appuntitled1 PROPERTIES
#    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.appuntitled1
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(appuntitled1
    PRIVATE Qt6::Quick
            Qt6::QuickControls2
            Qt6::WebSockets
            Qt6::Gui
            Qt6::Qml
            Qt6::Network
            Qt6::Svg
)


# Copy Client server executable to the runtime location
set(CLIENT_SERVER_EXECUTABLE ${CMAKE_SOURCE_DIR}/clientserver/sc_backend.exe)
add_custom_command(
    TARGET appuntitled1 POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
            ${CLIENT_SERVER_EXECUTABLE}
            ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}
)



include(GNUInstallDirs)
install(TARGETS appuntitled1
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

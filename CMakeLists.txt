cmake_minimum_required(VERSION 3.16)

project(WindowOCR_Paddle VERSION 0.1 LANGUAGES CXX)

if(MSVC)
    add_compile_options(/utf-8)
endif()

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(OpenCV_DIR "D:/opencv/build/x64/vc16/lib")

find_package(OpenCV REQUIRED)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets Concurrent)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(WindowOCR_Paddle
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET WindowOCR_Paddle APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(WindowOCR_Paddle SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(WindowOCR_Paddle
            ${PROJECT_SOURCES}
            selectionwindow.h selectionwindow.cpp
            cardlabel.h cardlabel.cpp
            cardsscreen.h cardsscreen.cpp cardsscreen.ui
            simple_ocr.h
        )
    endif()
endif()





set(PPOCR_LIB_PATH "${CMAKE_CURRENT_SOURCE_DIR}/build/Desktop_Qt_5_15_2_MSVC2019_64bit-Release")


target_link_libraries(WindowOCR_Paddle PRIVATE Qt${QT_VERSION_MAJOR}::Widgets
    ${PPOCR_LIB_PATH}/ocr_system.lib
    ${OpenCV_LIBS}
)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.WindowOCR_Paddle)
endif()
set_target_properties(WindowOCR_Paddle PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS WindowOCR_Paddle
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(WindowOCR_Paddle)
endif()

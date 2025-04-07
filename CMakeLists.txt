cmake_minimum_required(VERSION 3.16)

project(QuaverMetadataChanger VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets LinguistTools)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets LinguistTools)

set(TS_FILES translations/QuaverMetadataChanger_zh.ts translations/QuaverMetadataChanger_en.ts)

set(QT_I18N_TRANSLATED_LANGUAGES zh)
set(PROJECT_SOURCES
        src/main.cpp
        src/MainWindow.cpp
        include/MainWindow.h
        src/mainwindow.ui
        include/MapListModel.h src/MapListModel.cpp
        include/MapItem.h src/MapItem.cpp
        include/QuaverMap.h src/QuaverMap.cpp
        include/StringFieldEdit.h src/StringFieldEdit.cpp
        include/MapStringEdit.h src/MapStringEdit.cpp
        include/QVariantHasher.h
        ${TS_FILES}
        include/MapListFieldEdit.h
        src/MapListFieldEdit.cpp
        src/MapListFieldEdit.ui
)

include_directories(include)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(QuaverMetadataChanger
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        translations.qrc
        .gitignore
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET QuaverMetadataChanger APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation

    # qt_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
else()
    if(ANDROID)
        add_library(QuaverMetadataChanger SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(QuaverMetadataChanger
            ${PROJECT_SOURCES}
        )
    endif()

    # qt5_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
endif()

qt_add_translations(QuaverMetadataChanger
    TS_OUTPUT_DIRECTORY translations
)

target_link_libraries(QuaverMetadataChanger PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

# --------------YAML------------------
include(FetchContent)

FetchContent_Declare(
  yaml-cpp
  GIT_REPOSITORY https://github.com/jbeder/yaml-cpp.git
  GIT_TAG 0.8.0 # Can be a tag (yaml-cpp-x.x.x), a commit hash, or a branch name (master)
)
FetchContent_MakeAvailable(yaml-cpp)
# --------------YAML END--------------

target_link_libraries(QuaverMetadataChanger PUBLIC yaml-cpp::yaml-cpp) # The library or executable that require yaml-cpp library

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.QuaverMetadataChanger)
endif()
set_target_properties(QuaverMetadataChanger PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS QuaverMetadataChanger
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(QuaverMetadataChanger)
endif()

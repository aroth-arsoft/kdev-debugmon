project(kdev-debugmon)

set(VERSION_MAJOR 0)
set(VERSION_MINOR 80)
set(VERSION_PATCH 0)
# KDevplatform dependency version
set( KDEVPLATFORM_VERSION 1.90.90 )

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake/)

cmake_minimum_required(VERSION 2.8.12)
find_package (ECM 0.0.9 REQUIRED NO_MODULE)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${ECM_MODULE_PATH})

include(ECMAddTests)
include(KDEInstallDirs)
include(KDECMakeSettings)
include(KDECompilerSettings)

add_definitions(-DQT_USE_FAST_CONCATENATION -DQT_USE_FAST_OPERATOR_PLUS -DQT_NO_URL_CAST_FROM_STRING)

find_package(Qt5 REQUIRED Core Widgets Test)
find_package(KF5 REQUIRED COMPONENTS ThreadWeaver I18n TextEditor ItemModels SysGuard)
find_package(KDevPlatform ${KDEVPLATFORM_VERSION} REQUIRED)
find_package(KDevelop REQUIRED)

# Turn off missing-field-initializers warning for GCC to avoid noise from false positives with empty {}
# See discussion: http://mail.kde.org/pipermail/kdevelop-devel/2014-February/046910.html
if (CMAKE_COMPILER_IS_GNUCXX)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-missing-field-initializers")
endif()

configure_file(
  "${CMAKE_CURRENT_SOURCE_DIR}/version.h.cmake"
  "${CMAKE_CURRENT_BINARY_DIR}/version.h"
  @ONLY
)

enable_testing()

include_directories(
    ${KDEVELOP_INCLUDE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_BINARY_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/libs
)

#add_subdirectory(tests)

set(kdevdebugmon_SRCS
    debugmonplugin.cpp
    appperf.cpp
)

kdevplatform_add_plugin(kdevdebugmon JSON kdevdebugmon.json SOURCES ${kdevdebugmon_SRCS})

target_link_libraries(kdevdebugmon
    KF5::ThreadWeaver
    KF5::TextEditor
    KF5::SysGuard
    KF5::ProcessUi
    KDev::Util
    KDev::Interfaces
    KDev::Sublime
)

install(FILES kdevdebugmon.rc DESTINATION ${KXMLGUI_INSTALL_DIR}/kdevdebugmon)

feature_summary(WHAT ALL FATAL_ON_MISSING_REQUIRED_PACKAGES)

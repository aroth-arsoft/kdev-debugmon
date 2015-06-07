
include_directories(${CMAKE_CURRENT_BINARY_DIR})
configure_file(config-workspace.h.cmake ${CMAKE_CURRENT_BINARY_DIR}/config-workspace.h)


include_directories(
   SensorDisplayLib/
)


########### next target ###############

add_definitions(-DTRANSLATION_DOMAIN=\"ksysguard\")

set(libsensordisplays_SRCS
   	SensorDisplayLib/SensorDisplay.cpp
   	SensorDisplayLib/BarGraph.cpp
   	SensorDisplayLib/DancingBars.cpp
   	SensorDisplayLib/DancingBarsSettings.cpp
   	SensorDisplayLib/DummyDisplay.cpp
   	SensorDisplayLib/FancyPlotter.cpp
   	SensorDisplayLib/FancyPlotterSettings.cpp
   	SensorDisplayLib/ListView.cpp
   	SensorDisplayLib/LogFile.cpp
   	SensorDisplayLib/MultiMeter.cpp
   	SensorDisplayLib/MultiMeterSettings.cpp
   	SensorDisplayLib/ProcessController.cpp
   	SensorDisplayLib/SensorLogger.cpp
   	SensorDisplayLib/SensorLoggerDlg.cpp
   	SensorDisplayLib/SensorLoggerSettings.cpp
   	SensorDisplayLib/SensorModel.cpp
   	SensorDisplayLib/ListViewSettings.cpp
#   	SensorDisplayLib/modeltest.cpp
	)

ki18n_wrap_ui( libsensordisplays_SRCS
   SensorDisplayLib/ListViewSettingsWidget.ui
   SensorDisplayLib/LogFileSettings.ui
   SensorDisplayLib/MultiMeterSettingsWidget.ui
   SensorDisplayLib/SensorLoggerDlgWidget.ui
   SensorDisplayLib/SensorLoggerSettingsWidget.ui
)

set(ksysguard_KDEINIT_SRCS ${libsensordisplays_SRCS}
   ksortfilterproxymodel.cpp
   SensorBrowser.cpp
   WorkSheet.cpp
   WorkSheetSettings.cpp
   Workspace.cpp
   HostConnector.cpp
   StyleEngine.cpp
   ksysguard.cpp )

add_library(ksysguardui STATIC ${ksysguard_KDEINIT_SRCS})
target_compile_definitions(ksysguardui PRIVATE -DPROJECT_VERSION="${PROJECT_VERSION}")
target_compile_definitions(ksysguardui PRIVATE -DBUILD_KSYSGUARDUI=1)

target_link_libraries(ksysguardui
    KF5::ProcessUi
    KF5::SignalPlotter
    KF5::DBusAddons
    KF5::ItemViews
    KF5::NewStuff
    KF5::SysGuard
    KF5::I18n
    KF5::IconThemes
    KF5::KDELibs4Support
    )

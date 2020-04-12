#-------------------------------------------------
#
# Project created by QtCreator 2018-12-02T15:42:15
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Scan2Slice
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        main.cpp \
        gui/mainwindow.cpp \
    models/repository/repository.cpp \
    models/router.cpp \
    models/services/gcodes_view/gcodes_view_interactor.cpp \
    models/services/linear_scan/linear_scan_interactor.cpp \
    models/services/read_points_from_file/read_points_from_file_interactor.cpp \
    models/services/save_points_to_file/save_points_to_file_interactor.cpp \
    models/services/scan_to_slice/scan_to_slice_interactor.cpp \
    models/services/slice_scan/slice_scan_interactor.cpp \
    models/services/spiral_scan/spiral_scan_interactor.cpp \
    models/services/split_to_scans/split_to_scans_interactor.cpp \
    models/settings_manager/settings_manager.cpp \
    models/types/linear_interpolation/linear_equation.cpp \
    models/types/linear_interpolation/linear_interpolated_polynomial.cpp \
    models/types/point_3d/point_3d.cpp \
    models/types/scan/scan.cpp

HEADERS += \
        gui/mainwindow.h \
    libs/spline/src/spline.h \
    models/repository/repository.h \
    models/router.h \
    models/services/gcodes_view/gcodes_view_interactor.h \
    models/services/linear_scan/linear_scan_interactor.h \
    models/services/read_points_from_file/read_points_from_file_interactor.h \
    models/services/save_points_to_file/save_points_to_file_interactor.h \
    models/services/scan_to_slice/scan_to_slice_interactor.h \
    models/services/slice_scan/slice_scan_interactor.h \
    models/services/spiral_scan/spiral_scan_interactor.h \
    models/services/split_to_scans/split_to_scans_interactor.h \
    models/settings_manager/settings_manager.h \
    models/types/linear_interpolation/linear_equation.h \
    models/types/linear_interpolation/linear_interpolated_polynomial.h \
    models/types/point_3d/point_3d.h \
    models/types/scan/scan.h

FORMS += \
        gui/mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

macx: target.path = /opt/$${TARGET}/bin

RESOURCES += \
    gui/resources/resources.qrc

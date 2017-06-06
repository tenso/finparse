QT += qml quick

CONFIG += c++11

SOURCES += src/main.cpp \
    src/System.cpp \
    src/PdfDocumentModel.cpp

RESOURCES += src/qml/qml.qrc

INCLUDEPATH += 3rd_party/poppler_bin/include/poppler/cpp/

OTHER_FILES += .gitignore

MOC_DIR = build
OBJECTS_DIR = build
RCC_DIR = build

DEFINES += QT_DEPRECATED_WARNINGS
LIBS += "-lpoppler-qt5"
# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    src/System.hpp \
    src/PdfDocumentModel.hpp

DISTFILES += \
    3rd_party/readme.md \
    readme.md

TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    encryption.cpp \
    keygenerator.cpp \
    tables.cpp \
    decryption.cpp

HEADERS += \
    encryption.h \
    keygenerator.h \
    tables.h \
    decryption.h

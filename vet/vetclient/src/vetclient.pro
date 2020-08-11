QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += \
	main.cpp \
	types/address.cpp \
	types/client.cpp \
	types/contract.cpp \
	types/microchip.cpp \
	types/passport.cpp \
	types/position.cpp \
	types/shedule.cpp \
	types/staff.cpp \
	types/user_data.cpp \
	utlis/utils.cpp

HEADERS += \
	core/ISerializable.h \
	types/QJsonHeaders.h \
	types/address.h \
	types/client.h \
	types/contract.h \
	types/json_fields.h \
	types/microchip.h \
	types/passport.h \
	types/position.h \
	types/shedule.h \
	types/staff.h \
	types/user_data.h \
	utlis/utils.h

FORMS += \
    ui/add_contract.ui \
    ui/address.ui \
    ui/admin.ui \
    ui/animal.ui \
    ui/auth_dialog.ui \
    ui/chip.ui \
    ui/contacts.ui \
    ui/passport.ui \
    ui/shedule.ui \
    ui/staff.ui \
    ui/vaccination.ui \
    ui/visit.ui

qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

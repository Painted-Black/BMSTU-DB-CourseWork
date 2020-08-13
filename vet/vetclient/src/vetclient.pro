QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++14

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += \
	core/fetcher.cpp \
	main.cpp \
	types/address.cpp \
	types/animal_medical_record.cpp \
	types/animalstate.cpp \
	types/client.cpp \
	types/contract.cpp \
	types/gender.cpp \
	types/microchip.cpp \
	types/passport.cpp \
	types/position.cpp \
	types/prescribings.cpp \
	types/shedule.cpp \
	types/staff.cpp \
	types/user_data.cpp \
	types/vaccination.cpp \
	types/visit.cpp \
	utlis/utils.cpp

HEADERS += \
	core/ISerializable.h \
	core/fetcher.h \
	types/QJsonHeaders.h \
	types/address.h \
	types/animal_medical_record.h \
	types/animalstate.h \
	types/client.h \
	types/contract.h \
	types/gender.h \
	types/json_fields.h \
	types/microchip.h \
	types/passport.h \
	types/position.h \
	types/prescribings.h \
	types/shedule.h \
	types/staff.h \
	types/user_data.h \
	types/vaccination.h \
	types/visit.h \
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

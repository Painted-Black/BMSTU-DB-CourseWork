QT	   += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++14

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += \
	config/config.cpp \
	config/consoleparser.cpp \
	core/account_info_widget.cpp \
	core/animal_edit_widget.cpp \
	core/animal_info_widget.cpp \
	core/animal_list_item_widget.cpp \
	core/auth.cpp \
	core/mainwindow.cpp \
	core/new_visit_widget.cpp \
	core/network/network_fetcher.cpp \
	core/popup.cpp \
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
	types/schedule.cpp \
	types/short_animal_info.cpp \
	types/staff.cpp \
	types/user_data.cpp \
	types/vaccination.cpp \
	types/visit.cpp \
	core/add_med_dialog.cpp \
	utils/utils.cpp \
	model/prescribings_table_model.cpp

HEADERS += \
	config/config.h \
	config/consoleparser.h \
	core/account_info_widget.h \
	core/add_contract_widget.h \
	core/animal_edit_widget.h \
	core/animal_info_widget.h \
	core/animal_list_item_widget.h \
	core/auth.h \
	core/new_visit_widget.h \
	core/iserializable.h \
	core/mainwindow.h \
	core/network/network_fetcher.h \
	core/popup.h \
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
	types/proxy_auth.h \
	types/schedule.h \
	types/short_animal_info.h \
	types/staff.h \
	types/user_data.h \
	types/vaccination.h \
	core/add_med_dialog.h \
	model/prescribings_table_model.h \
	types/visit.h \
	utils/utils.h \
	utils/singlenton.h

FORMS += \
	ui/acc_info.ui \
	ui/add_contract.ui \
	 ui/add_med_dialog.ui \
	ui/address.ui \
	ui/admin.ui \
	ui/animal.ui \
	ui/animal_list_item_widget.ui \
	ui/auth_dialog.ui \
	ui/chip.ui \
	ui/client.ui \
	ui/contacts.ui \
	ui/mainwindow.ui \
	ui/passport.ui \
	ui/prescribings_widget.ui \
	ui/shedule.ui \
	ui/staff.ui \
	ui/text_dialog.ui \
	ui/visit.ui

LIBS += -lcurl

qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
	res.qrc

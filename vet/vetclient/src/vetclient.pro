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
	core/animal_list_item_widget.cpp \
	core/auth.cpp \
	core/client_list_widget.cpp \
    core/chose_staff_full_dialog.cpp \
	core/contacts.cpp \
	core/chose_animal_dialog.cpp \
	core/chose_animal_full_dialog.cpp \
	core/mainwindow.cpp \
	core/new_visit_widget.cpp \
	core/network/network_fetcher.cpp \
    core/password_line_edit.cpp \
	core/popup.cpp \
	main.cpp \
    model/positions_table_model.cpp \
    model/schedules_table_model.cpp \
    model/staff_schedule_tablemodel.cpp \
    model/staff_table_model.cpp \
	model/users_table_model.cpp \
	types/address.cpp \
	types/animal_medical_record.cpp \
	types/animalstate.cpp \
	types/client.cpp \
	types/contract.cpp \
	types/gender.cpp \
	types/image_loader.cpp \
	types/microchip.cpp \
	types/passport.cpp \
	types/position.cpp \
	types/prescribings.cpp \
	types/schedule.cpp \
	types/sheduled_visits.cpp \
    types/shedules_short_info.cpp \
	types/short_animal_info.cpp \
    types/short_staff_info.cpp \
	types/short_user_info.cpp \
    types/short_visit_info.cpp \
	types/staff.cpp \
	types/user_data.cpp \
	types/vaccination.cpp \
	types/visit.cpp \
	core/add_med_dialog.cpp \
    core/main_tab_widget.cpp \
    core/admin_pannel.cpp \
    core/user_info.cpp \
    core/user_info_dialog.cpp \
    core/question_dialog.cpp \
    core/change_login_dialog.cpp \
    core/change_password_dialog.cpp \
    core/chose_access_leveldialog.cpp \
    core/add_user_dialog.cpp \
    core/chose_staff_dialog.cpp \
    core/user_list_item_widget.cpp \
    core/main_vet_pannel.cpp \
    core/position_info_dialog.cpp \
    core/staff_tab_widget.cpp \
    core/fire_dialog.cpp \
    core/add_staff_dialog.cpp \
    core/add_shedule_item_dialog.cpp \
    core/scheduleswidget.cpp \
    core/visit_list_item_widget.cpp \
    core/visits_widget.cpp \
    core/scroll_dialog.cpp \
	utils/utils.cpp \
	model/prescribings_table_model.cpp

HEADERS += \
	config/config.h \
	config/consoleparser.h \
	core/account_info_widget.h \
	core/animal_edit_widget.h \
	core/animal_list_item_widget.h \
	core/auth.h \
	core/client_list_widget.h \
    core/chose_staff_full_dialog.h \
	core/contacts.h \
	core/chose_animal_dialog.h \
	core/chose_animal_full_dialog.h \
	core/new_visit_widget.h \
	core/iserializable.h \
	core/mainwindow.h \
	core/network/network_fetcher.h \
    core/password_line_edit.h \
	core/popup.h \
    model/positions_table_model.h \
    model/schedules_table_model.h \
    model/staff_schedule_tablemodel.h \
    model/staff_table_model.h \
	model/users_table_model.h \
	types/QJsonHeaders.h \
	types/address.h \
	types/animal_medical_record.h \
	types/animalstate.h \
	types/client.h \
	types/contract.h \
	types/gender.h \
	types/image_loader.h \
	types/json_fields.h \
	types/microchip.h \
	types/passport.h \
	types/position.h \
	types/prescribings.h \
	types/proxy_auth.h \
	types/schedule.h \
	types/sheduled_visits.h \
    types/shedules_short_info.h \
	types/short_animal_info.h \
    types/short_staff_info.h \
    types/short_user_info.h \
    types/short_visit_info.h \
	types/staff.h \
	types/user_data.h \
	types/vaccination.h \
	core/add_med_dialog.h \
	model/prescribings_table_model.h \
	types/visit.h \
    core/main_tab_widget.h \
    core/admin_pannel.h \
    core/user_info.h \
    core/user_info_dialog.h \
    core/question_dialog.h \
    core/change_login_dialog.h \
    core/change_password_dialog.h \
    core/chose_access_leveldialog.h \
    core/add_user_dialog.h \
    core/chose_staff_dialog.h \
    core/user_list_item_widget.h \
    core/main_vet_pannel.h \
    core/position_info_dialog.h \
    core/staff_tab_widget.h \
    core/fire_dialog.h \
    core/add_staff_dialog.h \
    core/add_shedule_item_dialog.h \
    core/scheduleswidget.h \
    core/visit_list_item_widget.h \
    core/visits_widget.h \
    core/scroll_dialog.h \
	utils/utils.h \
	utils/singlenton.h

FORMS += \
    ui/add_shedule_item_dialog.ui \
    ui/add_staff_dialog.ui \
    ui/chose_staff_full_dialog.ui \
    ui/add_user_dialog.ui \
	ui/admin_pannel.ui \
	ui/change_login_dialog.ui \
	ui/change_password_dialog.ui \
	ui/chose_access_leveldialog.ui \
	ui/chose_animal_full_dialog.ui \
	ui/chose_animal_dialog.ui \
	ui/acc_info.ui \
	ui/add_contract.ui \
	ui/add_med_dialog.ui \
	ui/address.ui \
	ui/animal.ui \
	ui/animal_list_item_widget.ui \
	ui/auth_dialog.ui \
	ui/chip.ui \
    ui/chose_staff_dialog.ui \
	ui/client.ui \
	ui/client_item_widget.ui \
	ui/client_widget_list.ui \
	ui/contacts.ui \
    ui/fire_dialog.ui \
    ui/scroll_dialog.ui \
    ui/scheduleswidget.ui \
	ui/main_tab_widget.ui \
    ui/main_vet_pannel.ui \
	ui/mainwindow.ui \
	ui/passport.ui \
    ui/position_info_dialog.ui \
	ui/prescribings_widget.ui \
    ui/question_dialog.ui \
	ui/shedule.ui \
    ui/staff_tab_widget.ui \
	ui/text_dialog.ui \
	ui/user_info.ui \
    ui/user_info_dialog.ui \
    ui/user_list_item_widget.ui \
	ui/visit.ui \
    ui/visit_list_item_widget.ui \
    ui/visits_widget.ui

LIBS += -lcurl

qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
	res.qrc

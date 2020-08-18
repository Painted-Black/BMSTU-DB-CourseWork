#pragma once

#include <QString>

namespace AddressJson
{
	const QString field_addr_id = "addr_id";
	const QString field_addr_country = "country";
	const QString field_addr_city = "city";
	const QString field_addr_street = "street";
	const QString field_addr_house = "house";
	const QString field_addr_flat = "flat";
}

namespace PassportJson
{
	const QString field_pass_id = "pass_id";
	const QString field_pass_surname = "surname";
	const QString field_pass_name = "name";
	const QString field_pass_patronymic = "patronymic";
	const QString field_pass_sex = "sex";
	const QString field_pass_birth = "birth";
	const QString field_pass_num = "num";
	const QString field_pass_issue_date = "issue_date";
	const QString field_pass_nationality = "nationality";
}

namespace ClientJson
{
	const QString field_cli_id = "cli_id";
	const QString field_cli_contacts = "contacts";
	const QString field_cli_address = "address";
	const QString field_cli_passport = "passport";
	const QString field_cli_phone = "phone";
	const QString field_cli_email = "email";
	const QString field_cli_social = "social";
}

namespace ContractJson
{
	const QString field_contr_id = "contr_id";
	const QString field_contr_code = "code";
	const QString field_contr_conclusion_date = "conclusion_date";
	const QString field_contr_last_update_date = "last_update_date";
	const QString field_contr_owner = "owner";
	const QString field_contr_valid_until = "valid_until";
}

namespace MicrochipJson
{
	const QString field_chip_id = "chip_id";
	const QString field_chip_chip_num = "chip_num";
	const QString field_chip_impl_date = "impl_date";
	const QString field_chip_country = "country";
	const QString field_chip_location = "location";
}

namespace PositionJson
{
	const QString field_pos_id = "pos_id";
	const QString field_pos_title = "title";
	const QString field_pos_salary = "salary";
}

namespace StaffJson
{
	const QString field_staff_id = "staff_id";
	const QString field_staff_passport = "passport";
	const QString field_staff_position = "position";
	const QString field_staff_edu_level = "edu_level";
	const QString field_staff_fire_date = "fire_date";
	const QString field_staff_employ_date = "employ_date";
	const QString field_staff_shedule = "schedule";
}

namespace AnimalMedicalRecordJson
{
	const QString field_anim_id = "anim_id";
	const QString field_anim_name = "name";
	const QString field_anim_breed = "breed";
	const QString field_anim_species = "species";
	const QString field_anim_sex = "sex";
	const QString field_anim_castrated = "castrated";
	const QString field_anim_birth = "birth";
	const QString field_anim_other_data = "other_data";
	const QString field_anim_color = "color";
	const QString field_anim_specil_signs = "specil_signs";
	const QString field_anim_registr_date = "registr_date";
	const QString field_anim_last_visit = "last_visit";
	const QString field_anim_chip_id = "chip_id";
	const QString field_anim_contract = "contract";
	const QString field_anim_rel_path_to_photo = "rel_path_to_photo";
}

namespace AnimalStateJson
{
	const QString field_state_id = "state_id";
	const QString field_state_general = "general";
	const QString field_state_pulse = "pulse";
	const QString field_state_weight = "weight";
	const QString field_state_ap = "ap";
	const QString field_state_temperature = "temperature";
	const QString field_state_cfr = "cfr";
	const QString field_state_resp_rate = "resp_rate";
}

namespace VisitJson
{
	const QString field_vis_id = "vis_id";
	const QString field_vis_doctor = "doctor";
	const QString field_vis_animal = "animal";
	const QString field_vis_ambulatury = "ambulatury";
	const QString field_vis_visit_date = "visit_date";
	const QString field_vis_owner_dynamics = "owner_dynamics";
	const QString field_vis_history_disease = "history_disease";
	const QString field_vis_cur_state = "cur_state";
	const QString field_vis_diagnosis = "diagnosis";
	const QString field_vis_recommendations = "recommendations";
	const QString field_vis_next_visit = "next_visit";
	const QString field_vis_prescribings = "prescribings";
	const QString field_vis_initial = "initial";
	const QString field_vis_note = "note";
}

namespace VaccinationJson
{
	const QString field_vac_id = "vac_id";
	const QString field_vac_against = "against";
	const QString field_vac_reg_num = "reg_num";
	const QString field_vac_vac_date = "vac_date";
	const QString field_vac_next_vac = "next_vac";
	const QString field_vac_animal = "animal";
	const QString field_vac_vet = "vet";
}

namespace AccessJson
{
	const QString field_acc_id = "acc_id";
	const QString field_acc_employee = "employee";
	const QString field_acc_login = "login";
	const QString field_acc_password = "password";
	const QString field_acc_access_level = "access_level";
}

namespace ScheduleJson
{
	const QString field_shed_id = "shed_id";
	const QString field_shed_employee_id = "employee_id";
	const QString field_shed_day_of_week = "day_of_week";
	const QString field_shed_type = "type";
	const QString field_shed_start = "start";
	const QString field_shed_end = "end";
	const QString field_shed_cabinet = "cabinet";
}

namespace GeneralStateType
{
	const QString general_state_middle = "middle";
	const QString general_state_good = "good";
	const QString general_state_bad = "bad";
}

namespace RusGeneralStateType
{
    const QString rus_general_state_middle = "средне";
    const QString rus_general_state_good = "хорошо";
    const QString rus_general_state_bad = "плохо";
}

namespace GenderType
{
	const QString gender_male = "m";
	const QString gender_female = "f";
	const QString gender_other = "other";
}

namespace GenderRussianType
{
	const QString gender_male = "муж.";
	const QString gender_female = "жен.";
	const QString gender_other = "другое";
}

namespace InjectionTypes
{
	const QString injection_subcutaneous = "s/c";
	const QString injection_intravenous = "i/v";
	const QString injection_intramuscular = "i/m";
	const QString injection_ingest = "ingest";
}

namespace PrescribingsJson
{
	const QString field_prescr_name = "name";
	const QString field_prescr_dosage = "dosage";
	const QString field_prescr_type = "type";
	const QString field_prescr_frequency_of_medication = "frequency_of_medication";
	const QString field_prescr_term_of_taking = "term_of_taking";
	const QString field_prescr_notes = "notes";
}

namespace DayOfWeekType
{
	const QString day_of_week_sun = "Sun";
	const QString day_of_week_mon = "Mon";
	const QString day_of_week_tue = "Tue";
	const QString day_of_week_wed = "Wed";
	const QString day_of_week_thu = "Thu";
	const QString day_of_week_fri = "Fri";
	const QString day_of_week_sat = "Sat";
}

namespace RussianDayOfWeekType
{
    const QString rus_day_of_week_sun = "Воскресенье";
    const QString rus_day_of_week_mon = "Понедельник";
    const QString rus_day_of_week_tue = "Вторник";
    const QString rus_day_of_week_wed = "Среда";
    const QString rus_day_of_week_thu = "Четверг";
    const QString rus_day_of_week_fri = "Пятница";
    const QString rus_day_of_week_sat = "Суббота";
}

namespace EduLevelType
{
	const QString edu_resident = "resident";
	const QString edu_middle = "middle";
	const QString edu_postgraduate = "postgraduate";
	const QString edu_specialist = "specialist";
	const QString edu_bachelor = "bachelor";
}

namespace AccessLevelType
{
	const QString access_vet = "vet";
	const QString access_main = "main";
	const QString access_admin = "admin";
	const QString access_registry = "registry";
}

namespace VaccinationAgainstType
{
	const QString vacc_against_rab = "rab";
	const QString vacc_against_inf = "inf";
}

namespace OwnerDynamicsType
{
	const QString owner_dynamics_stably = "stably";
	const QString owner_dynamics_worse = "worse";
	const QString owner_dynamics_better = "better";
}

namespace RusOwnerDynamicsType
{
    const QString rus_owner_dynamics_stably = "стабильно";
    const QString rus_owner_dynamics_worse = "лучше";
    const QString rus_owner_dynamics_better = "хуже";
}

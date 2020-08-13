#include <QApplication>
#include <QDebug>
#include <QFile>
#include <QCryptographicHash>
#include <QUuid>

#include "utlis/utils.h"
#include "types/staff.h"
#include "types/address.h"
#include "types/microchip.h"
#include "core/fetcher.h"

void cb (uint32_t, std::unique_ptr<QByteArray>);

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

//    Microchip m;
//    m.setChip_num("122435");
//    m.setCountry("Russia");
//    m.setLocation("Back left leg");
//    QDate date(2020, 3, 5);
//    m.setImpl_date(date);
//    qDebug().noquote() << m.serialize();

//	Position p;
//	p.setTitle("Уборщик");
//	p.setSalary(50000);

//	Gender gender;
//	gender.setGenderType(Gender::GenderEnum::Male);

//	Passport pass;
//	pass.setSurname("Бобков");
//	pass.setName("Боб");
//	pass.setPatronymic("Бобович");
//	pass.setGender(gender);
//	pass.setBirthday(QDate::fromString("2019-12-12T12:12:12", Qt::ISODate));
//	pass.setIssue_date(QDate::fromString("2019-11-11T11:11:11", Qt::ISODate));
//	pass.setNationality("Nigerian");

//	EducationLevel level;
//	level.setEducationLevel(EducationLevel::EducationLevelEnum::Bachelor);

//	Staff staff;
//	staff.setPassport(pass);
//	staff.setPosition(p);
//	staff.setEdu_level(level);
//	staff.setFire_date(QDate::fromString("2000-01-01T01:01:01", Qt::ISODate));
//	staff.setEmploy_date(QDate::fromString("2005-10-10T10:10:10", Qt::ISODate));

//	qDebug().noquote() << staff.serialize();

//	QFile f("aaaa.json");
//	if (f.open(QIODevice::ReadWrite) == false)
//	{
//		qCritical() << f.errorString();
//		return 1;
//	}

//	QTextStream stream(&f);
//	stream << toJson(staff.serialize());
//	f.close();

	return a.exec();
}

#include <QNetworkReply>
#include <QTextEdit>
#include <QScrollArea>
#include <QFileDialog>
#include "ui_animal.h"
#include "ui_text_dialog.h"
#include "ui_add_contract.h"
#include "ui_chip.h"
#include "ui_client.h"
#include "ui_contacts.h"
#include "ui_address.h"
#include "ui_passport.h"
#include "types/image_loader.h"
#include "types/json_fields.h"
#include "animal_edit_widget.h"
#include "core/network/network_fetcher.h"
#include "utils/utils.h"

namespace ID_FIELDS
{
	constexpr char animal[] = "anim_id";
	constexpr char contract[] = "contr_id";
	constexpr char microchip[] = "chip_id";;
	constexpr char address[] = "addr_id";
	constexpr char passport[] = "pass_id";
}

constexpr char IMG_PROPERTY[] ="image";
const QSize IMG_SIZE(256	, 256);


AnimalEditWidget::AnimalEditWidget(QWidget *parent)
	: QWidget(parent),
	  ui(new Ui::animal_widget()),
	  chip_ui(new Ui::chip_widget()),
	  contract_ui(new Ui::add_constract_widget()),
	  info_dlg_ui(new Ui::TextEditor()),
	  client_dlg_ui(new Ui::client()),
	  address_dlg_ui(new Ui::address_widget()),
	  passport_dlg_ui(new Ui::PassportWidget()),
	  info_dlg(new QDialog(this)),
	  client_dlg(new QDialog(this)),
	  contract(new QWidget(this)),
	  contact(new Contacts(this))
{
	ui->setupUi(this);
	client_dlg_ui->setupUi(client_dlg);

	QLayout* lay = new QHBoxLayout(client_dlg_ui->contact);
	lay->setMargin(0);
	lay->addWidget(contact);
	client_dlg_ui->contact->setLayout(lay);

	address_dlg_ui->setupUi(client_dlg_ui->address);
	passport_dlg_ui->setupUi(client_dlg_ui->passport);

	ui->sex_cb->addItem(GenderRussianType::gender_female, static_cast<uint32_t>(Gender::GenderEnum::Female));
	ui->sex_cb->addItem(GenderRussianType::gender_male, static_cast<uint32_t>(Gender::GenderEnum::Male));
	ui->sex_cb->addItem(GenderRussianType::gender_other, static_cast<uint32_t>(Gender::GenderEnum::Other));

	contract = new QWidget(ui->contract);
	contract_ui->setupUi(contract);

	lay = ui->contract->layout();
	contract->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	lay->addWidget(contract);

	chip = new QWidget(ui->chip);
	chip_ui->setupUi(chip);

	lay = ui->chip->layout();
	chip->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	lay->addWidget(chip);

	info_dlg_ui->setupUi(info_dlg);
	info_dlg->setModal(true);

	connect(ui->Info_client, &QPushButton::released, this, &AnimalEditWidget::activeClientDialog);
	connect(ui->sign_tb, &QToolButton::released, this, &AnimalEditWidget::activeSignDialog);
	connect(ui->info_tb, &QToolButton::released, this, &AnimalEditWidget::activeInfoDialog);
	connect(ui->chose_photo_pb, &QPushButton::released, this, [this]()
	{
		constexpr char msg[] = "Выберите изображение";
		constexpr char filter[] = "*.png *.jpg *.jpeg";
		auto file_path = QFileDialog::getOpenFileName(this, msg, QDir::home().path(), filter);
		if (file_path.isEmpty() == false)
		{
			setProperty(IMG_PROPERTY, file_path);
			ui->photo->setPixmap(QPixmap(file_path).scaled(IMG_SIZE, Qt::KeepAspectRatio));
		}
	});
}

void AnimalEditWidget::show(const QUrl& url, std::chrono::milliseconds tout, const QByteArray& pass)
{
	QNetworkRequest request;
	request.setUrl(url);
	request.setRawHeader("Authorization", QByteArray("Explicit: ").append(pass));

	NetworkFetcher fetcher;
	auto reply = fetcher.httpGet(request, tout);
	const auto& code = std::get<0>(reply);
	const auto& body = std::get<2>(reply);
	if (code != 200)
	{
		qCritical() << Q_FUNC_INFO << "Failed request. Http code:"<< code << body;
		return;
	}

	animal_record.deserialize(fromJson(body));
	setProperty(ID_FIELDS::animal, QVariant::fromValue(animal_record.getAnimId()));
	ui->name_le->setText(animal_record.getName());
	ui->species_le->setText(animal_record.getSpecies());
	ui->breed_le->setText(animal_record.getBreed());
	ui->sex_cb->setCurrentIndex(ui->sex_cb->findData(static_cast<uint32_t>(animal_record.getSex().getGenderType())));
	ui->birth_de->setDate(animal_record.getBirth());
	ui->costrat_cb->setChecked(animal_record.getCastrated());
	ui->color_le->setText(animal_record.getColor());
	ui->sign_le->setText(animal_record.getSpecialSigns());
	ui->info_le->setText(animal_record.getOtherData());
	ui->reg_de->setDate(animal_record.getRegistrDate());
	ui->last_visit_de->setDate(animal_record.getLastVisit());

	const auto& relative_path = animal_record.getRelPathToPhoto();
	auto img = ImageLoader::getInstance().loadPixmap(relative_path, pass);
	ui->photo->setPixmap(img.scaled(IMG_SIZE, Qt::KeepAspectRatio));
	setProperty(IMG_PROPERTY, relative_path);

	const Contract& contract_object = animal_record.getContract();
	setProperty(ID_FIELDS::contract, QVariant::fromValue(contract_object.getContrId()));
	contract_ui->num_le->setText(contract_object.getCode());
	contract_ui->valid_to_de->setDate(contract_object.getValidUntil());
	contract_ui->conclusion_de->setDate(contract_object.getConclusionDate());

	const Microchip& chip_object = animal_record.getChip();
	setProperty(ID_FIELDS::microchip, QVariant::fromValue(chip_object.getId()));
	chip_ui->num_le->setText(chip_object.getChipNum());
	chip_ui->country_le->setText(chip_object.getCountry());
	chip_ui->impl_de->setDate(chip_object.getImplDate());
	chip_ui->location_le->setText(chip_object.getLocation());

	updateClientData();
}

bool AnimalEditWidget::isFills() const
{
	bool is_empty = false;
	QSet<QLineEdit*> ignorable = { ui->info_le, ui->sign_le };
	QList<QLineEdit*> children = findChildren<QLineEdit*>();
	is_empty |= ui->name_le->text().isEmpty();
	is_empty |= ui->breed_le->text().isEmpty();
	is_empty |= ui->color_le->text().isEmpty();
	is_empty |= ui->species_le->text().isEmpty();

	children = contract->findChildren<QLineEdit*>();
	for (auto child : children)
	{
		is_empty |= child->text().isEmpty();
	}

	children = chip->findChildren<QLineEdit*>();
	for (auto child : children)
	{
		is_empty |= child->text().isEmpty();
	}

	is_empty |= property(IMG_PROPERTY).toString().isEmpty();

	return is_empty == false;
}

bool AnimalEditWidget::isEdit() const
{
	return false;
}

AnimalMedicalRecord AnimalEditWidget::getEditedAnimalMedicalRecord()
{
	AnimalMedicalRecord record;
	record.setAnimId(property(ID_FIELDS::animal).toULongLong());
	record.setName(ui->name_le->text());
	record.setSpecies(ui->species_le->text());
	record.setBreed(ui->breed_le->text());
	record.setRelPathToPhoto(property(IMG_PROPERTY).toString());

	Gender sex;
	sex.setGenderType(static_cast<Gender::GenderEnum>(ui->sex_cb->currentData().toUInt()));
	record.setSex(sex);
	record.setBirth(ui->birth_de->date());
	record.setCastrated(ui->costrat_cb->isChecked());
	record.setColor(ui->color_le->text());
	record.setSpecialSigns(ui->sign_le->text());
	record.setOtherData(ui->info_le->text());
	record.setRegistrDate(ui->reg_de->date());
	record.setLastVisit(ui->last_visit_de->date());

	Contract contract_object;
	contract_object.setContrId(property(ID_FIELDS::contract).toULongLong());
	contract_object.setCode(contract_ui->num_le->text());
	contract_object.setValidUntil(contract_ui->valid_to_de->date());
	contract_object.setConclusionDate(contract_ui->conclusion_de->date());
	record.setContract(std::move(contract_object));

	Microchip chip_object;
	chip_object.setId(property(ID_FIELDS::microchip).toULongLong());
	chip_object.setChipNum(chip_ui->num_le->text());
	chip_object.setCountry(chip_ui->country_le->text());
	chip_object.setImplDate(chip_ui->impl_de->date());
	chip_object.setLocation(chip_ui->location_le->text());
	record.setChip(std::move(chip_object));
	return record;
}

const AnimalMedicalRecord &AnimalEditWidget::getAnimalMedicalRecord() const
{
	return animal_record;
}

void AnimalEditWidget::updateClientData()
{
	const Client& client_object = animal_record.getContract().getClient();
	const auto& phones = client_object.getPhones();
	const auto& emails = client_object.getEmails();
	const auto& socials = client_object.getSocial();

	for (const auto& phone : phones)
	{
		contact->addNewPhone(phone);
	}

	for (const auto& email : emails)
	{
		contact->addNewEmail(email);
	}

	for (const auto& social : socials)
	{
		contact->addNewSocialSite(social);
	}

	const Address& address_object = client_object.getAddress();
	setProperty(ID_FIELDS::address, QVariant::fromValue(address_object.getId()));
	address_dlg_ui->city_lineEdit->setText(address_object.getCity());
	address_dlg_ui->flat_lineEdit->setText(address_object.getFlat());
	address_dlg_ui->house_lineEdit->setText(address_object.getHouse());
	address_dlg_ui->street_lineEdit->setText(address_object.getStreet());
	address_dlg_ui->country_lineEdit->setText(address_object.getCountry());

	const Passport& passport_object = client_object.getPassport();
	setProperty(ID_FIELDS::passport, QVariant::fromValue(passport_object.getId()));
	passport_dlg_ui->num_lineEdit->setText(passport_object.getPassportNum());
	passport_dlg_ui->name_lineEdit->setText(passport_object.getName());
	passport_dlg_ui->patr_lineEdit->setText(passport_object.getPatronymic());
	passport_dlg_ui->issue_date->setDate(passport_object.getIssueDate());
	passport_dlg_ui->surname_lineEdit->setText(passport_object.getSurname());
	passport_dlg_ui->nationality_lineEdit->setText(passport_object.getNationality());
	passport_dlg_ui->birth_dateEdit->setDate(passport_object.getBirthday());
	QRadioButton* btn =
			(passport_object.getGender().getGenderType() == Gender::GenderEnum::Male)
			? passport_dlg_ui->male_radioButton
			: passport_dlg_ui->female_radioButton;
	btn->setChecked(true);

	client_dlg_ui->contact->setEnabled(false);
	client_dlg_ui->passport->setEnabled(false);
	client_dlg_ui->address->setEnabled(false);
	client_dlg_ui->buttonBox->setStandardButtons(QDialogButtonBox::Ok);
}

void AnimalEditWidget::setClientData(const Client& client)
{
	animal_record.getContract().setClient(client);
}

void AnimalEditWidget::activeInfoDialog()
{
	info_dlg->show();
	ui->info_le->setText(showInfoDialog(ui->info_le->text()));
}

void AnimalEditWidget::activeSignDialog()
{
	info_dlg->show();
	ui->sign_le->setText(showInfoDialog(ui->sign_le->text()));
}

void AnimalEditWidget::activeClientDialog()
{
	client_dlg->exec();
}

QString AnimalEditWidget::showInfoDialog(const QString & txt)
{
	QString out_text = txt;
	info_dlg_ui->text->setText(txt);
	if (info_dlg->exec() == QDialog::Accepted)
	{
		out_text = info_dlg_ui->text->toPlainText();
	}
	return out_text;
}

void AnimalEditWidget::showContract()
{

}

void AnimalEditWidget::update()
{

}

#include <QNetworkReply>
#include <QTextEdit>
#include <QScrollArea>
#include "ui_animal.h"
#include "ui_text_dialog.h"
#include "ui_add_contract.h"
#include "ui_chip.h"
#include "ui_client.h"
#include "ui_contacts.h"
#include "ui_address.h"
#include "ui_passport.h"
#include "types/json_fields.h"
#include "animal_edit_widget.h"
#include "core/network/network_fetcher.h"
#include "utils/utils.h"

AnimalEditWidget::AnimalEditWidget(QWidget *parent)
	: QWidget(parent),
	  ui(new Ui::animal_widget()),
	  chip_ui(new Ui::chip_widget()),
	  contract_ui(new Ui::add_constract_widget()),
	  info_dlg_ui(new Ui::TextEditor()),
	  client_dlg_ui(new Ui::client()),
	  address_dlg_ui(new Ui::address_widget()),
	  passport_dlg_ui(new Ui::passport_widget()),
	  contact_dlg_ui(new Ui::contacts_widget()),
	  info_dlg(new QDialog(this)),
	  client_dlg(new QDialog(this))
{
	ui->setupUi(this);
	client_dlg_ui->setupUi(client_dlg);
	address_dlg_ui->setupUi(client_dlg_ui->address);
	passport_dlg_ui->setupUi(client_dlg_ui->passport);
	contact_dlg_ui->setupUi(client_dlg_ui->contact);

	ui->sex_cb->addItem(GenderRussianType::gender_female, static_cast<uint32_t>(Gender::GenderEnum::Female));
	ui->sex_cb->addItem(GenderRussianType::gender_male, static_cast<uint32_t>(Gender::GenderEnum::Male));
	ui->sex_cb->addItem(GenderRussianType::gender_other, static_cast<uint32_t>(Gender::GenderEnum::Other));

	contract = new QWidget(ui->contract);
	contract_ui->setupUi(contract);

	QLayout* lay = ui->contract->layout();
	contract->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	lay->addWidget(contract);

	chip = new QWidget(ui->chip);
	chip_ui->setupUi(chip);

	lay = ui->chip->layout();
	chip->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	lay->addWidget(chip);

	info_dlg_ui->setupUi(info_dlg);
	info_dlg->setModal(true);

	connect(ui->Info_client, &QPushButton::released, this, &AnimalEditWidget::active);
	connect(ui->sign_tb, &QToolButton::released, this, &AnimalEditWidget::activeSignDialog);
	connect(ui->info_tb, &QToolButton::released, this, &AnimalEditWidget::activeInfoDialog);
}

void AnimalEditWidget::show(const QUrl& url, const QByteArray& pass)
{
	QNetworkRequest request;
	request.setUrl(url);
	request.setRawHeader("Authorization", QByteArray("Explicit: ").append(pass));

	NetworkFetcher fetcher;
	auto reply = fetcher.httpGet(request, std::chrono::milliseconds(10000));
	const auto& code = std::get<0>(reply);
	const auto& body = std::get<2>(reply);
	if (code != 200)
	{
		qCritical() << Q_FUNC_INFO << "Failed request. Http code:"<< code << body;
		return;
	}

	animal_record.deserialize(fromJson(body));
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

	const Contract& contract_object = animal_record.getContract();
	contract_ui->num_le->setText(contract_object.getCode());
	contract_ui->valid_to_de->setDate(contract_object.getValidUntil());
	contract_ui->conclusion_de->setDate(contract_object.getConclusionDate());

	const Microchip& chip_object = animal_record.getChip();
	chip_ui->num_le->setText(chip_object.getChipNum());
	chip_ui->country_le->setText(chip_object.getCountry());
	chip_ui->impl_de->setDate(chip_object.getImplDate());
	chip_ui->location_le->setText(chip_object.getLocation());
}

bool AnimalEditWidget::isFills() const
{
	bool is_empty = false;
	QList<QLineEdit*> children = findChildren<QLineEdit*>();
	for (auto child : children)
	{
		is_empty |= child->text().isEmpty();
	}

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

	return is_empty == false;
}

bool AnimalEditWidget::isEdit() const
{
	return false;
}

AnimalMedicalRecord AnimalEditWidget::getEditedAnimalRecord()
{
	AnimalMedicalRecord record;
	record.setName(ui->name_le->text());
	record.setSpecies(ui->species_le->text());
	record.setBreed(ui->breed_le->text());

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
	contract_object.setCode(contract_ui->num_le->text());
	contract_object.setValidUntil(contract_ui->valid_to_de->date());
	contract_object.setConclusionDate(contract_ui->conclusion_de->date());
	record.setContract(contract_object);

	Microchip chip_object;
	chip_object.setChipNum(chip_ui->num_le->text());
	chip_object.setCountry(chip_ui->country_le->text());
	chip_object.setImplDate(chip_ui->impl_de->date());
	chip_object.setLocation(chip_ui->location_le->text());
	record.setChip(chip_object);
    return record;
}

const AnimalMedicalRecord &AnimalEditWidget::getAnimalRecord() const
{
    return animal_record;
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

void AnimalEditWidget::active()
{

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

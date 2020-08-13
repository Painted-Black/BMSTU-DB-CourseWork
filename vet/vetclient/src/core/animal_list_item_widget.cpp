#include "types/QJsonHeaders.h"
#include "ui_animal_list_item_widget.h"
#include "animal_list_item_widget.h"
#include "types/json_fields.h"

AnimalListItemWidget::AnimalListItemWidget(QWidget *parent)
    : QWidget(parent), ui(new Ui::Form())
{
    ui->setupUi(this);
}

AnimalListWidget::AnimalListWidget()
    : widget(nullptr)
{

}

bool AnimalListWidget::loadFromJson(const QByteArray& json)
{
    bool cast = true;
    QJsonArray datas = QJsonDocument::fromJson(json).array();
    for (const QJsonValue& data : datas)
    {
        QJsonObject obj = data.toObject();
        AnimalListItemWidget::AnimalData _d;
        _d.uid = obj.value(AnimalMedicalRecordJson::field_anim_id).toVariant().toULongLong(&cast);
        _d.name = obj.value(AnimalMedicalRecordJson::field_anim_name).toString();
        _d.spec = obj.value(AnimalMedicalRecordJson::field_anim_species).toString();
        _d.birth = QDate::fromString(obj.value(AnimalMedicalRecordJson::field_anim_birth).toString(), Qt::ISODate);
    }
}

void AnimalListWidget::view()
{
#pragma message "TODO"
}

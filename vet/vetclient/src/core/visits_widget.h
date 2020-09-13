#pragma once

#include <QWidget>

#include "core/visit_list_item_widget.h"
#include "types/visit.h"

namespace Ui {
class visits_widget;
}

class VisitsWidget : public QWidget
{
	Q_OBJECT

public:
	explicit VisitsWidget(QWidget *parent = nullptr);
	~VisitsWidget();

	void setPassword(const QByteArray &password);
	void show();

private:
	void addItem(const ShortVisitInfo&);
	void selectItemWidget(const QModelIndex &row);
	Visit queryToServer(uint64_t vis_id, bool *is_ok);

private:
	Ui::visits_widget *ui;
	QByteArray mPassword;
	QVector<ShortVisitInfo> mData;
};


#pragma once

#include <QWidget>
#include <QListWidget>

#include "types/short_visit_info.h"

namespace Ui {
class VisitListItemWidget;
}

class VisitListItemWidget : public QWidget
{
	Q_OBJECT

public:
	explicit VisitListItemWidget(QWidget *parent = nullptr);
	~VisitListItemWidget();
	void addVisit(const ShortVisitInfo& visit);
	void addVisitsVec(const QVector<ShortVisitInfo>& vec);

private:
	void addWidget(const ShortVisitInfo& visit);
	Ui::VisitListItemWidget *ui;
	QListWidget* mView;
	QVector<ShortVisitInfo> mData;
};


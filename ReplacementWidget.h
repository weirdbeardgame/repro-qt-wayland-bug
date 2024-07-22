#pragma once

#include <QtWidgets/QWidget>

class ReplacementWidget final : public QWidget
{
	Q_OBJECT

public:
	explicit ReplacementWidget(QWidget *parent);
	~ReplacementWidget();

	QPaintEngine* paintEngine() const override;
};

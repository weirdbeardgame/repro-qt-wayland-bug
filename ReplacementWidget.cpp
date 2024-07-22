#include "ReplacementWidget.h"


ReplacementWidget::ReplacementWidget(QWidget* parent)
	: QWidget(parent)
{
	// We want a native window for both D3D and OpenGL.
	setAutoFillBackground(false);
	setAttribute(Qt::WA_NativeWindow, true);
	setAttribute(Qt::WA_NoSystemBackground, true);
	setAttribute(Qt::WA_PaintOnScreen, true);
	setAttribute(Qt::WA_KeyCompression, false);
	setFocusPolicy(Qt::StrongFocus);
	setMouseTracking(true);
}

ReplacementWidget::~ReplacementWidget()
{
}

QPaintEngine* ReplacementWidget::paintEngine() const
{
	return nullptr;
}


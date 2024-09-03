#include "DisplayWidget.h"

#include <QtCore/QDebug>
#include <QtGui/QGuiApplication>
#include <QtGui/QKeyEvent>
#include <QtGui/QResizeEvent>
#include <QtGui/QScreen>
#include <QtGui/QWindow>
#include <QtGui/QWindowStateChangeEvent>

#include <bit>
#include <cmath>

DisplayWidget::DisplayWidget(QWidget* parent)
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

DisplayWidget::~DisplayWidget()
{
#ifdef _WIN32
	if (m_clip_mouse_enabled)
		ClipCursor(nullptr);
#endif
}

namespace QtUtils
{

qreal GetDevicePixelRatioForWidget(const QWidget* widget)
{
		const QScreen* screen_for_ratio = widget->screen();
		if (!screen_for_ratio)
			screen_for_ratio = QGuiApplication::primaryScreen();

		return screen_for_ratio ? screen_for_ratio->devicePixelRatio() : static_cast<qreal>(1);
}
}

int DisplayWidget::scaledWindowWidth() const
{
	return std::max(static_cast<int>(std::ceil(static_cast<qreal>(width()) * QtUtils::GetDevicePixelRatioForWidget(this))), 1);
}

int DisplayWidget::scaledWindowHeight() const
{
	return std::max(static_cast<int>(std::ceil(static_cast<qreal>(height()) * QtUtils::GetDevicePixelRatioForWidget(this))), 1);
}

QPaintEngine* DisplayWidget::paintEngine() const
{
	return nullptr;
}
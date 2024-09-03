#pragma once
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QWidget>
#include <optional>
#include <vector>

namespace QtUtils
{
    qreal GetDevicePixelRatioForWidget(const QWidget *widget);
}


class DisplayWidget final : public QWidget {

private:
public:
  explicit DisplayWidget(QWidget *parent);
  ~DisplayWidget();

  QPaintEngine *paintEngine() const override;

  int scaledWindowWidth() const;
  int scaledWindowHeight() const;

  void updateRelativeMode(bool enabled);
  void updateCursor(bool hidden);

  void handleCloseEvent(QCloseEvent *event);
  void destroy();

Q_SIGNALS:
  void windowResizedEvent(int width, int height, float scale);
  void windowRestoredEvent();
};
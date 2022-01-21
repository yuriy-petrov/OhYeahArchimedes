#pragma once

#include <QGraphicsView>
#include <QObject>

class GraphicsViewController : public QObject
{
    Q_OBJECT

  public:
    explicit GraphicsViewController( QGraphicsView * view, QObject * parent = nullptr );

    // QObject interface
    bool eventFilter( QObject * watched, QEvent * event ) override;

  private:
    QGraphicsView * _view;
    double _zoomFactor = 1.1;
};

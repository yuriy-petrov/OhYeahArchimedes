#include "GraphicsViewController.h"

#include <QEvent>
#include <QGraphicsSceneWheelEvent>
#include <QMouseEvent>
#include <QWheelEvent>
#include <QtMath>

GraphicsViewController::GraphicsViewController( QGraphicsView * view, QObject * parent )
  : QObject { parent }
  , _view( view )
{
    _view->setMouseTracking( true );
    _view->scene()->installEventFilter( this );
}

bool GraphicsViewController::eventFilter( QObject * watched, QEvent * event )
{
    Q_UNUSED( watched );
    if ( event->type() == QEvent::GraphicsSceneWheel ) {
        auto wheelEvent = static_cast<QGraphicsSceneWheelEvent *>( event );
        if ( wheelEvent->orientation() == Qt::Vertical ) {
            if ( wheelEvent->delta() > 0 ) {
                _view->scale( _zoomFactor, _zoomFactor );
            } else {
                _view->scale( 1.0 / _zoomFactor, 1.0 / _zoomFactor );
            }
            event->accept();
            return true;
        }
    }
    return false;
}

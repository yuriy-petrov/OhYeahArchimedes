#include "SegmentGraphicsItem.h"

#include <QCursor>
#include <QDebug>
#include <QGraphicsScene>
#include <QGraphicsSceneHoverEvent>
#include <QPainter>
#include <QPen>
#include <QToolTip>

SegmentGraphicsItem::SegmentGraphicsItem( Segment * segment )
  : _segment( segment )
{
    setZValue( 100 );
    setFlag( QGraphicsItem::ItemIsMovable );
    setFlag( QGraphicsItem::ItemIsSelectable );
    setFlag( QGraphicsItem::ItemSendsScenePositionChanges );
    setCursor( Qt::PointingHandCursor );
    setAcceptHoverEvents( true );
    QPen pen( Qt::black, 2.0 );
    pen.setCosmetic( true );
    setPen( pen );
    QObject::connect( segment, &Segment::changed, [this]() { setLine( _segment->line() ); } );
    QObject::connect( segment, &Segment::destroyed, [this]() {
        scene()->removeItem( this );
        delete this;
    } );

    setLine( segment->line() );
}

QLineF SegmentGraphicsItem::line() const
{
    return QGraphicsLineItem::line().translated( -pos() );
}

void SegmentGraphicsItem::setLine( const QLineF & line )
{
    QGraphicsLineItem::setLine( line.translated( pos() ) );
}

QVariant SegmentGraphicsItem::itemChange( GraphicsItemChange change, const QVariant & value )
{
    if ( change == QGraphicsItem::ItemPositionHasChanged ) {
        _segment->setLine( line() );
    }
    return QGraphicsLineItem::itemChange( change, value );
}

void SegmentGraphicsItem::hoverEnterEvent( QGraphicsSceneHoverEvent * event )
{
    QToolTip::showText( event->screenPos(),
                        QString( "(%1, %2) (%3, %4)" )
                          .arg( _segment->line().p1().x() )
                          .arg( _segment->line().p1().y() )
                          .arg( _segment->line().p2().x() )
                          .arg( _segment->line().p2().y() ) );
}

void SegmentGraphicsItem::hoverLeaveEvent( QGraphicsSceneHoverEvent * event )
{
    QToolTip::hideText();
}

#include "SegmentGraphicsItem.h"

#include <QCursor>
#include <QDebug>
#include <QGraphicsScene>
#include <QGraphicsSceneHoverEvent>
#include <QPainter>
#include <QPen>
#include <QToolTip>

#include <QLoggingCategory>

namespace {
Q_LOGGING_CATEGORY( LOG, "SegmentGraphicsItem" )
}

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
    QObject::connect( segment, &Segment::changed, [this]() {
        setLine( _segment->line() );
    } );
    QObject::connect( segment, &Segment::selectionChanged, [this]() { setSelected( _segment->isSelected() ); } );
    QObject::connect( segment, &Segment::destroyed, [this]() {
        scene()->removeItem( this );
        delete this;
    } );

    setLine( segment->line() );

    qCDebug( LOG ) << "created" << _segment;
}

SegmentGraphicsItem::~SegmentGraphicsItem()
{
    qCDebug( LOG ) << "destroyed" << _segment;
}

QLineF SegmentGraphicsItem::line() const
{
    auto line = QGraphicsLineItem::line();
    return { mapToScene( line.p1() ), mapToScene( line.p2() ) };
}

void SegmentGraphicsItem::setLine( const QLineF & line )
{
    QGraphicsLineItem::setLine( QLineF( mapFromScene( line.p1() ), mapFromScene( line.p2() ) ) );
}

QPainterPath SegmentGraphicsItem::shape() const
{
    auto pen = this->pen();
    pen.setWidth( 10 );
    return QPainterPathStroker( pen ).createStroke( QGraphicsLineItem::shape() );
}

QVariant SegmentGraphicsItem::itemChange( GraphicsItemChange change, const QVariant & value )
{
    if ( change == QGraphicsItem::ItemPositionHasChanged ) {
        _segment->setLine( line() );
    } else if ( change == QGraphicsItem::ItemSelectedHasChanged ) {
        _segment->setSelected( value.toBool() );
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

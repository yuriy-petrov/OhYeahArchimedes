#pragma once

#include "Segment.h"

#include <QGraphicsLineItem>

class SegmentGraphicsItem : public QGraphicsLineItem
{
  public:
    SegmentGraphicsItem( Segment * segment );
    ~SegmentGraphicsItem();

    QLineF line() const;
    void setLine( const QLineF & line );

    // QGraphicsItem interface
    QPainterPath shape() const override;

  protected:
    // QGraphicsItem interface
    QVariant itemChange( GraphicsItemChange change, const QVariant & value ) override;
    void hoverEnterEvent( QGraphicsSceneHoverEvent * event ) override;
    void hoverLeaveEvent( QGraphicsSceneHoverEvent * event ) override;

  private:
    Segment * _segment;
};

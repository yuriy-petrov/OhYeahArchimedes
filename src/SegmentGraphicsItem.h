#pragma once

#include "Segment.h"

#include <QGraphicsLineItem>

class SegmentGraphicsItem : public QGraphicsLineItem
{
  public:
    SegmentGraphicsItem( Segment * segment );

    QLineF line() const;
    void setLine( const QLineF & line );

  protected:
    // QGraphicsItem interface
    QVariant itemChange( GraphicsItemChange change, const QVariant & value ) override;

  private:
    Segment * _segment;
};

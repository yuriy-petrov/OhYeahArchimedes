#include "Segment.h"

Segment::Segment( const QLineF & line )
  : _line( line )
{
}

const QLineF & Segment::line() const
{
    return _line;
}

void Segment::setLine( const QLineF & newLine )
{
    _line = newLine;
    emit changed();
}

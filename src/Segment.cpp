#include "Segment.h"

#include <QLoggingCategory>

namespace {
Q_LOGGING_CATEGORY( LOG, "Segment" )
}

Segment::Segment( const QLineF & line )
  : _line( line )
{
    qCDebug( LOG ) << "created" << this;
}

Segment::~Segment()
{
    qCDebug( LOG ) << "destroyed" << this;
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

bool Segment::isSelected() const
{
    return _isSelected;
}

void Segment::setSelected( bool value )
{
    if ( _isSelected != value ) {
        qCDebug( LOG ) << ( value ? "selected" : "deselected" ) << this;
        _isSelected = value;
        emit selectionChanged();
    }
}

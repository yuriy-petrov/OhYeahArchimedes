#pragma once

#include <Segment.h>

#include <QLineF>
#include <QList>
#include <QObject>

class SegmentsController : public QObject
{
    Q_OBJECT

  public:
    SegmentsController( QObject * parent = nullptr );

    void loadFromCsv( const QString & fileName );
    void saveToCsv( const QString & fileName );

    Segment * append( const QLineF & line = {} );
    void remove( uint index );

    const std::vector<Segment::Ptr> & segments() const;

  signals:
    void loaded();
    void changed( uint index );

  private:
    std::vector<Segment::Ptr> _segments;
};


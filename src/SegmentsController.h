#pragma once

#include "Segment.h"
#include "SegmentsModel.h"

#include <QGraphicsScene>
#include <QLineF>
#include <QList>
#include <QObject>

class SegmentsController : public QObject
{
    Q_OBJECT

  public:
    SegmentsController( QGraphicsScene * scene, SegmentsModel * model, QObject * parent = nullptr );

    void loadFromCsv( const QString & fileName );
    void saveToCsv( const QString & fileName );

    Segment * append( const QLineF & line = {} );
    void remove( uint index );

    const std::vector<Segment::Ptr> & segments() const;

  signals:
    void changed( uint index );

  private:
    QGraphicsScene * _scene;
    SegmentsModel * _model;
    std::vector<Segment::Ptr> _segments;
};


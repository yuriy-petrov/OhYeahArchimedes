#pragma once

#include "Segment.h"
#include "SegmentsModel.h"

#include <QGraphicsScene>
#include <QLineF>
#include <QList>
#include <QTableView>

class SegmentsController
{
  public:
    SegmentsController( QGraphicsScene * scene, QTableView * tableView, SegmentsModel * model );

    void loadFromCsv( const QString & fileName );
    void saveToCsv( const QString & fileName );

    Segment * append( const QLineF & line = {} );
    void remove( uint index );
    const std::vector<Segment::Ptr> & segments() const;

    void select( int index );
    void clearSelection();

  signals:
    void changed( uint index );

  private:
    QGraphicsScene * _scene;
    QTableView * _view;
    SegmentsModel * _model;
    std::vector<Segment::Ptr> _segments;
};

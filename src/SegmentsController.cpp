#include "SegmentsController.h"
#include "SegmentGraphicsItem.h"

#include <QFile>
#include <QLoggingCategory>

namespace {
Q_LOGGING_CATEGORY( LOG, "SegmentsController" )
}

SegmentsController::SegmentsController( QGraphicsScene * scene, SegmentsModel * model, QObject * parent )
  : QObject( parent )
  , _scene( scene )
  , _model( model )
{   
}

void SegmentsController::loadFromCsv( const QString & fileName )
{
    _model->clear();

    QFile file( fileName );
    if ( file.open( QIODevice::ReadOnly ) ) {
        int lineNum = 0;
        while ( !file.atEnd() ) {
            lineNum++;
            auto line          = file.readLine();
            QStringList values = QString( line ).split( ',' );
            if ( values.size() == 4 ) {
                bool isOk[4];
                QLineF line( values.at( 0 ).toDouble( &isOk[0] ),
                             values.at( 1 ).toDouble( &isOk[1] ),
                             values.at( 2 ).toDouble( &isOk[2] ),
                             values.at( 3 ).toDouble( &isOk[3] ) );
                if ( isOk[0] && isOk[1] && isOk[2] && isOk[3] ) {
                    append( line );
                } else {
                    qCCritical( LOG ) << "Invalid double value! Line" << lineNum << ":" << line;
                }
            } else {
                qCCritical( LOG ) << "Invalid csv segments format: should be 4 columns! Line" << lineNum << ":" << line;
            }
        }
    } else {
        qCCritical( LOG ).noquote() << file.errorString() << ":" << file.fileName();
    }
}

void SegmentsController::saveToCsv( const QString & fileName )
{
    QFile file( fileName );
    if ( file.open( QIODevice::WriteOnly ) ) {
        QTextStream stream( &file );
        for ( auto const & segment : _segments ) {
            stream << segment.get()->line().x1() << ',' << segment.get()->line().y1() << ','
                   << segment.get()->line().x2() << ',' << segment.get()->line().y2() << '\n';
        }
    } else {
        qCCritical( LOG ).noquote() << file.errorString() << ":" << file.fileName();
    }
}

Segment * SegmentsController::append( const QLineF & line )
{
    auto segment = std::make_unique<Segment>( line );
    _segments.push_back( std::move( segment ) );
    auto ptr = _segments.back().get();

    connect( ptr, &Segment::changed, this, [this, ptr]() {
        auto it = std::find_if(
          _segments.cbegin(), _segments.cend(), [ptr]( const auto & segment ) { return segment.get() == ptr; } );
        if ( it != _segments.cend() ) {
            emit changed( std::distance( _segments.cbegin(), it ) );
        }
    } );

    _scene->addItem( new SegmentGraphicsItem( ptr ) );

    _model->insertRows( _model->rowCount(), 1 );
    _model->setData(
      _model->index( _model->rowCount() - 1, 0 ), QVariant::fromValue( ptr ), SegmentsModel::SegmentRole );

    return ptr;
}

void SegmentsController::remove( uint index )
{
    _model->removeRows( index, 1 );

    if ( index < _segments.size() ) {
        _segments.erase( _segments.begin() + index );
    }
}

const std::vector<Segment::Ptr> & SegmentsController::segments() const
{
    return _segments;
}

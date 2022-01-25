#include "SegmentsModel.h"
#include "SegmentsController.h"

SegmentsModel::SegmentsModel( QObject * parent )
  : QAbstractTableModel( parent )
{}

void SegmentsModel::clear()
{
    beginResetModel();
    _segments.clear();
    endResetModel();
}

QVariant SegmentsModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if ( orientation == Qt::Horizontal ) {
        if ( role == Qt::DisplayRole ) {
            switch ( static_cast<Column>( section ) ) {
                case Column::X1:
                    return "x1";
                case Column::X2:
                    return "x2";
                case Column::Y1:
                    return "y1";
                case Column::Y2:
                    return "y2";
            }
        }
    }
    return QAbstractTableModel::headerData( section, orientation, role );
}

int SegmentsModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED( parent );
    return _segments.size();
}

int SegmentsModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED( parent );
    return 4;
}

QVariant SegmentsModel::data(const QModelIndex &index, int role) const
{
    auto segment = _segments.at( index.row() );

    if ( segment ) {
        if ( role == Qt::DisplayRole || role == Qt::EditRole ) {
            switch ( static_cast<Column>( index.column() ) ) {
                case Column::X1:
                    return segment->line().x1();
                case Column::X2:
                    return segment->line().x2();
                case Column::Y1:
                    return segment->line().y1();
                case Column::Y2:
                    return segment->line().y2();
            }
        }
    }

    return QVariant();
}

bool SegmentsModel::setData( const QModelIndex & index, const QVariant & value, int role )
{
    Q_UNUSED( role );
    auto segment = _segments.at( index.row() );

    if ( role == Role::SegmentRole ) {
        auto segment           = value.value<Segment *>();
        _segments[index.row()] = segment;
        connect( segment, &Segment::changed, this, [segment, this]() {
            auto row = _segments.indexOf( segment );
            emit dataChanged( this->index( row, 0 ), this->index( row, columnCount() - 1 ) );
        } );
    } else {
        if ( segment ) {
            auto p1 = segment->line().p1();
            auto p2 = segment->line().p2();

            switch ( static_cast<Column>( index.column() ) ) {
                case Column::X1:
                    p1.setX( value.toDouble() );
                    break;
                case Column::X2:
                    p2.setX( value.toDouble() );
                    break;
                case Column::Y1:
                    p1.setY( value.toDouble() );
                    break;
                case Column::Y2:
                    p2.setY( value.toDouble() );
                    break;
            }

            segment->setLine( QLineF( p1, p2 ) );
        }
    }
    return true;
}

Qt::ItemFlags SegmentsModel::flags( const QModelIndex & index ) const
{
    return QAbstractTableModel::flags( index ) | Qt::ItemIsEditable;
}

bool SegmentsModel::insertRows( int row, int count, const QModelIndex & parent )
{
    Q_UNUSED( parent );
    beginInsertRows( QModelIndex(), row, row + count - 1 );
    while ( count-- > 0 ) {
        _segments.insert( row++, nullptr );
    }
    endInsertRows();
    return true;
}

bool SegmentsModel::removeRows( int row, int count, const QModelIndex & parent )
{
    Q_UNUSED( parent );
    beginRemoveRows( QModelIndex(), row, row + count - 1 );
    while ( count-- > 0 ) {
        _segments.removeAt( row );
    }
    endRemoveRows();
    return true;
}

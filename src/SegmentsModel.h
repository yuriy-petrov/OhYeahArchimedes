#pragma once

#include <QAbstractTableModel>

class Segment;

class SegmentsModel : public QAbstractTableModel
{
    Q_OBJECT

  public:
    enum class Column
    {
        X1,
        Y1,
        X2,
        Y2
    };

    enum Role
    {
        SegmentRole = Qt::UserRole
    };

    explicit SegmentsModel( QObject * parent = nullptr );

    void clear();

    // Header:
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

       // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data( const QModelIndex & index, int role = Qt::DisplayRole ) const override;
    bool setData( const QModelIndex & index, const QVariant & value, int role ) override;

    Qt::ItemFlags flags( const QModelIndex & index = QModelIndex() ) const override;

    bool insertRows( int row, int count, const QModelIndex & parent = QModelIndex() ) override;
    bool removeRows( int row, int count, const QModelIndex & parent = QModelIndex() ) override;

  private:
    QList<Segment *> _segments;
};

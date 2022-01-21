#pragma once

#include <QAbstractTableModel>

class SegmentsController;

class SegmentsModel : public QAbstractTableModel
{
    Q_OBJECT

    enum class Column
    {
        X1,
        Y1,
        X2,
        Y2
    };

  public:
    explicit SegmentsModel( SegmentsController * segmentsController, QObject * parent = nullptr );

    void appendSegment();
    void removeSegment( const QModelIndex & index );

    // Header:
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

       // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data( const QModelIndex & index, int role = Qt::DisplayRole ) const override;
    bool setData( const QModelIndex & index, const QVariant & value, int role ) override;

    Qt::ItemFlags flags( const QModelIndex & index = QModelIndex() ) const override;

  private:
    SegmentsController * _segmentsController;
};

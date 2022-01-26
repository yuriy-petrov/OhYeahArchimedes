#pragma once

#include <QLineF>
#include <QObject>
#include <memory>

class Segment : public QObject
{
    Q_OBJECT

  public:
    using Ptr = std::unique_ptr<Segment>;

    Segment( const QLineF & line );
    ~Segment();

    const QLineF & line() const;
    void setLine( const QLineF & newLine );

    bool isSelected() const;
    void setSelected( bool value );

  signals:
    void changed();
    void selectionChanged();

  private:
    QLineF _line;
    bool _isSelected = false;
};


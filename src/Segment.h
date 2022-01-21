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

    const QLineF & line() const;
    void setLine( const QLineF & newLine );

  signals:
    void changed();

  private:
    QLineF _line;
};


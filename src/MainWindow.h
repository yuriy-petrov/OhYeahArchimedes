#pragma once

#include "GraphicsViewController.h"

#include <QGraphicsScene>
#include <QMainWindow>

QT_BEGIN_NAMESPACE
  namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

  public:
    MainWindow( QWidget * parent = nullptr );
    ~MainWindow();

  private slots:
    void on_actionOpen_image_triggered();

  private:
    void restoreState();
    void saveState() const;

    void loadImage();

    Ui::MainWindow * ui;
    GraphicsViewController * _graphicsViewController;
    QString _imageDir;
    QString _imageFilename;
    QGraphicsScene _scene;
    QGraphicsPixmapItem * _imageItem = nullptr;
};

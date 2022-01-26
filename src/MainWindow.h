#pragma once

#include "GraphicsViewController.h"
#include "SegmentsController.h"
#include "SegmentsModel.h"

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
    void on_actionAppend_segment_triggered();
    void on_actionRemove_segment_triggered();
    void on_actionSave_segments_triggered();
    void on_actionOpen_segments_triggered();

  private:
    void restoreState();
    void saveState() const;

    void loadImage();
    void loadSegments();

    Ui::MainWindow * ui;
    GraphicsViewController * _graphicsViewController;
    QString _imageDir;
    QString _imageFilename = "://resources/archimedes.jpg";
    QString _segmentsDir;
    QString _segmentsFileName = ":/resources/segments.csv";
    QGraphicsScene _scene;
    QGraphicsPixmapItem * _imageItem = nullptr;
    SegmentsModel _segmentsModel;
    std::unique_ptr<SegmentsController> _segmentsController;
};

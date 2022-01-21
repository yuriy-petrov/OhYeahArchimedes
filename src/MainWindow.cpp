#include "MainWindow.h"
#include "ui_MainWindow.h"

#include <QEvent>
#include <QFileDialog>
#include <QGraphicsPixmapItem>
#include <QScrollBar>
#include <QSettings>

namespace {
auto const ParamGeometry    = "geometry";
auto const ParamSplitter    = "splitter";
auto const ParamImageDir    = "image_dir";
auto const ParamImage       = "image";
auto const ParamSegmentsDir = "segments_dir";
auto const ParamSegments    = "segments";
} // namespace

MainWindow::MainWindow( QWidget * parent )
  : QMainWindow( parent )
  , ui( new Ui::MainWindow )
  , _imageDir( qApp->applicationDirPath() )
  , _segmentsDir( qApp->applicationDirPath() )
  , _segmentsModel( &_segmentsController )
{
    ui->setupUi(this);
    ui->graphicsView->setScene( &_scene );
    ui->tableView->setModel( &_segmentsModel );

    ui->tableView->horizontalHeader()->setSectionResizeMode( QHeaderView::Stretch );

    _graphicsViewController = new GraphicsViewController( ui->graphicsView, this );

    restoreState();

    loadImage();
    loadSegments();

    ui->actionRemove_segment->setEnabled( false );
    connect( ui->tableView->selectionModel(), &QItemSelectionModel::selectionChanged, this, [this]() {
        ui->actionRemove_segment->setEnabled( ui->tableView->selectionModel()->hasSelection() );
    } );
}

MainWindow::~MainWindow()
{
    saveState();
    delete ui;
}

void MainWindow::on_actionOpen_image_triggered()
{
    auto fileName = QFileDialog::getOpenFileName( this, "Select image", _imageDir, "Images (*.jpg;*.png)" );
    if ( !fileName.isNull() ) {
        _imageFilename = fileName;
        _imageDir      = QFileInfo( _imageFilename ).absolutePath();
        loadImage();
    }
}

void MainWindow::on_actionAppend_segment_triggered()
{
    _segmentsModel.appendSegment();
}

void MainWindow::on_actionRemove_segment_triggered()
{
    _segmentsModel.removeSegment( ui->tableView->selectionModel()->selectedRows().first() );
}

void MainWindow::on_actionSave_segments_triggered()
{
    auto fileName = QFileDialog::getSaveFileName( this, "Save segments", _segmentsFileName, "CSV files (*.csv)" );
    if ( !fileName.isEmpty() ) {
        _segmentsController.saveToCsv( fileName );
    }
}

void MainWindow::on_actionOpen_segments_triggered()
{
    auto fileName = QFileDialog::getOpenFileName( this, "Select segments", _segmentsDir, "*.csv" );
    if ( !fileName.isNull() ) {
        _segmentsFileName = fileName;
        _segmentsDir      = QFileInfo( _segmentsFileName ).absolutePath();
        loadSegments();
    }
}

void MainWindow::restoreState()
{
    QSettings s;
    restoreGeometry( s.value( ParamGeometry, saveGeometry() ).toByteArray() );
    ui->splitter->restoreState( s.value( ParamSplitter, ui->splitter->saveState() ).toByteArray() );
    _imageDir      = s.value( ParamImageDir, _imageDir ).toString();
    _imageFilename = s.value( ParamImage, _imageFilename ).toString();
    _segmentsDir   = s.value( ParamSegmentsDir, _segmentsDir ).toString();
    //    _segmentsFileName = s.value( ParamSegments, _segmentsFileName ).toString();
}

void MainWindow::saveState() const
{
    QSettings s;
    s.setValue( ParamGeometry, saveGeometry() );
    s.setValue( ParamSplitter, ui->splitter->saveState() );
    s.setValue( ParamImageDir, _imageDir );
    s.setValue( ParamImage, _imageFilename );
    s.setValue( ParamSegmentsDir, _segmentsDir );
    s.setValue( ParamSegments, _segmentsFileName );
}

void MainWindow::loadImage()
{
    if ( _imageItem ) {
        _scene.removeItem( _imageItem );
        delete _imageItem;
        _imageItem = nullptr;
    }
    _imageItem = _scene.addPixmap( QPixmap( _imageFilename ) );
}

void MainWindow::loadSegments()
{
    _segmentsController.loadFromCsv( _segmentsFileName );
}

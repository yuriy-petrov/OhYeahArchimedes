#include "MainWindow.h"
#include "ui_MainWindow.h"

#include <QEvent>
#include <QFileDialog>
#include <QGraphicsPixmapItem>
#include <QScrollBar>
#include <QSettings>

namespace {
auto const ParamGeometry = "geometry";
auto const ParamImageDir = "image_dir";
auto const ParamImage    = "image";
} // namespace

MainWindow::MainWindow( QWidget * parent )
  : QMainWindow( parent )
  , ui( new Ui::MainWindow )
  , _imageDir( qApp->applicationDirPath() )
{
    ui->setupUi(this);
    ui->graphicsView->setScene( &_scene );

    _graphicsViewController = new GraphicsViewController( ui->graphicsView, this );

    restoreState();

    loadImage();
}

MainWindow::~MainWindow()
{
    saveState();
    delete ui;
}

void MainWindow::on_actionOpen_image_triggered()
{
    auto fileName = QFileDialog::getOpenFileName( this, "Select image", _imageDir, "*.jpg;*.png" );
    if ( !fileName.isNull() ) {
        _imageFilename = fileName;
        _imageDir      = QFileInfo( _imageFilename ).absolutePath();
        loadImage();
    }
}

void MainWindow::restoreState()
{
    QSettings s;
    restoreGeometry( s.value( ParamGeometry, saveGeometry() ).toByteArray() );
    _imageDir      = s.value( ParamImageDir, _imageDir ).toString();
    _imageFilename = s.value( ParamImage, _imageFilename ).toString();
}

void MainWindow::saveState() const
{
    QSettings s;
    s.setValue( ParamGeometry, saveGeometry() );
    s.setValue( ParamImageDir, _imageDir );
    s.setValue( ParamImage, _imageFilename );
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

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFile>
#include <QFileDialog>
#include <QMessageBox>
#include <QTextStream>
#include <QLabel>
#include <QStatusBar>
#include <QShortcut>
#include <QDebug>
#include <QColorDialog>
#include <QtMath>
#include <findandreplace.h>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget* parent = nullptr);
  ~MainWindow();

 private slots:
  void newFile();
  void saveFile();
  void saveFileAs();
  void openFile();
  void selectNone();
  void findAndReplace();
  void zoomIn();
  void zoomOut();
  void toolbarTop();
  void toolbarBottom();
  void toolbarLeft();
  void toolbarRight();


  void on_actionMovable_toolbar_toggled(bool arg1);
  void on_actionFloatable_toolbar_toggled(bool arg1);
  void on_plainTextEdit_textChanged();

 private:
  Ui::MainWindow* ui;

  QString m_fileName;
  bool m_saved;
  int m_zoomOutCounter;
  int m_zoomInCounter;

  void init();
  void setupStatusbar();
  void updateStatus(QString message);
  void createSignalSlots();
  void setPlainTextToCentralWidget();
  void createShortCut();
};
#endif // MAINWINDOW_H

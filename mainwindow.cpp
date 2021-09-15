#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget* parent)
  : QMainWindow(parent)
  , ui(new Ui::MainWindow)
{
  ui->setupUi(this);

  // conncet signal to slots
  createSignalSlots();

  // make shortcut
  createShortCut();

  // set up status bar
  setupStatusbar();
  // set to plain text to central widget
  setPlainTextToCentralWidget();

  // make new file
  newFile();
  m_saved = true;
}

MainWindow::~MainWindow()
{
  delete ui;
}

void MainWindow::newFile()
{
  ui->plainTextEdit->clear();
  m_fileName.clear();
  m_saved = false;
  updateStatus("New File");
}

void MainWindow::saveFile()
{
  if (m_fileName.isEmpty())
  {
    saveFileAs();
    return;
  }

  QFile file(m_fileName);
  qInfo() << m_fileName;
  qInfo() << file.errorString();

  if (!file.open(QIODevice::WriteOnly))
  {
    QMessageBox::critical(this, "Error", file.errorString());
    return;
  }

  QTextStream txtStream(&file);
  txtStream << ui->plainTextEdit->toPlainText();
  file.close();

  m_saved = true;
  updateStatus(m_fileName);
}

void MainWindow::saveFileAs()
{
  QString temp = QFileDialog::getSaveFileName(this, "Save File", QString(),
                                              "Text Files (*txt);;All Files (*,*)");

  if (temp.isEmpty()) return;

  m_fileName = temp;
  saveFile();
}

void MainWindow::openFile()
{
  QString temp = QFileDialog::getOpenFileName(this, "Open File", QString(),
                                              "Text Files (*txt);;All Files (*,*)");

  if (temp.isEmpty()) return;

  m_fileName = temp;
  qInfo() << m_fileName;
  QFile file(m_fileName);

  qInfo() << file.errorString();

  if (!file.open(QIODevice::ReadOnly))
  {
    newFile();
    QMessageBox::critical(this, "Error", file.errorString());
    return;
  }

  QTextStream txtStream(&file);
  ui->plainTextEdit->setPlainText(txtStream.readAll());
  file.close();

  m_saved = true;
  updateStatus(m_fileName);
}

void MainWindow::selectNone()
{
  QTextCursor cursor = ui->plainTextEdit->textCursor();
  int pos = cursor.position();
  cursor.clearSelection();
  cursor.setPosition(pos, QTextCursor::MoveMode::KeepAnchor);
  ui->plainTextEdit->setTextCursor(cursor);
}

void MainWindow::toolbarTop()
{
  addToolBar(Qt::ToolBarArea::TopToolBarArea, ui->toolBar);
}

void MainWindow::toolbarBottom()
{
  addToolBar(Qt::ToolBarArea::BottomToolBarArea, ui->toolBar);
}

void MainWindow::toolbarLeft()
{
  addToolBar(Qt::ToolBarArea::LeftToolBarArea, ui->toolBar);
}

void MainWindow::toolbarRight()
{
  addToolBar(Qt::ToolBarArea::RightToolBarArea, ui->toolBar);
}



void MainWindow::on_actionMovable_toolbar_toggled(bool arg1)
{
  ui->toolBar->setFloatable(arg1);
}


void MainWindow::on_actionFloatable_toolbar_toggled(bool arg1)
{
  ui->toolBar->setMovable(arg1);
}

void MainWindow::setupStatusbar()
{
  QLabel* lblIcon = new QLabel(this);
  lblIcon->setPixmap(QPixmap(":/files/images/new.png"));
  lblIcon->setObjectName("lblIcon");
  ui->statusbar->addWidget(lblIcon);

  QLabel* lblStatus = new QLabel(this);
  lblStatus->setText("Not Saved:");
  lblStatus->setObjectName("lblStatus");
  ui->statusbar->addWidget(lblStatus);

  QLabel* lblFile = new QLabel(this);
  lblFile->setText("New");
  lblFile->setObjectName("lblFile");
  ui->statusbar->addWidget(lblFile);
}

void MainWindow::updateStatus(QString message)
{
  qDebug() << " ***********************";
  QList<QLabel*> lableList;

  foreach (QObject* obj, ui->statusbar->children())
  {
    qDebug() << obj->objectName();

    if (obj->objectName().contains("lblIcon"))
      lableList.push_back(qobject_cast<QLabel*>(obj));

    if (obj->objectName().contains("lblStatus"))
      lableList.push_back(qobject_cast<QLabel*>(obj));

    if (obj->objectName().contains("lblFile"))
      lableList.push_back(qobject_cast<QLabel*>(obj));
  }

  QLabel* lblIcon = lableList[0];
  QLabel* lblStatus = lableList[1];
  QLabel* lblFile = lableList[2] ;

  if (m_saved)
  {

    lblIcon->setPixmap(QPixmap(":/files/images/save.png"));
    lblStatus->setText("Saved:");
  }
  else
  {
    lblIcon->setPixmap(QPixmap(":/files/images/new.png"));
    lblStatus->setText("Not Saved:");
  }


  lblFile->setText(!m_fileName.isEmpty() ? m_fileName : message);

}

void MainWindow::createSignalSlots()
{
  connect(ui->actionNew, &QAction::triggered, this, &MainWindow::newFile);
  connect(ui->actionOpen, &QAction::triggered, this, &MainWindow::openFile);
  connect(ui->actionSave, &QAction::triggered, this, &MainWindow::saveFile);
  connect(ui->actionSave_as, &QAction::triggered, this, &MainWindow::saveFileAs);
  connect(ui->actionExit, &QAction::triggered, this, &MainWindow::close);
  connect(ui->actionCopy, &QAction::triggered, ui->plainTextEdit, &QPlainTextEdit::copy);
  connect(ui->actionCut, &QAction::triggered, ui->plainTextEdit, &QPlainTextEdit::cut);
  connect(ui->actionPaste, &QAction::triggered, ui->plainTextEdit, &QPlainTextEdit::paste);
  connect(ui->actionSelect_All, &QAction::triggered, ui->plainTextEdit, &QPlainTextEdit::selectAll);
  connect(ui->actionSelect_None, &QAction::triggered, this, &MainWindow::selectNone);
  connect(ui->actionToolbar_top, &QAction::triggered, this, &MainWindow::toolbarTop);
  connect(ui->actionToolbar_bottom, &QAction::triggered, this, &MainWindow::toolbarBottom);
  connect(ui->actionToolbar_left, &QAction::triggered, this, &MainWindow::toolbarLeft);
  connect(ui->actionToolbar_right, &QAction::triggered, this, &MainWindow::toolbarRight);
}

void MainWindow::setPlainTextToCentralWidget()
{
  this->setCentralWidget(ui->plainTextEdit);
}

void MainWindow::createShortCut()
{
  // shortcut for copy
  ui->actionCopy->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_C));
  // shortcut for paste
  ui->actionPaste->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_V));
  // shortcut for cut
  ui->actionCut->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_X));
}



void MainWindow::on_plainTextEdit_textChanged()
{
  m_saved = false;

  if (m_fileName.isEmpty())
  {
    updateStatus("New File");
  }
  else
  {
    updateStatus(m_fileName);
  }
}

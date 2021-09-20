#include "findandreplace.h"
#include "ui_findandreplace.h"

FindAndReplace::FindAndReplace(QWidget* parent) :
  QDialog(parent),
  ui(new Ui::FindAndReplace)
{
  ui->setupUi(this);
  init();
  save();
}

FindAndReplace::~FindAndReplace()
{
  delete ui;
}

void FindAndReplace::init()
{
  QPushButton* btnReplace = new QPushButton("Replace", this);
  QPushButton* btnReplaceAll = new QPushButton("Replace All", this);

  ui->buttonBox->addButton(btnReplace, QDialogButtonBox::ActionRole);
  ui->buttonBox->addButton(btnReplaceAll, QDialogButtonBox::ActionRole);

  connect(btnReplace, &QPushButton::clicked, this, &FindAndReplace::replace);
  connect(btnReplaceAll, &QPushButton::clicked, this, &FindAndReplace::replaceAllMatched);
}

void FindAndReplace::save()
{
  m_TextToFind = ui->txtToFind->text();
  m_TextToReplace = ui->txtToReplace->text();
  m_replaceAll = false;
}

bool FindAndReplace::replaceAll() const
{
  return m_replaceAll;
}

const QString& FindAndReplace::TextToFind() const
{
  return m_TextToFind;
}

const QString& FindAndReplace::TextToReplace() const
{
  return m_TextToReplace;
}

void FindAndReplace::replace()
{
  save();
  accept();
}

void FindAndReplace::replaceAllMatched()
{
  save();
  m_replaceAll = true;
  accept();
}


void FindAndReplace::on_ButtonBox_rejected()
{
  reject();
}


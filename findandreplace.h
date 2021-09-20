#ifndef FINDANDREPLACE_H
#define FINDANDREPLACE_H

#include <QDialog>
#include <QPushButton>

namespace Ui {
class FindAndReplace;
}

class FindAndReplace : public QDialog {
  Q_OBJECT

 public:
  explicit FindAndReplace(QWidget* parent = nullptr);
  ~FindAndReplace();

  bool replaceAll() const;
  const QString& TextToFind() const;
  const QString& TextToReplace() const;

 private slots:
  void replace();
  void replaceAllMatched();
  void on_ButtonBox_rejected();

 private:
  Ui::FindAndReplace* ui;
  bool m_replaceAll;
  QString m_TextToFind;
  QString m_TextToReplace;

  void init();
  void save();
};

#endif // FINDANDREPLACE_H

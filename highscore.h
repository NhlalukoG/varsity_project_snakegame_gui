#ifndef HIGHSCORE_H
#define HIGHSCORE_H

#include <QDialog>

namespace Ui {
class HighScore;
}

class HighScore : public QDialog
{
    Q_OBJECT

public:
    explicit HighScore(QWidget *parent = 0);
    ~HighScore();

private slots:
    void on_pushButton_clicked();

private:
    Ui::HighScore *ui;
};

#endif // HIGHSCORE_H

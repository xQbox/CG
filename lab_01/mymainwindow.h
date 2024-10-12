#ifndef MYMAINWINDOW_H
#define MYMAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QRadioButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QMenuBar>
#include <QMessageBox>
#include <QAction>
#include <QCheckBox>
#include <QCoreApplication>
#include <QLineEdit>
#include <QRegularExpression>
#include <QRegularExpressionValidator>

#include "myscene.h"

class MyMainWindow : public QMainWindow
{
    Q_OBJECT
    MyScene *scene;
    QLineEdit *lineMoveEdit;
    QLineEdit *lineRotateClockwiseEdit;
public:
    explicit MyMainWindow(QWidget *parent = nullptr, MyScene *scene_ = nullptr);

private slots:


    void moveObject();
    void rotateClockwise();
    void rotateCounterClockwise();
    void resetToDefault();
    void uploadSave();
    void toggleGrid(bool checked);
    void toggleAxis(bool checked);
    void toggleOrigin(bool checked);
    void toggleEmulate(bool checked);

    void showHelp();
    void showImplementer();
    void closeEvent(QCloseEvent *event) override;
signals:

};

#endif // MYMAINWINDOW_H

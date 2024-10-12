#include "mymainwindow.h"
#include <QDebug>

MyMainWindow::MyMainWindow(QWidget *parent, MyScene *scene_) : QMainWindow(parent), scene(scene_)
{
            scene->show();
           // Создаем виджет центрального окна
           QWidget *centralWidget = new QWidget(this);

           QHBoxLayout *mainLayout = new QHBoxLayout();

           QVBoxLayout *buttonLayout = new QVBoxLayout();

           QPushButton *moveButton = new QPushButton("Переместить");
           QPushButton *rotateClockwiseButton = new QPushButton("Повернуть по часовой");
           QPushButton *rotateCounterClockwiseButton = new QPushButton("Повернуть против часовой");
           QPushButton *resetButton = new QPushButton("Вернуть в исходное состояние");
           QPushButton *backButton = new QPushButton("Назад");
           lineMoveEdit = new QLineEdit(this);
           lineRotateClockwiseEdit =  new QLineEdit(this);

           // Устанавливаем начальный текст lineEdit
           lineMoveEdit->setPlaceholderText("Введите (x,y)");

           lineRotateClockwiseEdit->setPlaceholderText("Введите угол (в градусах)");
           // Создаем регулярное выражение для ввода чисел и запятой
           // \\s* \\s* добавить для разрешения пробелов
           QRegularExpression regExp("^[-+]?\\d*\\.?\\d+,[-+]?\\d*\\.?\\d+$");
           QRegularExpressionValidator *validator = new QRegularExpressionValidator(regExp, lineMoveEdit);

           QRegularExpression regSecExp("^-?\\d+$");  // Разрешает только целые числа (отрицательные или положительные)
           QRegularExpressionValidator *validatorSecond = new QRegularExpressionValidator(regSecExp, lineRotateClockwiseEdit);
           lineRotateClockwiseEdit->setValidator(validatorSecond);
           // Устанавливаем валидатор на поле ввода
           lineMoveEdit->setValidator(validator);

           buttonLayout->addWidget(lineMoveEdit);
           buttonLayout->addWidget(moveButton);
           buttonLayout->addWidget(lineRotateClockwiseEdit);
           buttonLayout->addWidget(rotateClockwiseButton);
           buttonLayout->addWidget(rotateCounterClockwiseButton);
           buttonLayout->addWidget(resetButton);
           buttonLayout->addWidget(backButton);

           QVBoxLayout *radioButtonLayout = new QVBoxLayout();

           QCheckBox *showGridRadio = new QCheckBox("Отобразить сетку");
           QCheckBox *showCoordinatesRadio = new QCheckBox("Отобразить координаты");
           QCheckBox *showStartScene = new QCheckBox("Отобразить начало координат");
           QCheckBox *showEmulate = new QCheckBox("Эмулировать отдаление камеры над сценой");

           radioButtonLayout->addWidget(showGridRadio);
           radioButtonLayout->addWidget(showCoordinatesRadio);
           radioButtonLayout->addWidget(showStartScene);
           radioButtonLayout->addWidget(showEmulate);


           mainLayout->addLayout(buttonLayout);
           mainLayout->addLayout(radioButtonLayout);

           centralWidget->setLayout(mainLayout);
           setCentralWidget(centralWidget);

           connect(moveButton, &QPushButton::clicked, this, &MyMainWindow::moveObject);
           connect(rotateClockwiseButton, &QPushButton::clicked, this, &MyMainWindow::rotateClockwise);
           connect(rotateCounterClockwiseButton, &QPushButton::clicked, this, &MyMainWindow::rotateCounterClockwise);
           connect(resetButton, &QPushButton::clicked, this, &MyMainWindow::resetToDefault);
           connect(backButton, &QPushButton::clicked, this, &MyMainWindow::uploadSave);

           connect(showGridRadio, &QCheckBox::toggled, this, &MyMainWindow::toggleGrid);
           connect(showCoordinatesRadio, &QCheckBox::toggled, this, &MyMainWindow::toggleAxis);
           connect(showStartScene, &QCheckBox::toggled, this, &MyMainWindow::toggleOrigin);
           connect(showEmulate, &QPushButton::clicked, this, &MyMainWindow::toggleEmulate);


           QMenu *fileMenu = menuBar()->addMenu("Файл");
           QMenu *helpMenu = menuBar()->addMenu("Справка");

           QAction *helpAboutTask = new QAction("О программе", this);
           QAction *saveScreen = new QAction("Сохранить", this);
           QAction *helpAboutImplementer = new QAction("О студенте", this);
           connect(helpAboutTask, &QAction::triggered, this, &MyMainWindow::showHelp);

           connect(helpAboutImplementer, &QAction::triggered, this, &MyMainWindow::showImplementer);
           fileMenu->addAction(saveScreen);

           // TODO Назначить кнопкам другую
           helpMenu->addAction(helpAboutTask);
           helpMenu->addAction(helpAboutImplementer);
}

void MyMainWindow::moveObject()
{

        // Проверяем, что в поле lineMoveEdit введено значение
        if (lineMoveEdit->text().isEmpty())
        {
            QMessageBox::warning(this, "Внимание", "Введите координаты перемещения");
            return;
        }
        QString inputText = lineMoveEdit->text();

        // Парсим значения из текста
        QStringList values = inputText.split(',');
        if (values.size() != 2)
        {
            QMessageBox::warning(this, "Внимание", "Введите две координаты");
            return;
        }

        bool okX, okY;
        double x = values[0].toDouble(&okX);  // Преобразуем первую часть в число
        double y = values[1].toDouble(&okY);  // Преобразуем вторую часть в число
        if (!(okX && okY))
        {
            QMessageBox::warning(this, "Внимание", "Введите корректные координаты");
            return;
        }
        scene->setFiguresCenter(QPointF(x, y));

        scene->setPosition(QPointF((x - scene->getVisiableUserRect().width() / 2), y - scene->getVisiableUserRect().height() / 2));

//        qDebug() << scene->getVisiableUserRect().height() << "Height\n";
//        scene->printTransformMatrix();

}

void MyMainWindow::rotateClockwise()
{
    if (lineRotateClockwiseEdit->text().isEmpty())
    {
        QMessageBox::warning(this, "Внимание", "Введите угол");
    }
    QString inputText = lineRotateClockwiseEdit->text();
    auto angle = inputText.toInt();
    angle %= 360;
    scene->setFiguresAngle(angle);
}

void MyMainWindow::rotateCounterClockwise()
{
//    QMessageBox::information(this, "Действие", "Объект повернут против часовой стрелки!");
    scene->addFiguresAngle(10);
}

void MyMainWindow::resetToDefault()
{
    // Очистить сохранение
    scene->toDefaultSetting();
}

void MyMainWindow::uploadSave()
{
    scene->uploadSave();
}

void MyMainWindow::toggleGrid(bool checked)
{
    if (checked)
        scene->setDrawGrid(1);
    else
        scene->setDrawGrid(0);
}

void MyMainWindow::toggleAxis(bool checked)
{
    if (checked)
        scene->setDrawAxis(1);
    else
        scene->setDrawAxis(0);
}

void MyMainWindow::toggleOrigin(bool checked)
{
    if (checked)
        scene->setDrawCenter(1);
    else
        scene->setDrawCenter(0);
}

void MyMainWindow::toggleEmulate(bool checked)
{
    if (checked)
        scene->setDrawSceneRect(1);
    else
        scene->setDrawSceneRect(0);
}

void MyMainWindow::showHelp()
{
    QMessageBox::information(this, "Справка", "Программа реализует поворот, смещение и увеличение объекта.");
}

void MyMainWindow::showImplementer()
{
    QMessageBox::information(this, "Справка", "Лабораторная работа выполнена ст.гр.ИУ7-41БВ Родинковым Алексеем.");
}

void MyMainWindow::closeEvent(QCloseEvent *event)
{
    QCoreApplication::exit();
}


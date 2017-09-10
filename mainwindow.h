#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QMouseEvent>
#include <QGraphicsObject>
#include <QSettings>
#include "sceneeditor.h"
#include "gridscene.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	explicit MainWindow(QWidget *parent = 0);
	~MainWindow();

private slots:
	virtual void mousePressEvent(QMouseEvent *event);

private:
	Ui::MainWindow *ui;
	SceneEditor* editor;

private:
	void writeSettings();
	void readSettings();

};

#endif // MAINWINDOW_H

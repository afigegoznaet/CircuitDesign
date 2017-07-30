#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QMouseEvent>
#include <QGraphicsObject>
#include "sceneeditor.h"
#include "gridscene.h"
#include "capacitor.h"
#include "resistor.h"
#include "inductor.h"
#include "speaker.h"
#include "endpoint.h"

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
	void contextMenuRequested(const QPoint &pos);
	virtual void mousePressEvent(QMouseEvent *event);

private:
	Ui::MainWindow *ui;
	void insertCapacitor();
	void insertResistor();
	void insertInductor();
	void insertSpeaker();
	void insertEndPoint();
	SceneEditor* editor;
};

#endif // MAINWINDOW_H

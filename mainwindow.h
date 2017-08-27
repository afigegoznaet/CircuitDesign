#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QMouseEvent>
#include <QGraphicsObject>
#include "sceneeditor.h"
#include "gridscene.h"
#include "Elements/capacitor.h"
#include "Elements/resistor.h"
#include "Elements/inductor.h"
#include "Elements/speaker.h"
#include "Elements/endpoint.h"

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
	void createMenu();
	void insertCapacitor();
	void insertResistor();
	void insertInductor();
	void insertSpeaker();
	void insertEndPoint();
	SceneEditor* editor;
	QMenu* contextMenu;
};

#endif // MAINWINDOW_H

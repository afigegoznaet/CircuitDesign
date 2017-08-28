#ifndef SCENEEDITOR_H
#define SCENEEDITOR_H

#include <QObject>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QMessageBox>
#include "Elements/endpoint.h"
#include "Elements/capacitor.h"
#include "Elements/inductor.h"
#include "Elements/resistor.h"
#include "Elements/speaker.h"

class SceneEditor : public QObject
{
	Q_OBJECT
public:
	explicit SceneEditor(QObject *parent = nullptr);
	void install(QGraphicsScene *scene);
	bool eventFilter(QObject *, QEvent *);

private slots:
	void contextMenuRequested(const QPoint &pos);

private:
	QGraphicsItem *itemAt(const QPointF&);
	void showMenu(CircuitElement*elem);
	void createMenus();
	void insertElement(ElementType type);

private:
	QGraphicsScene *scene;
	Wire *conn;
	QMenu* sceneContextMenu;
	QMenu* itemContextMenu;
};

#endif // SCENEEDITOR_H

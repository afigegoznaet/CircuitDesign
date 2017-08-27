#ifndef SCENEEDITOR_H
#define SCENEEDITOR_H

#include <QObject>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QMessageBox>
#include "Elements/endpoint.h"
class SceneEditor : public QObject
{
	Q_OBJECT
public:
	explicit SceneEditor(QObject *parent = nullptr);
	void install(QGraphicsScene *scene);
	bool eventFilter(QObject *, QEvent *);

private:
	QGraphicsItem *itemAt(const QPointF&);
	void showMenu(CircuitElement*elem);

private:
	QGraphicsScene *scene;
	Wire *conn;

};

#endif // SCENEEDITOR_H

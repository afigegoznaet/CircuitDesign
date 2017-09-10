#ifndef GRIDSCENE_H
#define GRIDSCENE_H

#include <QObject>
#include <QGraphicsScene>
#include <QPainter>

class GridScene : public QGraphicsScene
{
	Q_OBJECT
public:
	explicit GridScene(QObject *parent = 0);
	int getGridSize(){return gridSize;}
	constexpr static int gridSize = 20;

private:
	virtual void drawBackground(QPainter *painter, const QRectF &rect);
signals:

public slots:
};

#endif // GRIDSCENE_H

#include "gridscene.h"

GridScene::GridScene(QObject *parent) : QGraphicsScene(parent)
{

}

void GridScene::drawBackground(QPainter *painter, const QRectF &rect)
{
	QPen pen;
	painter->setPen(pen);

	qreal left = int(rect.left()) - (int(rect.left()) % gridSize);
	qreal top = int(rect.top()) - (int(rect.top()) % gridSize);
	QVector<QPointF> points;
	for (qreal x = left; x < rect.right(); x += gridSize){
		for (qreal y = top; y < rect.bottom(); y += gridSize){
			points.append(QPointF(x,y));
		}
	}
	painter->drawPoints(points.data(), points.size());
}

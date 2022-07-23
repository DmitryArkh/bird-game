#ifndef PILLARITEM_H
#define PILLARITEM_H

#include <QDebug>
#include <QGraphicsItemGroup>
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QPropertyAnimation>
#include <QRandomGenerator>

class PillarItem : public QObject, public QGraphicsItemGroup
{
    Q_OBJECT
    Q_PROPERTY(double x READ x WRITE setX)

public:
    explicit PillarItem();
    ~PillarItem();
    double x() const;
    void setX(double newX);
    void freezeInPlace();

signals:
    void collideAndFail();

private:
    bool isCollidedWithBird();

    QGraphicsPixmapItem * topPillar;
    QGraphicsPixmapItem * bottomPillar;
    QPropertyAnimation * xAnimation;

    int yPos;
    double m_x;
    bool pastBird;
};

#endif // PILLARITEM_H

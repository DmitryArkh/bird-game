#include "pillaritem.h"
#include "birditem.h"
#include "scene.h"

PillarItem::PillarItem():
    topPillar(new QGraphicsPixmapItem(QPixmap(":/images/pillar.png"))),
    bottomPillar(new QGraphicsPixmapItem(QPixmap(":/images/pillar.png"))),
    pastBird(false)
{
    topPillar->setPos(QPointF(0,0) - QPointF(topPillar->boundingRect().width()/2,
                                             topPillar->boundingRect().height()+60));
    bottomPillar->setPos(QPointF(0,0) + QPointF(-bottomPillar->boundingRect().width()/2,60));

    addToGroup(topPillar);
    addToGroup(bottomPillar);

    yPos = QRandomGenerator::global()->bounded(150);
    int xRandomizer = QRandomGenerator::global()->bounded(200);
    setPos(QPoint(0,0) + QPoint(260 + xRandomizer,yPos));

    xAnimation = new QPropertyAnimation(this,"x",this);
    xAnimation->setStartValue(260 + xRandomizer);
    xAnimation->setEndValue(-260);
    xAnimation->setEasingCurve(QEasingCurve::Linear);
    xAnimation->setDuration(1500);

    connect(xAnimation,&QPropertyAnimation::finished,[=](){
        qDebug() << "Animation finished!";
        scene()->removeItem(this);
        delete this;
    });

    xAnimation->start();
}

double PillarItem::x() const
{
    return m_x;
}

void PillarItem::setX(double newX)
{
    //qDebug() << "PillarItem instance position: " << newX;
    m_x = newX;

    if(m_x < 0 && !pastBird){
        pastBird = true;
        QGraphicsScene* mScene = scene();
        Scene* myScene = dynamic_cast<Scene*>(mScene);
        if(myScene){
            myScene->incrementScore();
        }
    }

    setPos(QPointF(0,0) + QPointF(newX, yPos));
    if(isCollidedWithBird())
        emit collideAndFail();
}

bool PillarItem::isCollidedWithBird()
{
    QList<QGraphicsItem*> collidingItems = topPillar->collidingItems();
    collidingItems.append(bottomPillar->collidingItems());
    for(QGraphicsItem* item: collidingItems){
        BirdItem* birdItem = dynamic_cast<BirdItem*>(item);
        if (birdItem){
            qDebug() << "Collided with a pillar!";
            return true;
        }
    }
    return false;
}

PillarItem::~PillarItem()
{
    qDebug() << "Deleting Pillars..";
    delete topPillar;
    delete bottomPillar;
}

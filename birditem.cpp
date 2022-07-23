#include "birditem.h"

BirdItem::BirdItem(QPixmap pixmap):
    wingPosition(WingPosition::Up),wingDirection(0)
{
    setPixmap(pixmap);
    QTimer * birdWingsTimer = new QTimer(this);
    connect(birdWingsTimer,&QTimer::timeout,[=](){
        updatePixmap();
    });

    birdWingsTimer->start(80);

    groundPosition = scenePos().y() + 295;

    yAnimation = new QPropertyAnimation(this,"y",this);
    yAnimation->setStartValue(scenePos().y());
    yAnimation->setEndValue(groundPosition);
    yAnimation->setEasingCurve(QEasingCurve::InQuad);
    yAnimation->setDuration(1000);

    //yAnimation->start();

    rotationAnimation = new QPropertyAnimation(this,"rotation",this);

}

void BirdItem::updatePixmap()
{
    if(wingPosition == WingPosition::Middle){

        if(wingDirection){
            setPixmap(QPixmap(":/images/bird_blue_up.png"));
            wingPosition = WingPosition::Up;
            wingDirection = 0;
        }else{
            setPixmap(QPixmap(":/images/bird_blue_down.png"));
            wingPosition = WingPosition::Down;
            wingDirection = 1;
        }
    }else{
        setPixmap(QPixmap(":/images/bird_blue_middle.png"));
        wingPosition = WingPosition::Middle;
    }
}

double BirdItem::getRotation() const
{
    return m_rotation;
}

void BirdItem::setRotation(double newRotation)
{
    m_rotation = newRotation;

    QPointF c = boundingRect().center();
    QTransform t;
    t.translate(c.x(), c.y());
    t.rotate(newRotation);
    t.translate(-c.x(),-c.y());
    setTransform(t);
}

double BirdItem::getY() const
{
    return m_y;
}

void BirdItem::shootUp()
{
    yAnimation->stop();
    rotationAnimation->stop();

    double curPosY = getY();
    yAnimation->setStartValue(curPosY);
    yAnimation->setEndValue(curPosY - scene()->sceneRect().height()/8);
    yAnimation->setEasingCurve(QEasingCurve::OutQuad);
    yAnimation->setDuration(285);

    connect(yAnimation,&QPropertyAnimation::finished,
            this, &BirdItem::fallToGroundIfNecessary);

    yAnimation->start();

    rotateTo(-20,200,QEasingCurve::OutCubic);
}

void BirdItem::startFlying()
{
    yAnimation->start();
    rotateTo(90,1200,QEasingCurve::InQuad);
}

void BirdItem::setY(double newY)
{
    moveBy(0, newY - m_y);
    m_y = newY;
}

void BirdItem::rotateTo(const double &end, const int &duration,
                        const QEasingCurve &curve)
{
    rotationAnimation->setStartValue(getRotation());
    rotationAnimation->setEndValue(end);
    rotationAnimation->setEasingCurve(curve);
    rotationAnimation->setDuration(duration);

    rotationAnimation->start();
}

void BirdItem::fallToGroundIfNecessary()
{
    if(y() < groundPosition){
        rotationAnimation->stop();

        yAnimation->setStartValue(y());
        yAnimation->setEasingCurve(QEasingCurve::InQuad);
        yAnimation->setEndValue(groundPosition);
        yAnimation->setDuration(1200);

        yAnimation->start();

        rotateTo(90,1100,QEasingCurve::InCubic);
    }
}

#ifndef BIRDITEM_H
#define BIRDITEM_H

#include <QObject>
#include <QPropertyAnimation>
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QPixmap>
#include <QTimer>

class BirdItem : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
    Q_PROPERTY(double rotation READ getRotation WRITE setRotation)
    Q_PROPERTY(double y READ getY WRITE setY)

public:
    explicit BirdItem(QPixmap pixmap);
    double getRotation() const;
    double getY() const;
    void shootUp();
    void startFlying();
    void freezeInPlace();

signals:

public slots:
    void setRotation(double newRotation);
    void setY(double newY);
    void rotateTo(const double& end,const int& duration,
                  const QEasingCurve& curve);
    void fallToGroundIfNecessary();

private:
    enum WingPosition{Up, Middle, Down};
    void updatePixmap();

    WingPosition wingPosition;
    bool wingDirection; // 0 : down , 1 : up
    double m_rotation;
    double m_y;

    QPropertyAnimation * yAnimation;
    QPropertyAnimation * rotationAnimation;

    double groundPosition;
};

#endif // BIRDITEM_H

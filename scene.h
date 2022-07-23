#ifndef SCENE_H
#define SCENE_H

#include <QDebug>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QKeyEvent>
#include <QTimer>
#include "pillaritem.h"
#include "birditem.h"

class Scene : public QGraphicsScene
{
public:
    Scene(QObject* parent = nullptr);

    bool getGameOn() const;
    void setGameOn(bool newGameOn);
    void startGame();
    void incrementScore();
    void setScore(int newScore);

signals:

public slots:

    // QGraphicsScene interface
protected:
    void keyPressEvent(QKeyEvent *event);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);

private:
    void setBackground();
    void setBird();
    void setUpPillarTimer();
    void cleanPillars();
    void freezeBirdAndPillarsInPlace();
    void showGameOverGraphics();
    void hideGameOverGraphics();

    QTimer * pillarTimer;
    BirdItem * bird;

    bool gameOn;
    int score;
    int bestScore;

    QGraphicsPixmapItem * gameOverPix;
    QGraphicsTextItem * scoreTextItem;
};

#endif // SCENE_H

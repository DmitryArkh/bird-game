#include "scene.h"

Scene::Scene(QObject* parent): QGraphicsScene(parent),
    gameOn(false),score(0),bestScore(0),
    gameOverPix(nullptr),scoreTextItem(nullptr)
{
    setBackground();
    setUpPillarTimer();
    setBird();
}

void Scene::setBackground()
{
    QGraphicsPixmapItem * pixItem = new QGraphicsPixmapItem(QPixmap(":/images/sky.png"));
    addItem(pixItem);
    pixItem->setPos(QPointF(0,0) - QPointF(pixItem->boundingRect().width()/2,
                                           pixItem->boundingRect().height()/2));
}

void Scene::setUpPillarTimer()
{
    pillarTimer = new QTimer(this);
    connect(pillarTimer,&QTimer::timeout,[=](){
        PillarItem * pillarItem = new PillarItem();
        connect(pillarItem,&PillarItem::collideAndFail,[=](){
            pillarTimer->stop();
            freezeBirdAndPillarsInPlace();
            setGameOn(false);
            showGameOverGraphics();
        });
        addItem(pillarItem);
    });

    //pillarTimer->start(1000);
}

void Scene::setBird()
{
    bird = new BirdItem(QPixmap(":/images/bird_blue_up.png"));
    addItem(bird);
}

void Scene::startGame()
{
    bird->startFlying();
    if(!pillarTimer->isActive()){
        cleanPillars();
        setGameOn(true);
        hideGameOverGraphics();
        setScore(0);
        pillarTimer->start(1000);
    }
}

void BirdItem::freezeInPlace()
{
    yAnimation->stop();
    rotationAnimation->stop();
}

void PillarItem::freezeInPlace()
{
    xAnimation->stop();
}

void Scene::freezeBirdAndPillarsInPlace()
{
    bird->freezeInPlace();

    QList<QGraphicsItem *> sceneItems = items();
    foreach (QGraphicsItem *item, sceneItems) {
        PillarItem * pillar = dynamic_cast<PillarItem *>(item);
        if (pillar){
            pillar->freezeInPlace();
        }
    }
}

void Scene::cleanPillars()
{
    QList<QGraphicsItem *> sceneItems = items();
    foreach (QGraphicsItem *item, sceneItems) {
        PillarItem * pillar = dynamic_cast<PillarItem *>(item);
        if (pillar){
            removeItem(pillar);
            delete pillar;
        }
    }
}

bool Scene::getGameOn() const
{
    return gameOn;
}

void Scene::setGameOn(bool newGameOn)
{
    gameOn = newGameOn;
}

void Scene::incrementScore()
{
    score++;
    if(score > bestScore){
        bestScore = score;
    }
    qDebug() << "Score:" << score << "| Best Score:" << bestScore;
}

void Scene::setScore(int newScore)
{
    score = newScore;
}

void Scene::showGameOverGraphics()
{
    gameOverPix = new QGraphicsPixmapItem(QPixmap(":/images/game_over_red.png"));
    addItem(gameOverPix);
    gameOverPix->setPos(QPointF(0,0) - QPointF(gameOverPix->boundingRect().width()/2,
                                               gameOverPix->boundingRect().height()/2));

    scoreTextItem = new QGraphicsTextItem();

    QString htmlString = "<p> Score : " + QString::number(score) + " </p>"
                       + "<p> Best Score : " + QString::number(bestScore) + "</p>";

    QFont mFont("Consolas", 30, QFont::Bold);

    scoreTextItem->setHtml(htmlString);
    scoreTextItem->setFont(mFont);
    scoreTextItem->setDefaultTextColor(Qt::yellow);
    addItem(scoreTextItem);

    scoreTextItem->setPos(QPointF(0,0) - QPointF(scoreTextItem->boundingRect().width()/2,
                                                 -gameOverPix->boundingRect().height()/2));
}

void Scene::hideGameOverGraphics()
{
    if(gameOverPix){
        removeItem(gameOverPix);
        delete gameOverPix;
        gameOverPix = nullptr;
    }

    if(scoreTextItem){
        removeItem(scoreTextItem);
        delete scoreTextItem;
        scoreTextItem = nullptr;
    }
}

void Scene::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Space){
        if(gameOn){
            bird->shootUp();
        }
    }
    QGraphicsScene::keyPressEvent(event);
}

void Scene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(event->button() == Qt::LeftButton){
        if(gameOn){
            bird->shootUp();
        }
    }
    QGraphicsScene::mousePressEvent(event);
}

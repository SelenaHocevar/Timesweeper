#include "Headers/EnemyBoss.h"
#include "Headers/Game.h"
#include "Headers/Projectile.h"

extern Game *game;

EnemyBoss::EnemyBoss()
{
    setPixmap(QPixmap(":/CharacterModels/Resources/CharacterModels/alien_alpha_front.png"));
    connect(this, &EnemyBoss::alphaDied, game, &Game::triggerDialogue);
    connect(this, &EnemyBoss::alphaEscaped, game, &Game::gameOver);
    drawHealthBar();
}

void EnemyBoss::setLives(int lives) { m_lives = lives; }

int EnemyBoss::getLives() const { return m_lives; }

void EnemyBoss::drawHealthBar()
{
    game->bossHead = new QLabel(game);
    game->bossHead->setGeometry(game->width() - 300,
                                  game->height() - 60,
                                  50,
                                  38);
    game->bossHead->setProperty("foo", "boss");

    game->bossHealthBar = new QProgressBar(game);
    game->bossHealthBar->setMinimum(0);
    game->bossHealthBar->setMaximum(80);
    game->bossHealthBar->setValue(80);
    game->bossHealthBar->setTextVisible(false);
    game->bossHealthBar->setGeometry(game->width() - 250,
                                     game->height() - 50,
                                     200,
                                     20);
    game->bossHealthBar->setStyleSheet("QProgressBar::chunk { background: green; }");

    game->bossHead->show();
    game->bossHealthBar->show();
}

void EnemyBoss::advance(int phase)
{
    QGraphicsItem::advance(phase);
    move();
}

void EnemyBoss::move()
{
    // if EnemyBoss leaves the scene it's Game Over
    if(y() + boundingRect().height() <= 0)
    {
        game->scene()->removeItem(this);
        emit alphaEscaped();
    }

    // EnemyBoss starts moving when the player is near
    if(x() - game->player->x() < 650)
    {
        setPos(x(), y() - 1);
    }
}

void EnemyBoss::decreaseHealth()
{
    setLives(--m_lives);
    game->bossHealthBar->setValue(getLives());

    if(getLives() > 20 && getLives() <= 50)
    {
        game->bossHealthBar->setStyleSheet("QProgressBar::chunk { background: orange; }");
    }
    else if(getLives() > 0 && getLives() <= 20)
    {
        game->bossHealthBar->setStyleSheet("QProgressBar::chunk { background: red; }");
    }

    game->bossHealthBar->update();

    if(getLives() == 0)
    {
        game->isGameWon = true;
        emit alphaDied();
    }
}

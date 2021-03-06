#include "Headers/Projectile.h"
#include "Headers/EnemyBoss.h"
#include "Headers/EnemyCharacter.h"
#include "Headers/Game.h"
#include "Headers/Tile.h"

#include <qmath.h>

extern Game *game;

Projectile::Projectile(Shooter shooter)
    : m_shooter(shooter)
{
    if(m_shooter == Shooter::Player)
    {
        setPixmap(QPixmap(":/Other/Resources/Other/player_projectile.png"));
    }
    else
    {
        setPixmap(QPixmap(":/Other/Resources/Other/enemy_projectile.png"));
    }
}

Projectile::Shooter Projectile::getShooter() const { return m_shooter; }

void Projectile::advance(int phase)
{
    QGraphicsItem::advance(phase);
    move(30);
}

void Projectile::move(int distanceToMove)
{
    qreal angle = rotation();
    qreal dy    = distanceToMove * qSin(qDegreesToRadians(angle));
    qreal dx    = distanceToMove * qCos(qDegreesToRadians(angle));

    setPos(x() + dx, y() + dy);

    QList<QGraphicsItem *> colliding_items = collidingItems();
    for(auto &colliding_item : colliding_items)
    {
        if(typeid(*(colliding_item)) == typeid(Tile))
        {
            scene()->removeItem(this);
            delete this;
        }
        else if(typeid(*(colliding_item)) == typeid(EnemyCharacter))
        {
            auto enemy = dynamic_cast<EnemyCharacter *>(colliding_item);
            if(getShooter() == Projectile::Player)
            {
                enemy->decreaseHealth();
                if(enemy->getLives() == 0)
                {
                    enemy->hide();
                    enemy->healthBar->bar->hide();
                    enemy->healthBar->barFrame->hide();
                }

                scene()->removeItem(this);
                delete this;
            }
        }
        else if(typeid(*(colliding_item)) == typeid(EnemyBoss))
        {
            auto enemyBoss = dynamic_cast<EnemyBoss *>(colliding_item);
            if(getShooter() == Projectile::Player)
            {
                enemyBoss->decreaseHealth();
                if(enemyBoss->getLives() == 0)
                {
                    scene()->removeItem(enemyBoss);
                }

                scene()->removeItem(this);
                delete this;
            }
        }

        return;
    }

    // if the projectile goes outside its range we remove it
    if(x() > game->player->x() + 1200 || x() < game->player->x() - 1200 ||
       y() > game->player->y() + 700 || y() < game->player->y() - 700)
    {
        scene()->removeItem(this);
        delete this;
    }
}

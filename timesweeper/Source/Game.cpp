#include <iostream>
#include <QWidget>
#include "Headers/DialogueHandler.h"
#include "Headers/Game.h"
#include "Headers/Level.h"
#include "Headers/Pickup.h"

Game::Game(QWidget *parent)
{
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFixedSize(1200, 700);    // za view

    player = new PlayerCharacter();
    player->setFlag(QGraphicsItem::ItemIsFocusable);
    player->setFocus();

    //prologue level
    currentLevel = Level::LoadLevel(1);
    currentLevel->setSceneRect(0, 0, 2300, 700);
    currentLevel->setBackgroundBrush(QBrush(QImage(":/LevelBackgrounds/Resources/LevelBackgrounds/level_1_prologue.png")));
    DialogueHandler::initializeDialogue( /*level id*/ 1);
    setScene(currentLevel);
    currentLevel->addItem(player);
    centerOn(player);

}

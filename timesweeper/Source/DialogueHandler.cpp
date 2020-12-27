#include "Headers/DialogueHandler.h"
#include "Headers/DialogueBox.h"
#include "Headers/Game.h"

//staticke promenljivie klase DialogueHandler
QVector<QPair<DialogueHandler::Speaker, QString>> DialogueHandler::m_recenice;
int DialogueHandler::m_currentIndex;
DialogueBox *DialogueHandler::m_box;
bool DialogueHandler::isDialogueActive;

extern Game *game;

void DialogueHandler::initializeDialogue()
{
    m_currentIndex   = 0;
    m_recenice       = {};
    isDialogueActive = false;

    QString filename = ":/Levels/Resources/Levels/level" + QString::number(game->getLevelID()) + "_dialogue.txt";
    QFile file(filename);

    if(!file.exists())
    {
        qDebug() << "Fajl ne postoji!\n";
        return ;
    }
    if(!file.open(QIODevice::ReadOnly))
    {
        qDebug() << "Nije uspelo otvaranje fajla!\n";
        return ;
    }

    QTextStream in(&file);

    //prva linija u fajlu govori koliko ce recenica biti
    int numberOfLines = in.readLine().toInt();

    QStringList line;
    for(int i = 0; i < numberOfLines; i++)
    {
        line = in.readLine().split(" # ");
        //qDebug() << line.at(0) << line.at(1);
        int speaker = line.at(0).toInt();
        switch(speaker)
        {
            case 0:
                m_recenice.append(qMakePair(Speaker::Strauss, line.at(1)));
                break;
            case 1:
                m_recenice.append(qMakePair(Speaker::Player, line.at(1)));
                break;
            case 2:
                m_recenice.append(qMakePair(Speaker::Game, line.at(1)));
                break;
            default:
                qDebug() << "Los broj za enum!\n";
        }
    }

    file.close();
}

void DialogueHandler::advanceDialogue()
{
    if(m_box != nullptr)
    {
        game->scene()->removeItem(m_box);
    }

    if(QString::compare(m_recenice[m_currentIndex].second, "endsection") == 0)
    {
        setDialogueActive(false);
    }
    else if(m_currentIndex < m_recenice.size())
    {
            m_box = new DialogueBox(m_recenice[m_currentIndex]);
            game->scene()->addItem(m_box);
    }

    if(m_currentIndex < m_recenice.size() - 1)
    {
        m_currentIndex++;
    }
}

void DialogueHandler::setDialogueActive(bool isActive)
{
    isDialogueActive = isActive;
}

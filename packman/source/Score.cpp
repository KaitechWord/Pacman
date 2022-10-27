#include "../header/Score.h"
#include "QFont"

using namespace Qt;

Score::Score(int x, int y, const QString &text, int score)
    : m_score(score), m_text(text)
{
    setPos(x, y);
    setPlainText(m_text + QString::number(m_score));
    setDefaultTextColor(red);
    setFont(QFont("times", FONT_SIZE));
}

void Score::addScore(int value){
    m_score += value;
    setPlainText(m_text + QString::number(m_score));
}

int Score::getScore() const{
    return m_score;
}


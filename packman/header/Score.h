#pragma once

#include <QGraphicsTextItem> 

#define FONT_SIZE 16

class Score: public QGraphicsTextItem{
    protected:
        int m_score;
        const QString m_text;
    public:
        Score(int x, int y, const QString &text, int score);
        void addScore(int value);
        int getScore() const;
};
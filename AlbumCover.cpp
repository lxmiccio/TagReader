#include "AlbumCover.h"

#include <QDebug>
#include <QFile>
#include <QLabel>
#include <QTextEdit>
#include <QTextStream>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QWidget>

#include "MP3FileInfo.h"
#include "ScrollableArea.h"

AlbumCover::AlbumCover(QWidget *parent) : QMainWindow(parent)
{
    MP3FileInfo* mp3 = new MP3FileInfo("C:/WTF.mp3");

    QFile lrc("C:/WTF.lrc");
    QString lrcText;
    if(lrc.open(QFile::ReadOnly | QFile::Text))
    {
        QTextStream in(&lrc);
        lrcText = in.readAll();
    }

    QStringList rowsLrc = lrcText.split("\n");
    QStringList defRowsLrc;
    QString temp;

    foreach(const QString& line, rowsLrc)
    {
        if(defRowsLrc.size() == 0)
        {
            if(!line.mid(1).startsWith("by") && !line.mid(1).startsWith("id"))
            {
                temp.append(line + "\r\n");
            }

            if(line.length() >= 10 && line.mid(10) == "")
            {
                defRowsLrc << temp;
                temp = "";
            }
        }
        else
        {
            temp.append(line + "\r\n");

            if(line.length() >= 10 && line.mid(10) == "")
            {
                defRowsLrc << temp;
                temp = "";
            }
        }
    }

    QVector<QTextEdit*> lrcEdits;

    foreach(const QString& line, defRowsLrc)
    {
        QTextEdit* textEdit = new QTextEdit();
        textEdit->setText(line);

        lrcEdits.append(textEdit);
    }

    QStringList rowsLyric = mp3->lyrics.split("\n");
    QStringList defRowsLyric;

    foreach(const QString& line, rowsLyric)
    {
        if(line.startsWith("\r"))
        {
            defRowsLyric << temp;
            temp = "";
        }
        else
        {
            temp.append(line + "\n");
        }
    }

    defRowsLyric << temp;

    QVector<QTextEdit*> lyricEdits;

    foreach(const QString& line, defRowsLyric)
    {
        QString temp = line;

        if(temp != defRowsLyric.at(defRowsLyric.size() - 1))
        {
            while(temp.endsWith("\r") || temp.endsWith("\n"))
            {
                temp = temp.left(temp.length() - 2);
            }
        }

        QTextEdit* textEdit = new QTextEdit();
        textEdit->setText(temp);
        textEdit->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

        lyricEdits.append(textEdit);

        int count = temp.count("\r\n");
        const QFontMetrics& metrics = this->fontMetrics();

        textEdit->setFixedHeight(count * metrics.height() + metrics.height() * 2);
    }


    QLabel* label = new QLabel();
    //label->setPixmap(mp3->image.scaled(150, 150, Qt::KeepAspectRatio, Qt::SmoothTransformation));

    ScrollableArea* leftArea = new ScrollableArea();
    QVBoxLayout* leftvlayout = new QVBoxLayout();

    foreach(QTextEdit* textEdit, lrcEdits)
    {
        leftvlayout->addWidget(textEdit);
    }

    QWidget* leftWidget = new QWidget();
    leftWidget->setLayout(leftvlayout);

    leftArea->setWidget(leftWidget);

    ScrollableArea* rightArea = new ScrollableArea();
    QVBoxLayout* rightvlayout = new QVBoxLayout();

    foreach(QTextEdit* textEdit, lyricEdits)
    {
        rightvlayout->addWidget(textEdit);
    }

    QWidget* rightWidget = new QWidget();
    rightWidget->setLayout(rightvlayout);

    rightArea->setWidget(rightWidget);

    QHBoxLayout* hlayout = new QHBoxLayout();
    hlayout->addWidget(leftArea);
    hlayout->addWidget(rightArea);

    QVBoxLayout* vlayout = new QVBoxLayout();
    vlayout->addLayout(hlayout);
    vlayout->addWidget(label);

    QWidget* widget = new QWidget();
    widget->setLayout(vlayout);
    setCentralWidget(widget);
}

AlbumCover::~AlbumCover()
{

}

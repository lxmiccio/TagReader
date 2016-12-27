#ifndef SCROLLABLEAREA_H
#define SCROLLABLEAREA_H

#include <QFileInfo>
#include <QScrollArea>

class ScrollableArea : public QScrollArea
{
    Q_OBJECT

    public:
        ScrollableArea(QWidget* parent = 0);

    signals:
        void fileDropped(const QFileInfo& fileInfo);

    protected:
        virtual void dragEnterEvent(QDragEnterEvent* event);
        virtual void dropEvent(QDropEvent* event);
};

#endif // SCROLLABLEAREA_H

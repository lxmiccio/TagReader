#include "ScrollableArea.h"

#include <QDragEnterEvent>
#include <QMimeData>
#include <QScrollBar>

ScrollableArea::ScrollableArea(QWidget* parent) : QScrollArea(parent)
{
    setAcceptDrops(true);
    setWidgetResizable(true);
}

void ScrollableArea::dragEnterEvent(QDragEnterEvent* event)
{
    event->accept();
}

void ScrollableArea::dropEvent(QDropEvent* event)
{
    QList<QUrl> urls = event->mimeData()->urls();
    QListIterator<QUrl> iterator(urls);

    while(iterator.hasNext()) {
        QFileInfo fileInfo(iterator.next().toLocalFile());
        emit fileDropped(fileInfo);
    }
}

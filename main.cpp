#include "AlbumCover.h"
#include <QApplication>

#include "MP3FileInfo.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    AlbumCover w;
    w.show();

    return a.exec();
}

#ifndef MP3FILEINFO_H
#define MP3FILEINFO_H

#include <QObject>
#include <QImage>
#include <QPixmap>

#include <taglib/fileref.h>
#include <taglib/tag.h>

class MP3FileInfo : QObject
{
    public:
        MP3FileInfo(const QString &filename);

        QString m_filename;

        QPixmap image;

        QString lyrics;

        bool hasV1Tag;
        bool hasV2Tag;
        bool hasLyric;

        quint64 filesize;

        quint64 constantBitrate;
        quint64 variableBitrate;
        quint64 bitrate;
        quint64 sampleRate;
        quint64 length;


        QString szArtist;
        QString szTitle;
        QString szAlbum;
        QString szComment;
        QString szTrack; int nTrack;
        QString szYear; int nYear;
        QString szGenre;
};

#endif // MP3FILEINFO_H

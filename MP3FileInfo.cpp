#include "MP3FileInfo.h"

#include <QDebug>
#include <QFile>
#include <QMap>
#include <QStringListIterator>
#include <QVariant>

#include <lib/include/taglib/attachedPictureFrame.h>
#include "lib/include/taglib/id3v2frame.h"
#include "lib/include/taglib/id3v2header.h"
#include "lib/include/taglib/id3v2tag.h"
#include "lib/include/taglib/mp4file.h"
#include "lib/include/taglib/mpegfile.h"
#include "lib/include/taglib/unsynchronizedlyricsframe.h"

MP3FileInfo::MP3FileInfo(const QString& filename)
{
    TagLib::FileRef fileRef(filename.toStdString().c_str());

    QVariantMap tags;

    if(fileRef.audioProperties())
    {
        tags["bitrate"] = fileRef.audioProperties()->bitrate();
        tags["duration"] = fileRef.audioProperties()->length();
    }

    tags["artist"] = fileRef.tag()->artist().toCString(true);
    tags["album"] = fileRef.tag()->album().toCString(true);
    tags["title"] = fileRef.tag()->title().toCString(true);
    tags["track"] = fileRef.tag()->track();
    tags["year"] = fileRef.tag()->year();


    /* Retrieve cover */
    TagLib::MPEG::File file(filename.toStdString().c_str());
    TagLib::ID3v2::Tag* mp3Tag = file.ID3v2Tag();

    TagLib::ID3v2::FrameList listOfMp3Frames;
    TagLib::ID3v2::AttachedPictureFrame* pictureFrame;

    if(mp3Tag)
    {
        listOfMp3Frames = mp3Tag->frameListMap()["APIC"];
        if(!listOfMp3Frames.isEmpty())
        {
            for(TagLib::ID3v2::FrameList::ConstIterator i_frame = listOfMp3Frames.begin(); i_frame != listOfMp3Frames.end() ; i_frame++)
            {
                pictureFrame = static_cast<TagLib::ID3v2::AttachedPictureFrame*> (*i_frame);

                QByteArray cover = QByteArray(pictureFrame->picture().data(), pictureFrame->picture().size());
                image = QPixmap::fromImage(QImage::fromData(cover));
            }
        }
    }

    /* Retrieve lyrics */
    TagLib::ID3v2::FrameList frames = file.ID3v2Tag()->frameListMap()["USLT"];

    if(!frames.isEmpty())
    {
        TagLib::ID3v2::UnsynchronizedLyricsFrame* frame = dynamic_cast<TagLib::ID3v2::UnsynchronizedLyricsFrame*> (frames.front());
        if(frame)
        {
            lyrics = frame->text().toCString(true);
            lyrics.replace("\r", "\r\n");

            qDebug() << lyrics;

            QString outputFilename = "lyrics.txt";
            QFile outputFile(outputFilename);
            outputFile.open(QIODevice::WriteOnly);

            /* Check it opened OK */
            if(outputFile.isOpen()){
                /* Point a QTextStream object at the file */
                QTextStream outStream(&outputFile);

                /* Write the line to the file */
                outStream << lyrics;

                /* Close the file */
                outputFile.close();
            }
        }
    }
}

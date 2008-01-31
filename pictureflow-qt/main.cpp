/*
  PictureFlow - animated image show widget
  http://pictureflow.googlecode.com

  Copyright (C) 2008 Ariya Hidayat (ariya@kde.org)
  Copyright (C) 2007 Ariya Hidayat (ariya@kde.org)

  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files (the "Software"), to deal
  in the Software without restriction, including without limitation the rights
  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
  copies of the Software, and to permit persons to whom the Software is
  furnished to do so, subject to the following conditions:

  The above copyright notice and this permission notice shall be included in
  all copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
  THE SOFTWARE.
*/

#include <qapplication.h>
#include <qdir.h>
#include <qfileinfo.h>
#include <qpixmap.h>

#include "pictureflow.h"

QStringList findFiles(const QString& path = QString())
{
  QStringList files;

  QDir dir = QDir::current();
  if(!path.isEmpty())
    dir = QDir(path);

  dir.setFilter(QDir::Files | QDir::Hidden | QDir::NoSymLinks);
#if QT_VERSION >= 0x040000
  QFileInfoList list = dir.entryInfoList();
  for (int i = 0; i < list.size(); ++i) 
  {
    QFileInfo fileInfo = list.at(i);
    files.append(dir.absoluteFilePath(fileInfo.fileName()));
  }
#else
  const QFileInfoList* list = dir.entryInfoList();
  if(list) 
  {
    QFileInfoListIterator it( *list );
    QFileInfo * fi;
    while( (fi=it.current()) != 0 ) 
    {
      ++it;
      files.append(dir.absFilePath(fi->fileName()));
    }
  }
#endif

  return files;
}

int main( int argc, char ** argv )
{
  QApplication a( argc, argv );

  PictureFlow* w = new PictureFlow;


#if defined(_WS_QWS) || defined(Q_WS_QWS)
  w->showFullScreen();
  int ww = w->width();
  int wh = w->height();
  int dim = (ww > wh) ? wh : ww;
  dim = dim * 3 / 4;
  w->setSlideSize(QSize(3*dim/5, dim));
#else  
  w->setSlideSize(QSize(3*40, 5*40));
  w->resize(750, 270);
#endif

  QStringList files = (argc > 1) ? findFiles(QString(argv[1])) : findFiles();

  QPixmap pixmap;
  for(int i = 0; i < (int)files.count(); i++)
    if(pixmap.load(files[i]))
      w->addSlide(pixmap);

  w->setCenterIndex(w->slideCount()/2);
  w->setBackgroundColor(Qt::white);
  w->show();

  a.connect( &a, SIGNAL(lastWindowClosed()), &a, SLOT(quit()) );
  return a.exec();
}

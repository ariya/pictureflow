/*
  PictureFlow - animated image show widget
  http://pictureflow.googlecode.com

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

#include <QApplication>
#include <QDir>
#include <QFileInfo>

#include "pictureflow.h"

int main( int argc, char ** argv )
{
  QApplication a( argc, argv );

  PictureFlow* w = new PictureFlow;
  w->setWindowTitle("PictureFlow Demo");

  w->setSlideSize(QSize(150, 250));
  w->setSlideCount(1);
  w->resize(780, 350);

  QPixmap pixmap;
  int count = 0;

  QDir dir = QDir::current();
  if(argc > 1)
    dir = QDir(QString(argv[1]));

  dir.setFilter(QDir::Files | QDir::Hidden | QDir::NoSymLinks);
  QFileInfoList list = dir.entryInfoList();
  for (int i = 0; i < list.size(); ++i) 
  {
    QFileInfo fileInfo = list.at(i);
    if(pixmap.load(dir.absoluteFilePath(fileInfo.fileName())))
    {
      w->setSlideCount(count+1);
      w->setSlide(count, pixmap);
      count++;
    }
  }

  w->setCurrentSlide(count/2);
  w->setSlideCount(qMin(count, 60));
  w->show();

  a.connect( &a, SIGNAL(lastWindowClosed()), &a, SLOT(quit()) );
  return a.exec();
}

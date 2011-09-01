/*
   Copyright 2005-2009 Last.fm Ltd. 

   This file is part of the Last.fm Desktop Application Suite.

   lastfm-desktop is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   lastfm-desktop is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with lastfm-desktop.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef QUICK_START_WIDGET_H
#define QUICK_START_WIDGET_H

#include "lib/unicorn/StylableWidget.h"
#include <radio/RadioStation.h>

class QComboBox;

class QuickStartWidget : public StylableWidget
{
    Q_OBJECT
private:
    struct
    {
        class QLineEdit* edit;
        class QPushButton* button;
    } ui;

public:
    QuickStartWidget( QWidget* parent = 0 );

private slots:
    void play();
    void playNext();

    void setToCurrent();

    void onTextChanged( const QString& text );

    void customContextMenuRequested( const class QPoint& point );

private:

};

#endif

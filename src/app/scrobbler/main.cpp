/***************************************************************************
 *   Copyright 2005-2008 Last.fm Ltd                                       *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *    This program is distributed in the hope that it will be useful,      *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   51 Franklin Steet, Fifth Floor, Boston, MA  02110-1301, USA.          *
 ***************************************************************************/

#include "App.h"
#include "Settings.h"
#include "MainWindow.h"
#include "PlayerManager.h"
#include "PlayerListener.h"
#include "version.h"


int main( int argc, char** argv )
{
    // used by some Qt stuff, eg QSettings
    // must be before Settings object is created
    QCoreApplication::setApplicationName( "AudioScrobbler" );
    QCoreApplication::setOrganizationName( "Last.fm" );
    QCoreApplication::setOrganizationDomain( "last.fm" );

    Settings settings( VERSION, QCoreApplication::applicationFilePath() );
    Settings::instance = &settings;

    App app( argc, argv );

    MainWindow window;
    window.show();

    try
    {
        PlayerListener listener;
        PlayerManager manager;

        manager.connect( &listener, SIGNAL(trackStarted( TrackInfo )), SLOT(onTrackStarted( TrackInfo )) );
        manager.connect( &listener, SIGNAL(playbackEnded( QString )), SLOT(onPlaybackEnded( QString )) );
        manager.connect( &listener, SIGNAL(playbackPaused( QString )), SLOT(onPlaybackPaused( QString )) );
        manager.connect( &listener, SIGNAL(playbackResumed( QString )), SLOT(onPlaybackResumed( QString )) );

        app.connect( &listener, SIGNAL(bootstrapCompleted( QString, QString )), SLOT(onBootstrapCompleted( QString, QString )) );
        app.connect( &manager, SIGNAL(event( int, QVariant )), SLOT(onPlayerManagerEvent( int, QVariant )) );

        return app.exec();
    }
    catch (PlayerListener::SocketFailure& e)
    {
        //TODO
        //FIXME can't have it so that there is no radio option if listener socket fails!
    }   
}
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


PlayerManager::PlayerManager()
{

}


void
PlayerManager::ban()
{}


void
PlayerManager::love()
{}


void
PlayerManager::onTrackStarted( const TrackInfo& t )
{
    QString const id = t.playerId();
    Player& p = m_players[id];
    p.track = t;
    p.state = PlaybackState::Playing;
    p.watch.start();

    if (m_players.top().id == id)
        handleStateChange( p.state, p.track );
}


//TODO really we should be doing more checking, like is the top player actually in the playing state? could be paused.
void
PlayerManager::onPlaybackEnded( const QString& id )
{
    bool const isActive = m_players.top().id == id;

    // do before anything so the state emission we are about to do is reflected
    // here as well as elsewhere
    m_players.remove( id );

    if (isActive)
    {
        if (m_players.count())
        {
            handleStateChange( PlaybackState::Playing, m_players.top().track );
        }
        else
            handleStateChange( PlaybackState::Stopped );
    }
}


void
PlayerManager::onPlaybackPaused( const QString& id )
{}


void
PlayerManager::onPlaybackResumed( const QString& id )
{}


void
PlayerManager::handleStateChange( PlaybackState::Enum newState, const TrackInfo& t )
{
    using namespace PlaybackState;

    PlaybackState::Enum oldState = m_state;
    m_state = newState;

    switch (oldState)
    {
    case Playing:
        switch (newState)
        {
        case Playing:
            emit event( PlaybackEvent::TrackChanged, t );
            break;
        case Stopped:
            emit event( PlaybackEvent::PlaybackEnded );
            break;
        case Paused:
            emit event( PlaybackEvent::PlaybackPaused );
            break;
        }
        break;

    case Stopped:
        switch (newState)
        {
        case Playing:
            emit event( PlaybackEvent::PlaybackStarted, t );
            break;
        case Stopped:
            // do nothing
            break;
        case Paused:
            //TODO this shouldn't happen, but needs handling
            // perhaps we should just stay looking stopped? after all what else
            // can be done?
            break;
        }
        break;

    case Paused:
        switch (newState)
        {
        case Playing:
            emit event( PlaybackEvent::PlaybackResumed );
            break;
        case Stopped:
            emit event( PlaybackEvent::PlaybackEnded );
            break;
        case Paused:
            // do nothing;
            break;
        }
        break;
    }
}
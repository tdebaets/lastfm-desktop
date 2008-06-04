/***************************************************************************
 *   Copyright 2005 - 2008 Last.fm Ltd.                                    *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   51 Franklin Steet, Fifth Floor, Boston, MA  02110-1301, USA.          *
 ***************************************************************************/

#ifndef DLL_EXPORT_MACRO_H
#define DLL_EXPORT_MACRO_H

// When we compile the header in a DLL as part of the DLL, we need
// dllexport for the functions to be exported. When including the header
// as part of the client modules, we need dllimport. X_DLLEXPORT_PRO
// should only be defined in the DLL .pro.
#if defined(_WIN32) || defined(WIN32)
    #ifdef QMAKE_DLLEXPORT
        #define DLLEXPORT __declspec(dllexport)
    #else
        #define DLLEXPORT __declspec(dllimport)
    #endif
#else
    #define DLLEXPORT
#endif

#endif
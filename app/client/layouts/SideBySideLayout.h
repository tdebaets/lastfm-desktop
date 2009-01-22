/***************************************************************************
 *   Copyright 2005-2009 Last.fm Ltd.                                      *
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
 
#ifndef SIDE_BY_SIDE_LAYOUT_H
#define SIDE_BY_SIDE_LAYOUT_H

#include <QLayout>

/** @brief: A layout that allows 2 or more widgets to be laid out side by side
  *         and scroll forwards and backwards with nice animation.
  */

/** still to implement: scrollToWidget method
  *                     handle wrapping around the last/first widgets more nicely 
  *                     make sure it's robust 
  */

class SideBySideLayout : public QLayout
{
    Q_OBJECT
public:
    SideBySideLayout( class QWidget* parent = 0 );
    ~SideBySideLayout();
    
    void addItem(QLayoutItem *item);
    Qt::Orientations expandingDirections() const;
    bool hasHeightForWidth() const;
    int count() const;
    QLayoutItem *itemAt(int index) const;
    QSize minimumSize() const;
    void setGeometry(const QRect &rect);
    QSize sizeHint() const;
    QLayoutItem *takeAt(int index);
    QWidget* currentWidget();
    
public slots:
    void moveForward();
    void moveBackward();
    
private slots:
    void onFrameChanged( int frame );


private:
    void doLayout( const QRect &rect, int hOffset = 0 );
    QList<QLayoutItem *> m_itemList;
    QLayoutItem* m_currentItem;
    class QTimeLine* m_timeLine;
    


};

#endif //SIDE_BY_SIDE_LAYOUT_H
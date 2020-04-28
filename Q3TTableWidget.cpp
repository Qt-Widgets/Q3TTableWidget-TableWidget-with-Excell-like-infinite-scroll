/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** BSD License Usage
** Alternatively, you may use this file under the terms of the BSD license
** as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include "Q3TTableWidget.h"

#include <QScrollBar>
#include <QHeaderView>
#include <QStandardItemModel>

//! [constructor]
Q3TTableWidget::Q3TTableWidget()
{
    m_actualRowCount = 4;
    m_actualColumnCount= 4;
    m_model = new QStandardItemModel();
    m_model->setRowCount(m_actualRowCount);
    m_model->setColumnCount(m_actualColumnCount);
    setModel(m_model);
    init();

    //connect the headers and scrollbars of both tableviews together
    connect(horizontalHeader(),&QHeaderView::sectionResized, this,
          &Q3TTableWidget::updateSectionWidth);
    connect(verticalHeader(),&QHeaderView::sectionResized, this,
          &Q3TTableWidget::updateSectionHeight);
}
//! [constructor]

Q3TTableWidget::~Q3TTableWidget()
{

}

//! [init part1]
void Q3TTableWidget::init()
{
      setHorizontalScrollMode(ScrollPerPixel);
      setVerticalScrollMode(ScrollPerPixel);
}
//! [init part2]


//! [sections]
void Q3TTableWidget::updateSectionWidth(int logicalIndex, int /* oldSize */, int newSize)
{

}

void Q3TTableWidget::updateSectionHeight(int logicalIndex, int /* oldSize */, int newSize)
{

}
//! [sections]

//! [resize]
void Q3TTableWidget::resizeEvent(QResizeEvent * event)
{
    QTableView::resizeEvent(event);
//    int lastCellX = columnViewportPosition(m_model->columnCount());
//    int lastCellY = columnViewportPosition(m_model->rowCount());
    int oldRowConut = m_model->rowCount();
    int oldColumnConut = m_model->columnCount();
    QModelIndex index= m_model->index(oldRowConut - 1, oldColumnConut - 1);
    QRect rect = visualRect(index);
    int incWidth = geometry().right() - rect.right();
    int incHeight = geometry().bottom() - rect.bottom();

    int oneCellWidth = horizontalHeader()->defaultSectionSize();
    int oneCellHeight = verticalHeader()->defaultSectionSize();

    int needColumnCount = static_cast<int>(ceil(static_cast<double>(incWidth)/static_cast<double>(oneCellWidth)));
    int needRowCount = static_cast<int>(ceil(static_cast<double>(incHeight)/static_cast<double>(oneCellHeight)));

    int nNewRowCount = oldRowConut;
    if(needRowCount != 0 && oldRowConut + needRowCount > m_actualRowCount)
    {
        nNewRowCount = oldRowConut + needRowCount;
        m_model->setRowCount(nNewRowCount);
    }
    int nNewColumnCount = oldColumnConut;
    if(needColumnCount != 0 && oldRowConut + needColumnCount > m_actualColumnCount)
    {
        nNewColumnCount = oldColumnConut + needColumnCount;
        m_model->setColumnCount(nNewColumnCount);
    }

    emit rowColumnCountChange(m_actualRowCount, m_actualColumnCount, nNewRowCount, nNewColumnCount);
 }
//! [resize]


//! [navigate]
QModelIndex Q3TTableWidget::moveCursor(CursorAction cursorAction,
                                          Qt::KeyboardModifiers modifiers)
{
    QModelIndex current = QTableView::moveCursor(cursorAction, modifiers);

    if (cursorAction == MoveLeft && current.column() > 0)
    {

    }
    return current;
}
//! [navigate]

void Q3TTableWidget::scrollTo (const QModelIndex & index, ScrollHint hint)
{
QTableView::scrollTo(index, hint);
}



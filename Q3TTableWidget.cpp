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
#include <QWheelEvent>


Q3TTableWidget::Q3TTableWidget()
{
    m_actualRowCount = 10;
    m_actualColumnCount= 10;
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

Q3TTableWidget::~Q3TTableWidget()
{

}

void Q3TTableWidget::updateSectionWidth(int logicalIndex, int /* oldSize */, int newSize)
{

}

void Q3TTableWidget::updateSectionHeight(int logicalIndex, int /* oldSize */, int newSize)
{

}


void Q3TTableWidget::resizeEvent(QResizeEvent * event)
{
    QTableView::resizeEvent(event);

    resetRowColumnCountByGeometry();
 }

static const int incRowCountOneTime = 6;
static const int incColumnCountOneTime = 4;
void Q3TTableWidget::scrollTo(const QModelIndex & index, ScrollHint hint)
{
    int oldRowCount = m_model->rowCount();
    int oldColumnConut = m_model->columnCount();
    int newRowCount = oldRowCount;
    if(index.row() >= oldRowCount - incRowCountOneTime)
    {
        newRowCount = oldRowCount + incRowCountOneTime;
        m_model->setRowCount(newRowCount);
    }
    int newColumnCount = oldColumnConut;
    if(index.column() >= oldColumnConut - incColumnCountOneTime)
    {
        newColumnCount = oldColumnConut + incColumnCountOneTime;
        m_model->setColumnCount(newColumnCount);
    }

    emit rowColumnCountChange(m_actualRowCount, m_actualColumnCount, newRowCount, newColumnCount);

    QTableView::scrollTo(index, hint);
}

void Q3TTableWidget::wheelEvent(QWheelEvent *event)
{
    if(event->delta() < 0)
        resetRowColumnCountByGeometry(false);

    QTableView::wheelEvent(event);
}


void Q3TTableWidget::init()
{
      setHorizontalScrollMode(ScrollPerPixel);
      setVerticalScrollMode(ScrollPerPixel);
}

void Q3TTableWidget::resetRowColumnCountByGeometry(bool isDecrease)
{
    int oldRowConut = m_model->rowCount();
    int oldColumnConut = m_model->columnCount();
    QModelIndex index= m_model->index(oldRowConut - 1, oldColumnConut - 1);
    QRect rect = visualRect(index);

    QRect clientRect = geometry();
    QHeaderView* horiHV =  horizontalHeader();
    QHeaderView* vertHV =  verticalHeader();
    // make clientRect base (0, 0)
    int incWidth = clientRect.right() - clientRect.left() - (rect.right() + horiHV->height());
    int incHeight = clientRect.bottom() - clientRect.top() - (rect.bottom() + vertHV->width());
    int oneCellWidth = horiHV->defaultSectionSize();
    int oneCellHeight = vertHV->defaultSectionSize();

    int needColumnCount = static_cast<int>(ceil(static_cast<double>(incWidth)/static_cast<double>(oneCellWidth)));
    int needRowCount = static_cast<int>(ceil(static_cast<double>(incHeight)/static_cast<double>(oneCellHeight)));

    int newRowCount = oldRowConut;
    if(needRowCount != 0 && (isDecrease || needRowCount + incRowCountOneTime > 0) && oldRowConut + needRowCount > m_actualRowCount)
    {
        newRowCount = oldRowConut + needRowCount + incRowCountOneTime;
        m_model->setRowCount(newRowCount);
    }
    int newColumnCount = oldColumnConut;
    if(needColumnCount != 0 && (isDecrease || needColumnCount + incColumnCountOneTime > 0) && oldRowConut + needColumnCount > m_actualColumnCount)
    {
        newColumnCount = oldColumnConut + needColumnCount + incColumnCountOneTime;
        m_model->setColumnCount(newColumnCount);
    }

    emit rowColumnCountChange(m_actualRowCount, m_actualColumnCount, newRowCount, newColumnCount);
}

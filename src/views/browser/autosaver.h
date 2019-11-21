/****************************************************************************
**
** Copyright (C) 2015 The Qt Company Ltd.
** Contact: http://www.qt.io/licensing/
**
** This file is part of the demonstration applications of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see http://www.qt.io/terms-conditions. For further
** information use the contact form at http://www.qt.io/contact-us.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL included in the
** packaging of this file. Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** As a special exception, The Qt Company gives you certain additional
** rights. These rights are described in The Qt Company LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3.0 as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL included in the
** packaging of this file. Please review the following information to
** ensure the GNU General Public License version 3.0 requirements will be
** met: http://www.gnu.org/copyleft/gpl.html.
**
**
** $QT_END_LICENSE$
**
****************************************************************************/

#ifndef AUTOSAVER_H
#define AUTOSAVER_H

#include <QtCore/QBasicTimer>
#include <QtCore/QObject>
#include <QtCore/QTime>

#include <QtGlobal>
#if QT_VERSION == 0x050600
#include <QObject>
#include <wobjectdefs.h>
#endif

// QT_BEGIN_NAMESPACE

namespace web {
/*
            This class will call the save() slot on the parent object when the
   parent changes.
            It will wait several seconds after changed() to combining multiple
   changes and
            prevent continuous writing to disk.
 */
class AutoSaver : public QObject {
#if QT_VERSION == 0x050600
	W_OBJECT(AutoSaver)
#else
	Q_OBJECT
#endif
	public:
	AutoSaver(QObject *parent);
	~AutoSaver();
	void saveIfNeccessary();

	public slots:
	void changeOccurred();

	protected:
	void timerEvent(QTimerEvent *event);

	private:
	QBasicTimer _timer;
	QTime _firstchange;
};
}

// QT_END_NAMESPACE

#endif  // AUTOSAVER_H

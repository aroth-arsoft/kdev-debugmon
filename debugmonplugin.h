/*
 * Debug Monitor Plugin
 *
 * Copyright 2015 Andreas Roth <aroth@arsoft-online.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of the
 * License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public
 * License along with this program; if not, write to the
 * Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 */

#ifndef _DEBUGMONPLUGIN_H_
#define _DEBUGMONPLUGIN_H_

#include <QByteArray>
#include <QLabel>
#include <QtCore/QVariant>

#include <KConfigGroup>
#include <KTextEditor/Cursor>
#include <QUrl>

#include <interfaces/iplugin.h>
#include <interfaces/istatus.h>

class QLabel;
class QMenu;
class QDBusInterface;
class QSignalMapper;
class ProcessWidget;

class KToolBar;
class QAction;

namespace KDevelop {
class Context;
class ProcessLineMaker;
}

namespace DebugMon
{

class DebugMonitorPlugin : public KDevelop::IPlugin, public KDevelop::IStatus
{
    Q_OBJECT
    Q_INTERFACES(KDevelop::IStatus)

public:
    DebugMonitorPlugin( QObject *parent, const QVariantList & = QVariantList() );
    ~DebugMonitorPlugin();

    virtual void unload() override;
    
    virtual KDevelop::ContextMenuExtension contextMenuExtension( KDevelop::Context* ) override;
    
    DebugSession *createSession();

private Q_SLOTS:

protected:
    virtual void initializeGuiState() override;

private:
    KConfigGroup config() const;

    void attachProcess(int pid);
    void setupActions();

    KConfigGroup m_config;
};

}

#endif
 

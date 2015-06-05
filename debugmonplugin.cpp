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

#include "debugmonplugin.h"


namespace DebugMon
{

K_PLUGIN_FACTORY_WITH_JSON(DebugMonFactory, "kdevdebugmon.json", registerPlugin<DebugMonitorPlugin>(); )


DebugMonitorPlugin::DebugMonitorPlugin( QObject *parent, const QVariantList & ) :
    KDevelop::IPlugin( "kdevgdb", parent ),
    m_config(KSharedConfig::openConfig(), "Debug Monitor")
{
    core()->debugController()->initializeUi();

    setXMLFile("kdevdebugmon.rc");
/*
    core()->uiController()->addToolView(
        i18n("GDB"),
        gdbfactory);
*/

    setupActions();

    setupDBus();
}

void DebugMonitorPlugin::unload()
{
    //core()->uiController()->removeToolView(memoryviewerfactory);
}

void DebugMonitorPlugin::setupActions()
{
    KActionCollection* ac = actionCollection();
}

void DebugMonitorPlugin::setupDBus()
{
}

DebugMonitorPlugin::~DebugMonitorPlugin()
{
}


void DebugMonitorPlugin::initializeGuiState()
{
}

KDevelop::ContextMenuExtension DebugMonitorPlugin::contextMenuExtension( KDevelop::Context* context )
{
    KDevelop::ContextMenuExtension menuExt = KDevelop::IPlugin::contextMenuExtension( context );

    if( context->type() != KDevelop::Context::EditorContext )
        return menuExt;


    return menuExt;
}

void DebugMonitorPlugin::attachProcess(int pid)
{
    /*
    emit showMessage(this, i18n("Attaching to process %1", pid), 1000);

    DebugSession* session = createSession();
    session->attachToProcess(pid);

    KillSessionJob *job = new KillSessionJob(session);
    job->setObjectName(i18n("Debug process %1", pid));
    core()->runController()->registerJob(job);
    job->start();
    */
}

// Used to disable breakpoint actions when non-text document selected

// save/restore partial project session

KConfigGroup DebugMonitorPlugin::config() const
{
    return m_config;
}

}

#include "debugmonplugin.moc"

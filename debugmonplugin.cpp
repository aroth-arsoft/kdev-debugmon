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

#include <kpluginfactory.h>

#include <sublime/view.h>

#include <interfaces/icore.h>
#include <interfaces/iuicontroller.h>
#include <interfaces/idebugcontroller.h>
#include <interfaces/iplugincontroller.h>
#include <interfaces/contextmenuextension.h>
#include <interfaces/context.h>

#include <execute/iexecuteplugin.h>

#include "appperf.h"

namespace DebugMon
{

K_PLUGIN_FACTORY_WITH_JSON(DebugMonFactory, "kdevdebugmon.json", registerPlugin<DebugMonitorPlugin>(); )


template<class T>
class DebugMonToolFactory : public KDevelop::IToolViewFactory
{
public:
  DebugMonToolFactory(DebugMonitorPlugin* plugin, const QString &id, Qt::DockWidgetArea defaultArea)
  : m_plugin(plugin), m_id(id), m_defaultArea(defaultArea)
  {}

  virtual QWidget* create(QWidget *parent = 0) override
  {
    return new T(m_plugin, parent);
  }

  virtual QString id() const override
  {
    return m_id;
  }

  virtual Qt::DockWidgetArea defaultPosition() override
  {
    return m_defaultArea;
  }

  virtual void viewCreated(Sublime::View* view) override
  {
      if (view->widget()->metaObject()->indexOfSignal(QMetaObject::normalizedSignature("requestRaise()")) != -1)
          QObject::connect(view->widget(), SIGNAL(requestRaise()), view, SLOT(requestRaise()));
  }

  /* At present, some debugger widgets (e.g. breakpoint) contain actions so that shortcuts
     work, but they don't need any toolbar.  So, suppress toolbar action.  */
  virtual QList<QAction*> toolBarActions( QWidget* viewWidget ) const override
  {
      Q_UNUSED(viewWidget);
      return QList<QAction*>();
  }

private:
  DebugMonitorPlugin* m_plugin;
  QString m_id;
  Qt::DockWidgetArea m_defaultArea;
};

DebugMonitorPlugin::DebugMonitorPlugin( QObject *parent, const QVariantList & ) :
    KDevelop::IPlugin( "kdevgdb", parent ),
    m_config(KSharedConfig::openConfig(), "Debug Monitor")
{
    core()->debugController()->initializeUi();

    setXMLFile("kdevdebugmon.rc");

    appperformancefactory = new DebugMonToolFactory<ApplicationPerformanceWidget>(
    this, "org.kdevelop.debugmon.Performance",Qt::BottomDockWidgetArea);
    
    core()->uiController()->addToolView(
        i18n("Performance"),
        appperformancefactory);

    setupActions();
}

void DebugMonitorPlugin::unload()
{
    //core()->uiController()->removeToolView(memoryviewerfactory);
}

void DebugMonitorPlugin::setupActions()
{
    KActionCollection* ac = actionCollection();
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

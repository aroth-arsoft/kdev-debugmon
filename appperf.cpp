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

#include "appperf.h"

#include <QIcon>
#include <QVBoxLayout>
#include <QTabWidget>
#include <QAction>

#include <KLocalizedString>

#include <processui/ksysguardprocesslist.h>

#include <ksgrd/SensorManager.h>

#include "ksysguardui/Workspace.h"
#include "ksysguardui/SensorBrowser.h"

namespace DebugMon
{
class DebugMonitorPlugin;

ApplicationPerformanceWidget::ApplicationPerformanceWidget(DebugMonitorPlugin* plugin, QWidget* parent)
    : QWidget(parent)
    , plugin_(plugin)
    , workspace_(NULL)
    , sensorBrowserWidget_(NULL)
{
    setWindowIcon(QIcon::fromTheme("utilities-system-monitor"));
    setWindowTitle(i18n("Performance"));

    QVBoxLayout *l = new QVBoxLayout(this);
    l->setContentsMargins(0, 0, 0, 0);

    workspace_ = new Workspace(this);
    workspace_->setContentsMargins(0, 0, 0, 0);
    l->addWidget(workspace_);

    setLayout(l);

    QAction * newWorksheetAction = new QAction(this);
    newWorksheetAction->setText(i18n("New worksheet"));
    newWorksheetAction->setToolTip(i18nc("@info:tooltip", "New worksheet."));
    newWorksheetAction->setIcon(QIcon::fromTheme("tab-new"));
    connect(newWorksheetAction, &QAction::triggered, workspace_, &Workspace::newWorkSheet);
    addAction(newWorksheetAction);

    QAction * showSensorBrowserWidgetAction = new QAction(this);
    showSensorBrowserWidgetAction->setText(i18n("Show sensors"));
    showSensorBrowserWidgetAction->setToolTip(i18nc("@info:tooltip", "Shows the list of available sensors."));
    connect(showSensorBrowserWidgetAction, &QAction::triggered, this, &ApplicationPerformanceWidget::showSensorBrowserWidget);
    addAction(showSensorBrowserWidgetAction);
    
    workspace_->newWorkSheet();
}

void ApplicationPerformanceWidget::showSensorBrowserWidget()
{
    if(!sensorBrowserWidget_) 
        sensorBrowserWidget_ = new SensorBrowserWidget( this, KSGRD::SensorMgr );
    sensorBrowserWidget_->show();
}

void ApplicationPerformanceWidget::slotAddMonitorView()
{
    /*
    WorkSheet * widget = new WorkSheet(this);
    tab_->addTab(widget, widget->windowTitle());
    tab_->setCurrentIndex(tab_->indexOf(widget));
    */
    //memoryViews_.push_back(widget);
}

}

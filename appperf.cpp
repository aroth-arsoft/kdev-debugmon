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
#include <QToolBox>
#include <QAction>

#include <KLocalizedString>

#include <processui/ksysguardprocesslist.h>

namespace DebugMon
{
class DebugMonitorPlugin;

ApplicationPerformanceWidget::ApplicationPerformanceWidget(DebugMonitorPlugin* plugin, QWidget* parent)
    : QWidget(parent)
{
    setWindowIcon(QIcon::fromTheme("debugger"));
    setWindowTitle(i18n("Performance"));

    QAction * addPerformanceMonitorAction = new QAction(this);
    addPerformanceMonitorAction->setShortcutContext(Qt::WidgetWithChildrenShortcut);
    addPerformanceMonitorAction->setText(i18n("New performance monitor"));
    addPerformanceMonitorAction->setToolTip(i18nc("@info:tooltip", "Open a new performance monitor."));
    addPerformanceMonitorAction->setIcon(QIcon::fromTheme("window-new"));
    connect(addPerformanceMonitorAction, &QAction::triggered, this, &ApplicationPerformanceWidget::slotAddMonitorView);
    addAction(addPerformanceMonitorAction);

    QVBoxLayout *l = new QVBoxLayout(this);
    l->setContentsMargins(0, 0, 0, 0);

    tab_ = new QTabWidget(this);
    tab_->setContentsMargins(0, 0, 0, 0);
    l->addWidget(tab_);

    setLayout(l);
    
    slotAddMonitorView();
}

void ApplicationPerformanceWidget::slotAddMonitorView()
{
    KSysGuardProcessList * widget = new KSysGuardProcessList(this);
    tab_->addTab(widget, widget->windowTitle());
    tab_->setCurrentIndex(tab_->indexOf(widget));
    //memoryViews_.push_back(widget);
}

}

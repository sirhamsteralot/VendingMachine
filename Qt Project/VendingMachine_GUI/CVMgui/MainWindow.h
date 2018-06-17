/****************************************************************************
**
** Copyright (C) 2013 Digia Plc and/or its subsidiary(-ies).
** Contact: http://www.qt-project.org/legal
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** You may use this file under the terms of the BSD license as follows:
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
**   * Neither the name of Digia Plc and its Subsidiary(-ies) nor the names
**     of its contributors may be used to endorse or promote products derived
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

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "StateMachine.h"
#include <QDialog>

QT_BEGIN_NAMESPACE
class QAction;
class QDialogButtonBox;
class QGroupBox;
class QLabel;
class QMenu;
class QMenuBar;
class QPushButton;
class QTextEdit;
QT_END_NAMESPACE

class MainWindow: public QDialog
{
   Q_OBJECT

public:
   MainWindow();
   void enableCentButtons(bool enable);
   void setDisplay(const QString& text);
   void setLogger(const QString& text);

private:
   void createMenu();
   void createHorizontalGroupBoxes();
   void createGridGroupBox();
   void createFormGroupBox();

   enum { NumGridRows = 3, NumButtons = 6 , NumDrinks = 4};

   QMenuBar *menuBar;
   QGroupBox *horizontalGroupBox0;
   QGroupBox *horizontalGroupBox1;
   QGroupBox *horizontalGroupBox2;
   QGroupBox *gridGroupBox;

   QTextEdit *display;
   QTextEdit *logDisplay;
   //QLabel *labels[NumGridRows];
   QPushButton *buttons[NumButtons];
   QPushButton *drinkbuttons[NumDrinks];
   QDialogButtonBox *buttonBox;

   QMenu *fileMenu;
   QAction *exitAction;

   //**************************************************************************
   StateMachine *pStateMachine;
   event_e event;

private slots:
   void coin5C();
   void coin10C();
   void coin20C();
   void coin50C();
   void coin100C();
   void coin420C();

   void drinkCoffee();
   void drinkMokka();
   void drinkChoco();
   void drinkDishwasherwater();
};

#endif // MAINWINDOW_H

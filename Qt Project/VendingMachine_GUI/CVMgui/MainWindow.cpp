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

#include <QtWidgets>
#include <QColor>
#include <QLabel>
#include <QPixmap>
#include <QLineEdit>

#include "AppInfo.h"
#include "MainWindow.h"

MainWindow::MainWindow()
{
   pStateMachine = new StateMachine(this);

   createMenu();
   createHorizontalGroupBoxes();
   createGridGroupBox();

   buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok
                                    | QDialogButtonBox::Cancel);
   connect(buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
   connect(buttonBox, SIGNAL(rejected()), this, SLOT(reject()));

   QVBoxLayout *mainLayout = new QVBoxLayout;
   mainLayout->setMenuBar(menuBar);
   mainLayout->addWidget(horizontalGroupBox0);
   mainLayout->addWidget(horizontalGroupBox1);
   mainLayout->addWidget(gridGroupBox);
   mainLayout->addWidget(horizontalGroupBox2);
   mainLayout->addWidget(horizontalGroupBox3);
   mainLayout->addWidget(buttonBox);

   setLayout(mainLayout);
   setWindowTitle(tr(APPNAME_VERSION));
   pStateMachine->handleEvent(E_INIT);

   QFont font("Comic Sans MS");
   this->setFont(font);
}

void MainWindow::enableCentButtons(bool enable) {
   for (int i = 0; i < NumButtons; i++) {
      buttons[i]->setEnabled(enable);
   }

   for (int i = 0; i < NumDrinks; i++) {
      drinkbuttons[i]->setEnabled(!enable);
   }
}

void MainWindow::enableAdminButtons(bool enable) {
    for (int i = 0; i < NumAdminButtons; i++) {
       adminbuttons[i]->setEnabled(enable);
       adminbuttons[i]->setHidden(!enable);
    }

    for (int i = 0; i < NumAdminLoginButtons; i++) {
       adminloginbuttons[i]->setEnabled(!enable);
       adminloginbuttons[i]->setHidden(enable);
    }

    password ->setEnabled(!enable);
    password ->setHidden(enable);
}

void MainWindow::setDisplay(const QString &text) {
   display->setText(text);
   display->update();
}

void MainWindow::setLogger(const QString &text) {
   logDisplay->moveCursor(QTextCursor::End);
   logDisplay->insertPlainText("\n" + text);
   logDisplay->moveCursor(QTextCursor::End);
}

void MainWindow::createMenu()
{
   menuBar = new QMenuBar;
   fileMenu = new QMenu(tr("&File"), this);
   exitAction = fileMenu->addAction(tr("E&xit"));
   menuBar->addMenu(fileMenu);
   connect(exitAction, SIGNAL(triggered()), this, SLOT(accept()));
}

void MainWindow::createHorizontalGroupBoxes()
{


    // HorizontalGroupBox 0 -----------------------------------------------------
    horizontalGroupBox0 = new QGroupBox(tr("Drink selection"));
    QHBoxLayout *layout0 = new QHBoxLayout;

    drinkbuttons[0] = new QPushButton(tr("Coffee"));
    layout0->addWidget(drinkbuttons[0]);
    connect(drinkbuttons[0], SIGNAL(released()), this, SLOT(drinkCoffee()));

    drinkbuttons[1] = new QPushButton(tr("Mokka"));
    layout0->addWidget(drinkbuttons[1]);
    connect(drinkbuttons[1], SIGNAL(released()), this, SLOT(drinkMokka()));

    drinkbuttons[2] = new QPushButton(tr("Choco"));
    layout0->addWidget(drinkbuttons[2]);
    connect(drinkbuttons[2], SIGNAL(released()), this, SLOT(drinkChoco()));

    drinkbuttons[3] = new QPushButton(tr("Dishwasherwater"));
    layout0->addWidget(drinkbuttons[3]);
    connect(drinkbuttons[3], SIGNAL(released()), this, SLOT(drinkDishwasherwater()));

   horizontalGroupBox0->setLayout(layout0);

   // HorizontalGroupBox 1 -----------------------------------------------------
   horizontalGroupBox1 = new QGroupBox(tr("Input cents"));
   QHBoxLayout *layout1 = new QHBoxLayout;

   buttons[0] = new QPushButton(tr("5C"));
   layout1->addWidget(buttons[0]);
   connect(buttons[0], SIGNAL(released()), this, SLOT(coin5C()));

   buttons[1] = new QPushButton(tr("10C"));
   layout1->addWidget(buttons[1]);
   connect(buttons[1], SIGNAL(released()), this, SLOT(coin10C()));

   buttons[2] = new QPushButton(tr("20C"));
   layout1->addWidget(buttons[2]);
   connect(buttons[2], SIGNAL(released()), this, SLOT(coin20C()));

   buttons[3] = new QPushButton(tr("50C"));
   buttons[3]->setIcon(QIcon(":/icons/50cent.ico"));
   layout1->addWidget(buttons[3]);
   connect(buttons[3], SIGNAL(released()), this, SLOT(coin50C()));

   buttons[4] = new QPushButton(tr("100C"));
   layout1->addWidget(buttons[4]);
   connect(buttons[4], SIGNAL(released()), this, SLOT(coin100C()));

   buttons[5] = new QPushButton(tr("420C"));
   buttons[5]->setIcon(QIcon(":/icons/420.ico"));
   layout1->addWidget(buttons[5]);
   connect(buttons[5], SIGNAL(released()), this, SLOT(coin420C()));

   enableCentButtons(false);
   horizontalGroupBox1->setLayout(layout1);

   // HorizontalGroupBox 2 -----------------------------------------------------
   horizontalGroupBox2 = new QGroupBox(tr("Logging"));
   QHBoxLayout *layout2 = new QHBoxLayout;
   logDisplay = new QTextEdit("Logging started", this);
   logDisplay->setOverwriteMode(false);
   logDisplay->setReadOnly(true);
   layout2->addWidget(logDisplay);
   horizontalGroupBox2->setLayout(layout2);

   // HorizontalGroupBox 3 -----------------------------------------------------
   horizontalGroupBox3 = new QGroupBox(tr("Admin menu"));
   QHBoxLayout *layout3 = new QHBoxLayout;

   password = new QLineEdit;
   password -> setEchoMode(QLineEdit::Password);
   layout3->addWidget(password);

   adminloginbuttons[0] = new QPushButton(tr("Login"));
   layout3->addWidget(adminloginbuttons[0]);
   connect(adminloginbuttons[0], SIGNAL(released()), this, SLOT(adminLogin()));

   adminbuttons[0] = new QPushButton(tr("Refill"));
   layout3->addWidget(adminbuttons[0]);
   connect(adminbuttons[0], SIGNAL(released()), this, SLOT(adminRefill()));

   adminbuttons[1] = new QPushButton(tr("Add 100"));
   layout3->addWidget(adminbuttons[1]);
   connect(adminbuttons[1], SIGNAL(released()), this, SLOT(adminAdd100()));

   adminbuttons[2] = new QPushButton(tr("Empty change"));
   layout3->addWidget(adminbuttons[2]);
   connect(adminbuttons[2], SIGNAL(released()), this, SLOT(adminEmptyChange()));

   adminbuttons[3] = new QPushButton(tr("Exit"));
   layout3->addWidget(adminbuttons[3]);
   connect(adminbuttons[3], SIGNAL(released()), this, SLOT(adminExit()));

   enableAdminButtons(false);
   horizontalGroupBox3->setLayout(layout3);
}

void MainWindow::createGridGroupBox()
{
   gridGroupBox = new QGroupBox(tr("Display"));
   QGridLayout *layout = new QGridLayout;

   QPixmap *image = new QPixmap(":/icons/Coffee.ico");  // in CVMresources.qrc
   QLabel *label = new QLabel;
   label->setPixmap(*image);
   layout->addWidget(label, 0, 0);

   display = new QTextEdit(this);
   display->setReadOnly(true);
   display->setTextColor(QColor(0,0,0));
   display->setFontPointSize(30);
   display->setFixedSize(500, 50);
   display->setOverwriteMode(true);
   layout->addWidget(display, 0, 1, 1, 5);

   layout->setColumnStretch(1, 10);
   layout->setColumnStretch(2, 20);
   gridGroupBox->setLayout(layout);

   for (int i = 0; i < NumButtons; i++) {
       buttons[i]->setStyleSheet("background-color:red;");
   }

}

//----------------------------------------------------------- GUI event handlers
void MainWindow::coin5C()
{
   pStateMachine->handleEvent(E_IN5C);
}

void MainWindow::coin10C()
{
   pStateMachine->handleEvent(E_IN10C);
}

void MainWindow::coin20C()
{
   pStateMachine->handleEvent(E_IN20C);
}

void MainWindow::coin50C()
{
   pStateMachine->handleEvent(E_IN50C);
}

void MainWindow::coin100C()
{
   pStateMachine->handleEvent(E_IN100C);
}

void MainWindow::coin420C()
{
   pStateMachine->handleEvent(E_IN420C);
}

void MainWindow::drinkCoffee() {
    pStateMachine->handleEvent(E_COFFEE);
}

void MainWindow::drinkMokka() {
    pStateMachine->handleEvent(E_MOKKA);
}

void MainWindow::drinkChoco() {
    pStateMachine->handleEvent(E_CHOCO);
}

void MainWindow::drinkDishwasherwater() {
    pStateMachine->handleEvent(E_DISHWASHERWATER);
}

void MainWindow::adminRefill() {
    pStateMachine->handleEvent(E_REFILL);
}

void MainWindow::adminAdd100(){
    pStateMachine->handleEvent(E_ADD100);
}

void MainWindow::adminExit(){
    pStateMachine->handleEvent(E_EXIT);
}

void MainWindow::adminEmptyChange(){
    pStateMachine->handleEvent(E_EMPTYCHANGE);
}

void MainWindow::adminLogin() {
    pStateMachine->handleEvent(E_ADMINLOGIN);
}

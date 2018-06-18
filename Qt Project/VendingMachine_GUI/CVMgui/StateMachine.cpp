#include "MainWindow.h"
#include "StateMachine.h"
#include <QTextEdit>
#include <QPushButton>
#include <iostream>
#include <sstream>
#include <Qfile>
#include <QTextStream>
#include "hal.h"

void StateMachine::handleEvent(event_e eventIn) {
   // Handle sequential states.
   while (eventIn != E_NO) {
      eventIn = statemachine(eventIn);
   }
}

event_e StateMachine::statemachine(event_e eventIn) {
   state_e nextState = S_NO;
   event_e eventOut = E_NO;

   // Sequential states must sent E_SEQ (= eventOut).
   // Sequential stepping ends with sending E_NO.
   switch(currentState) {
   case S_START:
      pDialog->setLogger("-state: Start");
      Log("-state: Start");
      nextState = S_INIT;
      eventOut = E_SEQ;
      break;

   case S_INIT:
      pDialog->setLogger("-state: Init");
      Log("-state: Init");
      money = 0.0;
      selectedDrink = "";

      ReadFromFIle();

      pDialog->setDisplay("Select your drink please");
      pDialog->enableCentButtons(false);
      nextState = S_WAIT_FOR_DRINKS;
      eventOut = E_NO;  // Go waiting for external events: event driven
      break;

   case S_WAIT_FOR_DRINKS:
      pDialog->setLogger("-state: Wait for drinks");
      Log("-state: Wait for drinks");
      switch(eventIn) {
      case E_COFFEE:
         nextState = S_COFFEE;
         break;
      case E_MOKKA:
         nextState = S_MOKKA;
         break;
      case E_CHOCO:
         nextState = S_CHOCO;
         break;
      case E_DISHWASHERWATER:
         nextState = S_DISHWASHERWATER;
         break;
      case E_ADMINLOGIN:
          nextState = S_ADMINLOGON;
          break;
      default:
         pDialog->setLogger("S_WAIT_FOR_DRINKS System ERROR: Unknown drink");
         Log("S_WAIT_FOR_DRINKS System ERROR: Unknown drink");
      }
      eventOut = E_SEQ;
      break;

   case S_COFFEE:
       pDialog->setLogger("-state: Coffee");
       Log("-state: Coffee");

       if (Coffee_Stock < 1) {
           pDialog->setLogger("-state: NotEnoughCoffee");
           nextState = S_WAIT_FOR_DRINKS;
           eventOut = E_NO;
           break;
       }

       pDialog->enableCentButtons(true);
       selectedDrink = "Coffee";
       priceCoke = 100;
       pDialog->setDisplay("Enter your coins please");
       nextState = S_WAIT_FOR_COINS;
       eventOut = E_NO;
   break;

   case S_MOKKA:
       pDialog->setLogger("-state: Mokka");
       Log("-state: Mokka");

       if (Mokka_Stock < 1) {
           pDialog->setLogger("-state: NotEnoughMokka");
           nextState = S_WAIT_FOR_DRINKS;
           eventOut = E_NO;
           break;
       }
       pDialog->enableCentButtons(true);
       pDialog->setDisplay("Enter your coins please");
       selectedDrink = "Mokka";
       priceCoke = 220;

       nextState = S_WAIT_FOR_COINS;
       eventOut = E_NO;
   break;

   case S_CHOCO:
       pDialog->setLogger("-state: Choco");
       Log("-state: Choco");

       if (Choco_Stock < 1) {
           pDialog->setLogger("-state: NotEnoughChoco");
           nextState = S_WAIT_FOR_DRINKS;
           eventOut = E_NO;
           break;
       }
       pDialog->enableCentButtons(true);

       pDialog->setDisplay("Enter your coins please");
       selectedDrink = "Choco";
       priceCoke = 120;

       nextState = S_WAIT_FOR_COINS;
       eventOut = E_NO;
   break;

   case S_DISHWASHERWATER:
       pDialog->setLogger("-state: Dishwasherwater");
       Log("-state: Dishwasherwater");

       if (Dishwater_Stock < 1) {
           pDialog->setLogger("-state: NotEnoughDishwater");
           nextState = S_WAIT_FOR_DRINKS;
           eventOut = E_NO;
           break;
       }
       pDialog->enableCentButtons(true);
       pDialog->setDisplay("Enter your coins please");
       selectedDrink = "Dishwasherwater";
       priceCoke = 420;

       nextState = S_WAIT_FOR_COINS;
       eventOut = E_NO;
   break;

   case S_WAIT_FOR_COINS:
      pDialog->setLogger("-state: Wait for coins");
      Log("-state: Wait for coins");
      switch(eventIn) {
      case E_IN5C:
         nextState = S_5C;
         break;
      case E_IN10C:
         nextState = S_10C;
         break;
      case E_IN20C:
         nextState = S_20C;
         break;
      case E_IN50C:
         nextState = S_50C;
         break;
      case E_IN100C:
         nextState = S_100C;
         break;
      case E_RETURN:
          nextState = S_RETURN;
      case E_ADMINLOGIN:
          nextState = S_ADMINLOGON;
          break;
      default:
         pDialog->setLogger("S_WAIT_FOR_COINS System ERROR: Unknown coin");
         Log("S_WAIT_FOR_COINS System ERROR: Unknown coin");
         nextState = S_UNKNOWN;
      }
      eventOut = E_SEQ;
      break;

   case S_UNKNOWN :
       pDialog->setDisplay("Please try again.");
       nextState = S_WAIT_FOR_COINS;
       eventOut = E_NO;
       break;

   case S_5C:
      pDialog->setLogger("-state: 5C");
      Log("-state: 5C");
      switch(checkCents(5)) {
      case E_MONEY_ENOUGH:
         nextState = S_DRINKOUT;
         eventOut = E_SEQ;
         break;
      case E_MONEY_NOTENOUGH:
         nextState = S_WAIT_FOR_COINS;
         eventOut = E_NO;
         break;
      default:
         pDialog->setLogger("S_5C System ERROR: Unknown event");
         break;
      }
      break;

   case S_10C:
      pDialog->setLogger("-state: 10C");
      Log("-state: 10C");
      switch(checkCents(10)) {
      case E_MONEY_ENOUGH:
         nextState = S_DRINKOUT;
         eventOut = E_SEQ;
         break;
      case E_MONEY_NOTENOUGH:
         nextState = S_WAIT_FOR_COINS;
         eventOut = E_NO;
         break;
      default:
         pDialog->setLogger("S_10C System ERROR: Unknown event");
         break;
      }
      break;

   case S_20C:
      pDialog->setLogger("-state: 20C");
      Log("-state: 20C");
      eventIn = checkCents(20);
      switch(eventIn) {
      case E_MONEY_ENOUGH:
         nextState = S_DRINKOUT;
         eventOut = E_SEQ;
         break;
      case E_MONEY_NOTENOUGH:
         nextState = S_WAIT_FOR_COINS;
         eventOut = E_NO;
         break;
      default:
         pDialog->setLogger("S_20C System ERROR: Unknown event");
         break;
      }
      break;

   case S_50C:
      eventIn = checkCents(50);
      switch(eventIn) {
      case E_MONEY_ENOUGH:
         nextState = S_DRINKOUT;
         eventOut = E_SEQ;
         break;
      case E_MONEY_NOTENOUGH:
         nextState = S_WAIT_FOR_COINS;
         eventOut = E_NO;
         break;
      default:
         pDialog->setLogger("S_50C System ERROR: Unknown event");
         break;
      }
      break;

   case S_100C:
      eventIn = checkCents(100);
      switch(eventIn) {
      case E_MONEY_ENOUGH:
         nextState = S_DRINKOUT;
         eventOut = E_SEQ;
         break;
      case E_MONEY_NOTENOUGH:
         nextState = S_WAIT_FOR_COINS;
         eventOut = E_NO;
         break;
      default:
         pDialog->setLogger("S_100C System ERROR: Unknown event");
         break;
      }
      break;

   case S_RETURN:
   {
       pDialog->setLogger("-state: S_RETURN, returned money");
       Log("-state: S_RETURN, returned money");

       std::stringstream displayBuffer1;
       displayBuffer1 << " = " << money << " cents";
       pDialog->setLogger("-state: CHANGE, change "
                          + QString(displayBuffer1.str().c_str()));
       Log("-state: CHANGE, change "
           + QString(displayBuffer1.str().c_str()));

       nextState = S_INIT;
       eventOut = E_SEQ;
   }
   break;

   case S_DRINKOUT:
      pDialog->setLogger("-state: DRINKOUT, drink is delivered");
      Log("-state: DRINKOUT, drink is delivered");

      if (selectedDrink == "Coffee") {
        Coffee_Stock--;
      } else if (selectedDrink == "Mokka") {
        Mokka_Stock--;
      } else if (selectedDrink == "Choco") {
        Choco_Stock--;
      } else if (selectedDrink == "Dishwasherwater") {
        Dishwater_Stock--;
      }

      Change_Stock += priceCoke;

      WriteToFile();
      nextState = S_CHANGE;
      eventOut = E_SEQ;
      break;

   case S_CHANGE:
   {
      std::stringstream displayBuffer;
      displayBuffer << " = " << money - priceCoke << " cents";
      pDialog->setLogger("-state: CHANGE, change "
                         + QString(displayBuffer.str().c_str()));

      Log("-state: CHANGE, change "
          + QString(displayBuffer.str().c_str()));
      nextState = S_INIT;
      eventOut = E_SEQ;
      break;
   }

   case S_ADMINLOGON:
       pDialog->setLogger("-state: Adminlogon");
       Log("-state: Adminlogon");
       nextState = S_INIT;
       eventOut = E_SEQ;

       if (QString::compare(pDialog->password->text(), QString::number(current_Password)) == 0) {
           nextState = S_ADMINMODE;
           eventOut = E_NO;
           pDialog->enableAdminButtons(true);
           pDialog->enableCentButtons(false);
       }
       break;

   case S_ADMINMODE:
       pDialog->setLogger("-state: adminmode");
       Log("-state: adminmode");

       nextState = S_ADMINMODE;
       eventOut = E_NO;

       switch (eventIn) {
           case E_REFILL:
                Restock();
           break;
           case E_ADD100:
                Change_Stock += 100;
                WriteToFile();
           break;
           case E_EMPTYCHANGE:
                Change_Stock = 0;
                WriteToFile();
           break;
           case E_EXIT:
                pDialog->enableAdminButtons(false);
                pDialog->enableCentButtons(true);
                nextState = S_INIT;
                eventOut = E_SEQ;
           break;
       }
       break;

   default:
      pDialog->setLogger("Statemachine System ERROR: Unknown state");
      Log("Statemachine System ERROR: Unknown state");
      eventOut = E_NO;
      break;
   }
   currentState = nextState;
   return eventOut;
}

event_e StateMachine::checkCents(const int cents) {
   money += cents;
   if (money >= priceCoke) {
      return E_MONEY_ENOUGH;
   }
   else {
      return E_MONEY_NOTENOUGH;
   }
}

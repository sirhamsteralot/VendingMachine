#include "MainWindow.h"
#include "StateMachine.h"
#include <QTextEdit>
#include <QPushButton>
#include <iostream>
#include <sstream>

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
      nextState = S_INIT;
      eventOut = E_SEQ;
      break;

   case S_INIT:
      pDialog->setLogger("-state: Init");
      money = 0.0;
      pDialog->setDisplay("Enter your coins please");
      pDialog->enableCentButtons(true);
      nextState = S_WAIT_FOR_COINS;
      eventOut = E_NO;  // Go waiting for external events: event driven
      break;

   case S_WAIT_FOR_COINS:
      pDialog->setLogger("-state: Wait for coins");
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
      default:
         pDialog->setLogger("S_WAIT_FOR_COINS System ERROR: Unknown event");
      }
      eventOut = E_SEQ;
      break;

   case S_5C:
      pDialog->setLogger("-state: 5C");
      switch(checkCents(5)) {
      case E_MONEY_ENOUGH:
         nextState = S_COKE;
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
      switch(checkCents(10)) {
      case E_MONEY_ENOUGH:
         nextState = S_COKE;
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
      eventIn = checkCents(20);
      switch(eventIn) {
      case E_MONEY_ENOUGH:
         nextState = S_COKE;
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
         nextState = S_COKE;
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

   case S_COKE:
      pDialog->setLogger("-state: COKE, Coke is delivered");
      nextState = S_CHANGE;
      eventOut = E_SEQ;
      break;

   case S_CHANGE:
   {
      std::stringstream displayBuffer;
      displayBuffer << " = " << money - priceCoke << " cents";
      pDialog->setLogger("-state: CHANGE, change "
                         + QString(displayBuffer.str().c_str()));
      nextState = S_INIT;
      eventOut = E_SEQ;
      break;
   }

   default:
      pDialog->setLogger("Statemachine System ERROR: Unknown state");
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

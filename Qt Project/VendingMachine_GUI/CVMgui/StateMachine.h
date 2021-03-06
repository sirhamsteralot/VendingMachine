#ifndef STATEMACHINE_H
#define STATEMACHINE_H

typedef int error_t;

typedef enum {NOERR} error_e;

typedef enum {S_NO, S_START, S_INIT, S_WAIT_FOR_COINS,
              S_5C, S_10C, S_20C, S_50C, S_100C, S_420C,
              S_MOKKA, S_COFFEE, S_DISHWASHERWATER, S_CHOCO,
              S_DRINKOUT,
              S_CHANGE, S_RETURN, S_UNKNOWN, S_WAIT_FOR_DRINKS, S_ADMINMODE, S_ADMINLOGON}
             state_e;
typedef enum {E_NO, E_SEQ, E_INIT, E_WAITFORCOINS, E_RETURN,
              E_IN5C, E_IN10C, E_IN20C, E_IN50C, E_IN100C, E_IN420C,
              E_MOKKA, E_COFFEE, E_DISHWASHERWATER, E_CHOCO,
              E_MONEY_NOTENOUGH, E_MONEY_ENOUGH,
              E_COKE_DELIVERED, E_CHANGE_DELIVERED,
              E_REFILL, E_ADD100, E_EXIT, E_EMPTYCHANGE, E_ADMINLOGIN}
             event_e;

class MainWindow;

class StateMachine {
public:
   StateMachine(MainWindow* pDialog):
      pDialog(pDialog),
      currentState(S_START), money(0.0), priceCoke(125) {}
   ~StateMachine() {}

   void handleEvent(event_e eventIn);
   state_e getCurrentState() const { return currentState; }

private:
   MainWindow *pDialog;
   state_e currentState;
   int money;
   int priceCoke;
   event_e statemachine(event_e eventIn);
   event_e checkCents(const int cents);
};

#endif

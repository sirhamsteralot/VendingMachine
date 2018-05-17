#ifndef STATEMACHINE_H
#define STATEMACHINE_H

typedef int error_t;

typedef enum {NOERR} error_e;

typedef enum {S_NO, S_START, S_INIT, S_WAIT_FOR_COINS,
              S_5C, S_10C, S_20C, S_50C, S_100C, S_420C,
              S_COKE, S_CHANGE}
             state_e;
typedef enum {E_NO, E_SEQ, E_INIT, E_WAITFORCOINS,
              E_IN5C, E_IN10C, E_IN20C, E_IN50C, E_IN100C, E_IN420C,
              E_COKE,
              E_MONEY_NOTENOUGH, E_MONEY_ENOUGH,
              E_COKE_DELIVERED, E_CHANGE_DELIVERED}
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
   const int priceCoke;
   event_e statemachine(event_e eventIn);
   event_e checkCents(const int cents);
};

#endif

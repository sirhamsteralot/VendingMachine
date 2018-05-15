#ifndef STATES_H
#define STATES_H

/*==================| states |==================*/
typedef enum { S_Idle, S_Initialisation, S_Wait_For_Selection, S_Wait_For_Money, S_Amount_Check, S_Admin_Mode, S_Wait_For_Admin_Selection
}
state_t;

#endif // STATES_H

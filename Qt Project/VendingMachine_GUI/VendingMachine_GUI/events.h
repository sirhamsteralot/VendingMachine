#ifndef EVENTS_H
#define EVENTS_H

typedef enum{
                E_10C, E_20C, E_50C, E_100C, E_Not_Enough_Money, E_Enough_Money, E_Start, E_Continue, E_Coffee, E_Mokka,
                E_Choco, E_DishwasherWater, E_OutOfStock, E_AdminMode, E_Restock, E_EmptyChange, E_AddChange100, E_ExitAdmin,
                E_Shutdown
            }
event_t;

state_t event_handler(event_t event);

void initialize(int *money);
void add_10(int *money);
void add_20(int *money);
void add_50(int *money);
void add_100(int *money);
event_t check_amount(const int money);
event_t coin_insertion();
event_t Selection();
event_t AdminModeSelect();

#endif // EVENTS_H

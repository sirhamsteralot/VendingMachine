state_t event_handler(event_t event) {
    static state_t state = S_Idle;
    static int money = 0;
    state_t next_state;

    while (1) {
        // Source States/Events
        switch (state) {
        case S_Idle:
            switch (event) {
            case E_Start:
                // Mealy Action
                // (code here)
                // Destination State
                next_state = S_Initialisation;
                break;
            }
            break;

        case S_Initialisation:
            switch (event) {
            case E_Continue:
                // Mealy Action
                // (code here)
                // Destination State
                next_state = S_Wait_For_Selection;
                break;
            }
            break;
        case S_Wait_For_Selection:
            next_state = S_Wait_For_Money;

            switch (event) {
            case E_Coffee:
                strcpy(drinkName, "Coffee");
                Price = Coffee_Price;
                break;
            case E_Mokka:
                strcpy(drinkName, "Mokka");
                Price = Mokka_Price;
                break;
            case E_Choco:
                strcpy(drinkName, "Choco");
                Price = Choco_Price;
                break;
            case E_DishwasherWater:
                strcpy(drinkName, "DishwasherWater");
                Price = Dishwater_Price;
                break;
            case E_AdminMode:
                next_state = S_Admin_Mode;
                break;
            case E_OutOfStock:
                printf("\nThis item is out of stock,please make a different selection\n");
                next_state = S_Wait_For_Selection;
                break;
            }
            break;
        case S_Wait_For_Money:
            switch (event) {
            case E_10C:
                // Mealy Action
                add_10(&money);
                // Destination State
                next_state = S_Amount_Check;
                break;


            case E_20C:
                // Mealy Action
                add_20(&money);
                // Destination State
                next_state = S_Amount_Check;
                break;


            case E_50C:
                // Mealy Action
                add_50(&money);
                // Destination State
                next_state = S_Amount_Check;
                break;

            case E_100C:
                add_100(&money);
                next_state = S_Amount_Check;
                break;
            }
            break;
        case S_Amount_Check:
            switch (event) {
            case E_Not_Enough_Money:
                // Mealy Action
                printf("\n Not Enough Money:%d", money);
                // Destination State
                next_state = S_Wait_For_Money;
                break;

            case E_Enough_Money:
                // Mealy Action
                dispense_coffee(money, Price, drinkName, &Change_Stock, &Coffee_Stock, &Mokka_Stock, &Choco_Stock, &Dishwater_Stock);
                WriteToFile();
                // Destination State
                next_state = S_Initialisation;
                break;
            }
            break;

        case S_Admin_Mode:
            // Default Destination State
            next_state = S_Admin_Mode;
            switch (event) {
            case E_Restock:
                // Mealy Action
                Restock();
                puts("Restocked!");
                break;
            case E_AddChange100:
                // Mealy Action
                Change_Stock += 100;
                WriteToFile();
                puts("Added 100 cents");
                break;
            case E_EmptyChange:
                // Mealy Action
                Change_Stock = 0;
                WriteToFile();
                puts("Emptied change!");
                break;
            case E_ExitAdmin:
                // Mealy Action
                system("@cls||clear");
                // Destination State
                next_state = S_Initialisation;
                break;
            case E_Shutdown:
                // Mealy Action
                WriteToFile();
                exit(0);
            }
            break;
        }
        /*=========| Destination States |=========*/
        switch (next_state) {
        case S_Initialisation:
            // Moore Action
            initialize(&money);
            // Event Generation
            event = E_Continue;
            break;
        case S_Wait_For_Selection:
            // Moore Action
            event = Selection();
            // Event Generation/Preparation
            event = event;
            break;

        case S_Admin_Mode:
            // Moore Action
            system("@cls||clear");
            puts("Welcome to the admin mode");
            event = AdminModeSelect();
            // Event Generation/Preparation
            event = event;
            next_state = S_Admin_Mode;
            break;

        case S_Wait_For_Money:
            // Moore Action
            printf("\nI have the %s if you have the coin. (%d cent)\n", drinkName, Price);
            event = coin_insertion();
            // Event Generation/Preparation
            event = event;
            break;
        case S_Amount_Check:
            // Moore Action
            event = check_amount(money);
            // Event Generation/Preparation
            event = event;
            break;
        }
        state = next_state;
    }
}

/*===============| Initialization |===============*/
void initialize(int *money) {
    *money = 0;
    ReadFromFIle();
}

/*==============| Money Inserted Logic. |==============*/
void add_10(int *money) {
    *money += 10;
    Change_Stock += 10;
    WriteToFile();
}

void add_20(int *money) {
    *money += 20;
    Change_Stock += 20;
    WriteToFile();
}

void add_50(int *money) {
    *money += 50;
    Change_Stock += 50;
    WriteToFile();
}

void add_100(int *money) {
    *money += 100;
    Change_Stock += 100;
    WriteToFile();
}

/*===============| Amount Check Event |===============*/
event_t check_amount(const int money) {
    return (money < Price) ? E_Not_Enough_Money : E_Enough_Money;
}

/*============| Coin Selection interface |============*/
event_t coin_insertion() {
    int sel;
    while (1)
    {
        puts("Select your coin");
        puts("1-- 10 Cent");
        puts("2-- 20 Cent");
        puts("3-- 50 Cent");
        puts("4-- 100 Cent");

        scanf("%d", &sel);
        getchar();

        switch (sel)
        {
        case 1:
            return E_10C;
            break;
        case 2:
            return E_20C;
            break;
        case 3:
            return E_50C;
            break;
        case 4:
            return E_100C;
            break;
        default:
            puts("Wrong Selection");
        }

    }
}

/*============| Main selection interface |============*/
event_t Selection() {
    int sel;
    while (1)
    {
        puts("Select your option");
        puts("1-- Coffee");
        puts("2-- Mokka");
        puts("3-- Choco");
        puts("4-- DishwasherWater");
        puts("5-- Administrator mode");

        scanf("%d", &sel);
        getchar();

        switch (sel)
        {
        case 1:
            if (Coffee_Stock > 0)
                return E_Coffee;
            else
                return E_OutOfStock;
            break;
        case 2:
            if (Mokka_Stock > 0)
                return E_Mokka;
            else
                return E_OutOfStock;
            break;
        case 3:
            if (Choco_Stock > 0)
                return E_Choco;
            else
                return E_OutOfStock;
            break;
        case 4:
            if (Dishwater_Stock > 0)
                return E_DishwasherWater;
            else
                return E_OutOfStock;
            break;
        case 5:
            puts("Please enter the administrator password");
            int input;
            scanf("%d", &input);

            if (input == current_Password)
                return E_AdminMode;
            else
                puts("Incorrect password");

            break;
        default:
            puts("Wrong Selection");
            break;
        }
    }
}

/*===========| Admin mode selection interface |===========*/
event_t AdminModeSelect() {
    int sel;

    while (1)
    {
        puts("\nSelect your option:");
        puts("1-- Refill all");
        puts("2-- Empty change");
        puts("3-- Add 100 cents to change");
        puts("4-- Change admin password");
        puts("5-- Exit admin mode");
        puts("6-- Shutdown");

        scanf("%d", &sel);
        getchar();
        switch (sel) {
        case 1:
            return E_Restock;
            break;
        case 2:
            return E_EmptyChange;
            break;
        case 3:
            return E_AddChange100;
            break;
        case 4:
            puts("Please insert new password (must be a number):");
            scanf("%d", &current_Password);
            WriteToFile();
            break;
        case 5:
            return E_ExitAdmin;
            break;
        case 6:
            return E_Shutdown;
            break;
        default:
            puts("Wrong Selection");
            break;
        }
    }
}

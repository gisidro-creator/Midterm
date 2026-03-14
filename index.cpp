#include <iostream>
#include <vector>
using namespace std;

void clearScreen() {
#if _WIN32
    system("cls");
#else
    system("clear");
#endif
}

// Recursive function to calculate number of bills for a given amount
void calculateBills(double amount,int& bills1000, int& bills500) {
    if (amount >= 1000) {
        bills1000++;
        calculateBills(amount - 1000, bills1000, bills500);
    } 
    else if (amount >= 500) {
        bills500++;
        calculateBills(amount - 500, bills1000, bills500);
    }
    // Base case: amount < 500, recursion stops automatically
}

int login(){

    cout << "====================================\n";
    cout << "                ATM \n";
    cout << "====================================\n\n";

    int choice;
    cout << "[1]User     " << "[2]Admin" << endl;
    cin >> choice;

    if(choice == 1){
        return 1;
    }
    else if(choice == 2){
        return 2;
    }
    else{
        cout << "Invalid Choice";
        return 0;
    }
};


int displayMenu(){;
    int choice;



    cout << "====================================\n";
    cout << "                ATM \n";
    cout << "====================================\n\n";

    cout << "=========================== \n";
    cout << "[1] Check Balance \n";
    cout << "[2] Widthraw Cash \n";
    cout << "[3] Transfer funds \n";
    cout << "[4] View transaction summary \n";
    cout << "[5] Exit\n";
    cout << "=========================== \n";
    cin >> choice;

    return choice;
};


int clientMenu(vector <string>& card, vector<string>& cardNumbers, vector<string>& encodedPINs, 
    vector<double>& balances, vector<string>& userBanks, int billCount[], double localFees[], string bankNames[],  
    vector<string>& accountTypes,  double intlFees[]){
    int contin; // variable for UI to continue
    int index; //index of the corresponding vectors
    int enterNumber;




    cout << "====================================\n";
    cout << "            ATM LOGIN\n";
    cout << "====================================\n\n";

    cout << "Insert Card: \n";

    for(int i = 0; i < card.size(); i++){    // print the cards in hand
        cout << "["<< i + 1 <<"]" << card[i] << endl; 
    }
    cin >> enterNumber;
    if(enterNumber < 1 || enterNumber > card.size()){ // Checks for invalid input
        int contin;
        cout << "\n------------------------------------\n";
        cout << "Invalid input \n";
        cout << "press any key to continue: ";
        cin >> contin;
        clearScreen();
        return 0;
    }

    index = enterNumber - 1;

    clearScreen();

    int choice;
    do{
        clearScreen();
        choice =  displayMenu();

        if(choice == 1){              //Checks balance
            string pin;
            cout << "Enter PIN: ";
            cin >> pin;
            if(pin != encodedPINs[index]){ // check for invalid input
                cout << "Invalid pin"; 
                return 0;
            }
            else{
                cout << "\n------------------------------------\n";
                cout << "Current Balance: " << balances[index] << endl;
                cout << "\n------------------------------------\n";
                cout << "Press any key to continue: "; 
                cin >> contin;
            }
        }
        else if(choice == 2){ // widthraw money
            int amount;
            int bills1000 = 0;
            int bills500 = 0;

            cout << "\n=========== WITHDRAW MONEY ==========\n";


            cout << "\n \n Choose amount to widthraw:\n" ;

            int widthraw[] = {500, 1000, 2000, 3000, 4000, 5000, 6000, 7000, 8000, 9000, 10000};
            for(int i = 0; i < 11; i++){
                cout << "[" << i + 1 << "]" << widthraw[i] << endl;
            }

            int selection;
            cin >> selection;

            if(selection < 1 || selection > 11){
                cout << "Invalid selection.\n";
                return 0;
            }

            amount = widthraw[selection - 1];
        
            string pin;
            cout << "Enter PIN: ";
            cin >> pin;
            if(pin != encodedPINs[index]){
                cout << "Invalid pin";
                return 0;
                }
            else{

                calculateBills(amount,bills1000, bills500);

                // Check if ATM has enough bills
                if (bills1000 > billCount[1] || bills500 > billCount[0]) {
                    cout << "ATM does not have enough bills for this amount.\n";
                } 
                else {
                    string accountType = accountTypes[index]; 
                    int bankIDX; 
                    double fee;

                    for(int i = 0; i < 4; i++){
                        if(bankNames[i] == userBanks[index]){
                            bankIDX = i;
                            break;
                        }
                    }

                    if(accountType == "Local"){ // checks if account is local or international
                        fee = localFees[bankIDX];
                    } else {
                        fee = intlFees[bankIDX];
                    }


                    double totalDispensed = bills1000 * 1000 + bills500 * 500;

                    if(totalDispensed + fee > balances[index]){
                        cout << "Insufficient balance to cover withdrawal service fee.\n";
                    }
                    else{
                        // Dispense the money
                        billCount[1] -= bills1000; // minus 1000 bills
                        billCount[0] -= bills500;  // minus 500 bills


                        cout << "\n=========== CASH DISPENSED ==========\n";
                        cout << "Dispensed:\n";
                        cout << bills1000 << " x 1000\n";
                        cout << bills500 << " x 500\n";
                        cout << "------------------------------------\n";

                        cout << "Service Fee: PHP " << fee << endl;
                        cout << "Total dispensed: PHP " << totalDispensed << "\n";

                        balances[index] = balances[index] - totalDispensed;
                        balances[index] = balances[index] - fee;
                        cout << "Press any key to continue: "; 
                        cin >> contin;
                    }
                }      
            }
        }

    }while(choice != 5);
};


void adminMenu();



int main(){
    const int NUM_BANKS = 4;
    string bankNames[NUM_BANKS] = {"BDO", "BPI", "Metrobank", "Security Bank"};
    double localFees[NUM_BANKS] = {25, 20, 30, 15};
    double intlFees[NUM_BANKS] = {150, 125, 200, 100};
    double dailyLimits[NUM_BANKS] = {50000, 75000, 100000, 60000};

    const int NUM_DENOMINATIONS = 2;
    int denominations[NUM_DENOMINATIONS] = {500, 1000};
    int billCount[NUM_DENOMINATIONS] = {500, 500}; 



    vector<string> card = {"BDO", "BPI"};

    vector<string> cardNumbers = {"123456789123", "987654321987"};
    // Parallel vectors - keep in sync!


    vector<string> encodedPINs = {"123456", "654321"};     
    // Encoded passwords


    vector<double> balances = {10000, 5000};        
    // Account balances


    vector<string> userBanks = {"BDO", "BPI"};        
    // Which bank


    vector<string> accountTypes = {"Local", "Local"};    
    // "Local" or "International"

    while(true){
        int role = login();
        if(role == 1){
            clientMenu(card, cardNumbers, encodedPINs, balances, userBanks, billCount, localFees, bankNames, accountTypes, intlFees);
        }
    }
    
    return 0;
}

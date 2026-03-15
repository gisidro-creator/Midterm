#include <iostream>
#include <vector>
#include <ctime>

using namespace std;

string encodeString(string plain) {
    string encoded = "";
    for (char c : plain) {
        encoded += to_string((int)c) + "-"; 
    }
    return encoded;
}

void updateBalance(vector<double>& balances, int index, double amount) {
    balances[index] -= amount;
}
void updateBalance(vector<double>& balances, int index, string amountStr) {
    double amount = stod(amountStr);
    updateBalance(balances, index, amount);
}

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

//Recursive fucntion that calculate the fees
double calculateFee(int transactions, double bankFee){
    if(transactions == 0){
        return 0; // base case
    }

    return bankFee + calculateFee(transactions - 1, bankFee);
}



// reccursion for calculating tranfer funds
void deductBalance(double& balance, double amount){
    if(amount <= 0){
        return; // base case
    }

    balance -= amount;     // subtract once
    deductBalance(balance, 0); 
}

// Recursive function to deduct from daily limit
void deductDailyLimit(double& dailyLimit, double amount) {
    if (amount <= 0) {
        return; // base case
    }

    double chunk = (amount > 1000) ? 1000 : amount; 
    dailyLimit -= chunk;

    deductDailyLimit(dailyLimit, amount - chunk);
}

string getTime() { // couts time
    time_t now = time(0);
    tm* localtm = localtime(&now);

    char buffer[80];
    strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", localtm);

    return buffer;
}


void transactionHistory(vector<string>& transactionTypes, vector<double>& transactionAmounts, vector<double>& transactionFees,
     vector<int>& transactionQuantities,  vector <string>& time, vector <int>& owner, int& index, string bankNames[], vector<string>& accountTypes){
    clearScreen();
    string key;
    
    cout << "============================================== \n";
    cout << "             Transaction History \n";
    cout << "-----------------------------------------------\n";
    cout << " Date & Time: " << getTime() << "\n";
    cout << "  Bank: " << bankNames[index] << "           Type: " << accountTypes[index] << endl;
    cout << "-----------------------------------------------\n";

    for(int i = 0; i < transactionTypes.size(); i++){

        if(owner[i] == index){
            cout << "Type: " << transactionTypes[i] << endl;
            cout << "Amount: " << transactionAmounts[i] << endl;
            cout << "Fee: " << transactionFees[i] << endl;
            cout << "Quantity : " << transactionQuantities[i] << endl;
            cout << "Time: " << time[i] << endl;
            cout << "-----------------------------------------------\n";
        }
    }

    cout << "Press any key to continue: ";
    cin >> key;
}

int login(){

    cout << "====================================\n";
    cout << "                ATM \n";
    cout << "====================================\n";
    cout << "Date & Time: " << getTime() << "\n";
    cout << "----------------------------------------\n";

    int choice;
    cout << "[1]User     " << "[2]Admin" << "  [3]Exit " << endl;
    cin >> choice;

    if(choice == 1){
        return 1;
    }
    else if(choice == 2){
        return 2;
    }
    else if(choice == 3){
        return 0;
    }
    else{
        cout << "Invalid Choice";
        return 0;
    }
};


int displayMenu(int& index, string bankNames[], vector<string>& accountTypes){;
    clearScreen();
    int choice;

    cout << "\n";
    cout << "========================================\n";
    cout << "              WELCOME TO ATM            \n";
    cout << "========================================\n";
    cout << " Date & Time: " << getTime() << "\n";
    cout << "  Bank: " << bankNames[index] << "           Type: " << accountTypes[index] << endl;
    cout << "----------------------------------------\n";
    cout << "  [1] Check Balance\n";
    cout << "  [2] Withdraw Cash\n";
    cout << "  [3] Transfer Funds\n";
    cout << "  [4] Transaction Summary\n";
    cout << "  [5] Change PIN \n";
    cout << "  [6] Exit\n";
    cout << "----------------------------------------\n";
    cout << "  Enter Choice: ";
    
    cin >> choice;

    cout << "========================================\n";


    return choice;
};


void clientMenu(vector <string>& card, vector<string>& cardNumbers, vector<string>& encodedPINs, 
    vector<double>& balances, vector<string>& userBanks, int billCount[], double localFees[], string bankNames[],  
    vector<string>& accountTypes,  double intlFees[], double dailyLimits[], vector<string>& transactionTypes  ,vector<double>& transactionAmounts, vector<double>& transactionFees,
    vector<int>& transactionQuantities,  vector <string>& time, vector <int>& owner){

    int choice = 0;   
    int index = 0;    
    int bankIDX = 0;  
    string contin; // variable for UI to continue

    while(true) { // loop for inserting card 
        clearScreen();
        cout << "====================================\n";
        cout << "            ATM LOGIN\n";
        cout << "====================================\n\n";
        cout << "Date & Time: " << getTime() << "\n";
        cout << "----------------------------------------\n";

        cout << "Insert Card: \n";
        for(int i = 0; i < card.size(); i++){    
            cout << "["<< i + 1 <<"] " << card[i] << endl; 
        }
        cout << "[0] Exit\n";


        int enterNumber;
        cout << "Enter Choice: ";
        cin >> enterNumber;

        if(enterNumber == 0){
            clearScreen();
            return;
        }; // exit back to main
        if(enterNumber < 1 || enterNumber > card.size()) {
            cout << "Invalid input. Press any key to continue: ";
            cin >> contin;
            continue; // retry card insertion
        }

        int index = enterNumber - 1;

        // Now show the ATM menu for this card
        int choice;
        int bankIDX; 

        string pin;
        cout << "Enter PIN: ";
        cin >> pin;

        if (encodeString(pin) != encodedPINs[index]) { 
        cout << "Invalid PIN!\n";
   
        }

        }
        clearScreen();

        do{
            choice =  displayMenu(index,bankNames ,accountTypes);

            if(choice == 1){              //Checks balance
                clearScreen();
                cout << "\n=========== Balance ==========\n";
                cout << "Date & Time: " << getTime() << "\n";
                cout << "  Bank: " << bankNames[index] << "      Type: " << accountTypes[index] << endl;
                cout << "----------------------------------------\n";
                cout << "------------------------------------\n";
                cout << "Current Balance: " << balances[index] << endl;
                cout << "\n------------------------------------\n";

                cout << "Press any key to continue: "; 
                cin >> contin;
                clearScreen();
            }
            else if(choice == 2){ // widthraw money
                clearScreen();
                int amount;
                int bills1000 = 0;
                int bills500 = 0;

                cout << "\n=========== WITHDRAW MONEY ==========\n";
                cout << "Date & Time: " << getTime() << "\n";
                cout << "  Bank: " << bankNames[index] << "      Type: " << accountTypes[index] << endl;
                cout << "----------------------------------------\n";


                cout << "\n Choose amount to widthraw:\n" ;

                int withdraw[] = {500, 1000, 2000, 3000, 4000, 5000, 6000, 7000, 8000, 9000, 10000};
                for(int i = 0; i < 11; i++) {

                    cout << "[" << i+1 << "] "
                        << withdraw[i];

                    // spacing for alignment
                    if(withdraw[i] < 10000)
                        cout << "   ";

                    // print 2 columns
                    if(i % 2 == 1 || i == 10)
                        cout << endl;
                    else
                        cout << "        ";
                }

                cout << "\n=====================================\n";

                int selection;
                cout << "Enter Choice: ";
                cin >> selection;

                if(selection < 1 || selection > 11){
                    cout << "Invalid selection.\n";
                    cout << "Press any key to continue";
                    cin >> contin;
                    continue;
                }

                amount = withdraw[selection - 1];
        

                calculateBills(amount,bills1000, bills500);


                // Check if ATM has enough bills
                if (bills1000 > billCount[1] || bills500 > billCount[0]) {
                    cout << "ATM does not have enough bills for this amount.\n";
                    cout << "Press any key to continue: ";
                    cin >> contin;
                    continue;
                } 
                else {
                    string accountType = accountTypes[index]; 
                    double fee;

                    for(int i = 0; i < 4; i++){
                        if(bankNames[i] == userBanks[index]){
                            bankIDX = i;
                            break;
                        }
                    }


                    if(dailyLimits[bankIDX] <= 0){
                        cout << "Daily limit of widthraw for bank has reached can no longer widthraw. \n";
                        cout << "Press any key to continue: ";
                        cin >> contin;
                        continue;
                    }
                    //checks if daily limit for bank has been reached 
                    deductDailyLimit(dailyLimits[bankIDX], amount);

                    if(accountType == "Local"){ // checks if account is local or international
                        fee = localFees[bankIDX];
                    } else {
                        fee = intlFees[bankIDX];
                    }

                    fee = calculateFee(1, fee); 
                    double totalDispensed = bills1000 * 1000 + bills500 * 500;

                    if(totalDispensed + fee > balances[index]){
                        cout << "Insufficient balance to cover withdrawal service fee.\n";
                        cout << "Press any key to continue: "; 
                        cin >> contin;
                        continue;
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

                        deductBalance(balances[index], totalDispensed);
                        deductBalance(balances[index], fee);

                        transactionTypes.push_back("Withdraw");
                        transactionAmounts.push_back(amount);
                        transactionFees.push_back(fee);
                        transactionQuantities.push_back(1);
                        owner.push_back(index);
                        time.push_back(getTime()); 

                        cout << "Press any key to continue: "; 
                        cin >> contin;
                        clearScreen();

                    }
                }      
                
            }
            else if(choice == 3){ // transfer fund
                string numofRecepient;
                double  transferAmount;
                int receptantIndex = -1;
                int senderIndex;
                double fee;
                string accountType = accountTypes[index]; 

                cout << "Enter Account Number where to transfer fund: ";
                cin >> numofRecepient;

                for(int i = 0; i < cardNumbers.size(); i++){
                    if(numofRecepient == cardNumbers[i]){
                        receptantIndex = i;
                        break;
                    }
                }
                if(receptantIndex == -1){
                    cout << "Cannot find recepient \n";
                    cout << "Press any key to continue";
                    cin >> contin;
                    continue;
                }



                cout << "============= \n";
                cout << "Enter amount: ";
                cin >> transferAmount;

                
                for(int i = 0; i < 4; i++){
                    if(bankNames[i] == userBanks[index]){
                    senderIndex = i;
                    break;
                    }
                }

                if(accountType == "Local"){ // checks if account is local or international
                    fee = localFees[senderIndex];
                }
                else {
                    fee = intlFees[senderIndex];
                }

                if(balances[index] < transferAmount + fee){
                    cout << "Insufficient balance.\n";
                    cout << "Press any key to continue";
                    cin >> contin;
                    continue;
                }

            
                // Deduct transfer amount 
                deductBalance(balances[index], transferAmount);

                // Deduct fee
                deductBalance(balances[index], fee);

                // Add money to recipient
                balances[receptantIndex] += transferAmount;


                transactionTypes.push_back("Tranfer");
                transactionAmounts.push_back(transferAmount);
                transactionFees.push_back(fee);
                transactionQuantities.push_back(1);
                owner.push_back(index);
                time.push_back(getTime()); 


                cout << "=============================== \n";
                cout << "\nTransfer Successful!\n";
                cout << "Transferred: PHP " << transferAmount << endl;
                cout << "Transfer Fee: PHP " << fee << endl;
                cout << "Remaining Balance: PHP " << balances[index] << endl;
                cout << "=============================== \n";
                cout << "Press any key to continue: "; 
                cin >> contin;
                clearScreen();

            }
            else if(choice == 4){
                transactionHistory(transactionTypes, transactionAmounts, transactionFees, transactionQuantities, time, owner, index, bankNames, accountTypes);
            }
            else if(choice == 5){
                clearScreen();
                string current;
                string newPin;
                string input;

                cout << "\n=========== CHANGE PIN ==========\n";
                cout << "Date & Time: " << getTime() << "\n";
                cout << "  Bank: " << bankNames[index] << "      Type: " << accountTypes[index] << endl;

                cout << "----------------------------------------\n";

                cout << "Enter Current Pin: ";
                cin >> current;

                if(current != encodedPINs[index]){
                    cout << "Incorrect Pin \n";
                    cout << "Press any key to continue \n";
                    cin >> current;
                    continue;
                }
                else{
                    cout << "Enter New Pin: ";
                    cin >> newPin;

                    if(newPin.size() != 6){
                        cout << "New pin must contain 6 numbers. \n";
                        cout << "Press any key to continue \n";
                        cin >> input;
                        continue;
                    }

                    encodedPINs[index] = newPin;
                    cout << "Successfully changed pin \n";
                    cout << "Press any key to continue \n";
                    cin >> input;
                    continue;
                }
            }                
        }while(choice != 6);
    }  


void adminMenu(vector<string>& cardNumbers, vector<string>& encodedPINs, 
               vector<double>& balances, vector<string>& userBanks, 
               vector<string>& accountTypes, int billCount[], string& adminPasscode) {
        
    clearScreen();
    string inputPass;
    int attempts = 0;

    // Part III: Admin Authentication (Max 3 attempts)
    while (attempts < 3) {
        cout << "Enter Admin Passcode: ";
        cin >> inputPass;
       if (inputPass == adminPasscode) {
        break; // Success! Jump out of this loop and show the menu
    }
        attempts++;
        cout << "Incorrect. Attempts left: " << 3 - attempts << endl;
        if (attempts == 3) {
            cout << "System Locked. Returning to main menu...\n";
            return;
        }
        }
   int choice;
    string contin;
    do {
        clearScreen();
        cout << "======= ADMIN DASHBOARD =======\n";
        cout << "Time: " << getTime() << endl;
        cout << "[1] Cash Management (Refill)\n";
        cout << "[2] Create New Account\n";
        cout << "[3] View All Accounts\n";
        cout << "[4] Delete Account\n";
        cout << "[5] Change Admin Passcode\n";
        cout << "[6] Logout\n";
        cout << "-------------------------------\nChoice: ";
        cin >> choice;

        if (choice == 1) { // Part 3: Machine Refilling with ctime
            time_t now = time(0);
            tm* localTime = localtime(&now);
            // Maintenance window: 8:00 - 8:15 AM
            if (localTime->tm_hour == 8 && localTime->tm_min <= 15) {
                billCount[0] += 100; // Add 500s
                billCount[1] += 100; // Add 1000s
                cout << "Refill successful (Maintenance Window Active).\n";
            } else {
                cout << "REFILL DENIED: Maintenance is only 8:00 AM - 8:15 AM.\n";
            }
            cin.ignore(); getline(cin, contin);
        }
        else if (choice == 2) { // Account Creation
            string newCard, newPin, newBank, newType;
            cout << "Enter Card Number: "; cin >> newCard;
            cout << "Enter PIN: "; cin >> newPin;
            cout << "Enter Bank (BDO/BPI/etc): "; cin >> newBank;
            cout << "Enter Type (Local/Intl): "; cin >> newType;
    
            cardNumbers.push_back(newCard);
            encodedPINs.push_back(newPin); // In a real version, use your encode function here
            balances.push_back(0.0);
            userBanks.push_back(newBank);
            accountTypes.push_back(newType);
            cout << "Account created!\n";
            cin.ignore(); getline(cin, contin);
        }
        else if (choice == 3) { // View All
            for(int i=0; i < cardNumbers.size(); i++) {
                cout << i+1 << ". Card: " << cardNumbers[i] << " | Bal: " << balances[i] << " | Bank: " << userBanks[i] << endl;
            }
            cout << "Press Enter to continue...";
            cin.ignore(); getline(cin, contin);
        }
    } while (choice != 6);
}

int main(){
    string adminPasscode = "6767";
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


   vector<string> encodedPINs = {encodeString("123456"), encodeString("654321")}; 
    // Encoded passwords


    vector<double> balances = {70000, 85000};        
    // Account balances


    vector<string> userBanks = {"BDO", "BPI"};        
    // Which bank


    vector<string> accountTypes = {"Local", "Local"};    
    // "Local" or "International"

    // For each account's transaction history
    vector<string> transactionTypes;    

    // "Withdrawal", "Deposit", "Transfer"
    vector<double> transactionAmounts;
    vector<double> transactionFees;
    vector<int> transactionQuantities;
    vector <string> time;

    vector <int> owner;

     while(true) {
        int role = login();
        if(role == 1) {
            clientMenu(card, cardNumbers, encodedPINs, balances, userBanks, billCount, localFees, bankNames, accountTypes, 
                intlFees, dailyLimits, transactionTypes, transactionAmounts,  transactionFees, transactionQuantities, time, owner);
        } 
        else if(role == 2) {
            // Pass the vectors by reference so admin changes affect the system
            adminMenu(cardNumbers, encodedPINs, balances, userBanks, accountTypes, billCount, adminPasscode);
        }
        else if(role == 0) {
            cout << "Exiting ATM...\n";
            break; 
        }
    }

    
    return 0;
}

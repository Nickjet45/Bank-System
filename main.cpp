#include <iostream>
#include <string>
#include <fstream>

class BankSystem{
    public:
        //Declaration of member functions
        std::string outputName();
        void getName();
        void depositMoney(int amountToDeposit);
        void withdrawMoney(int amountToWithdraw);
        void import(std::ifstream& inStream);
        bool setStatus(int PIN, std::string userName);
        bool isUser(int PIN, std::string userName);
        double getBalance();
    
    private:
        std::string userName;
        long int currentBalance = 0; //Initalizes at zero, long int incase they wish to store a large amount of money
        bool isDeleted = false; //Checks to see if the user has wished to delete their account
        int PIN;
};

//Returns the username of the object
std::string BankSystem::outputName(){
    return userName;
}

//Retrieves the username from standard input and stores it into the string userName
void BankSystem::getName(){

    std::cin.ignore();
    std::cout << "What is your name? ";
    getline(std::cin, userName);

    //Prompts the user for their special PIN
    std::cout << "Please enter what you wish for your special PIN to be: ";
    std::cin >> PIN;
}

//Increases the object's currentBalance based off of the number passed through
void BankSystem::depositMoney(int amountToDeposit){
    if(amountToDeposit < 0){
        std::cout << "You have entered an invalid amount";
    }
    else{
        currentBalance += amountToDeposit;
        std::cout << "Sucessfully deposited into your account";
    }


}

//Decreases the object's currentBalance based off of the amount passed into the function
void BankSystem::withdrawMoney(int amountToWithdraw){

    if((currentBalance - amountToWithdraw) < 0){
        std::cout << "The amount you have entered would put your balance in the negative, please enter a valid amount \n";
    }
    else{
        currentBalance -= amountToWithdraw;
        std::cout << "You have successfully withdrawn: $" << amountToWithdraw << std::endl;
    }
}

void BankSystem::import(std::ifstream& inStream){
    inStream >> isDeleted;

    if(isDeleted){
        std::string null;
        inStream >> null >> null >> null;
    }
    else{
        std::string firstName, lastName;
        inStream >> firstName >> lastName;

        userName = firstName + " " + lastName;

        inStream >> currentBalance >> PIN;
    }
}

bool BankSystem::setStatus(int enteredPIN, std::string enteredUserName){
    if((enteredPIN == PIN) && (enteredUserName == userName)){
        isDeleted = true;

        std::cout << "Your account has been set to be deleted, sorry to see you go \n";

        return true;
    }
    else{

        std::cout << "Either the PIN or username you have entered is incorrect."
                  << "Therefore, we are unable to delete your account \n";
        return false;
    }
}

//Adjusted system to verify that the user is within the system, which will make it easier to prompt the user
bool BankSystem:: isUser(int enteredPIN, std::string enteredName){
    if((enteredPIN == PIN) && (enteredName == userName)){
        return true;
    }
    else{
        return false;
    }
}

double BankSystem:: getBalance(){
    return currentBalance;
}

int menu(){
    int userChoice = 0;

    std::cout << "Please enter your choice: \n"
              << "1- Create Account \n"
              << "2- Login to Account \n"
              << "3- Deposit Money \n"
              << "4- Withdraw Money \n"
              << "5- Delete Account \n";
              std::cin >> userChoice;

    return userChoice;
}

//Opens the input file(checks to see if the program needs to import X amount of users)
void openInput(std::ifstream& inStream){
    inStream.open("BankBackup.txt");

    if(inStream.fail()){
        std::cout << "Failed to open backup file, exiting program";
        exit(1);
    }

}

//Opens the output file(same as input) and sets the pointer to be towards the end of the program
void openOutput(std::ofstream& outStream){
    outStream.open("Bankbackup.txt", std::ofstream::app);

    if(outStream.fail()){
        std::cout << "Failed to generate backup file, exiting program";
        exit(1);
    }
    outStream.seekp(0, outStream.end);
    long size = outStream.tellp();
    outStream.seekp(size);
}



int main(){
    std::ifstream inStream;
    std::ofstream outStream;
    std::string userName;
    int numOfusers, PIN, userChoice, userNumber = -1; //Sets the user number to -1 to see if the user has logined yet
    char rerun = 'Y';
    bool hasDeleted = false;

    BankSystem *system; //Creation of pointer to allow dynamic array of the system

    //Opens the input and output stream
    openInput(inStream);
    openOutput(outStream);

    //Reads in the number of users from the input file to determine if the program needs to fill objects before continuing
    inStream >> numOfusers;

    //Creates an array of BankSystems whose size is the imported number of users + 20
    int sizeOfArray = numOfusers + 20;
    system = new BankSystem[sizeOfArray];

    for(int i = 0; i < numOfusers; i++){
        system[i].import(inStream); //Imports the required data from the input file
    }

    //After the program has imported the nessecary users, ask what the user would like to do
    while(toupper(rerun) != 'N'){
        userChoice = menu();
        switch(userChoice){
            case 1:
                system[numOfusers + 1].getName();
                numOfusers++;
                break;
            case 2:
                //Prompts the user for their PIN and user name

                std::cin.ignore();

                std::cout << "What is your user name? ";
                getline(std::cin, userName);

                std::cout << "What is your PIN? ";
                std::cin >> PIN;

                //Loops over the size of the array, and if the user's PIN and userName is found to match, 
                //their number is the index of array at i
                for(int i = 0; i < sizeOfArray; i++){
                    if(system[i].isUser(PIN, userName)){
                        userNumber = i;
                        std::cout << "Successfully logined to the system, please continue \n";
                        break;
                    }
                }

                break;
            case 3:
                if(userNumber == -1){ //If user has yet to login, tell them to go login
                    std::cout << "Please login first \n";
                    break;
                }

                //Prompt for the amount they wish to deposit into their account
                double amountD;
                std::cout << "How much would you like to deposit into your account? $";
                std::cin >> amountD;
                
                system[userNumber].depositMoney(amountD);
                break;

            case 4:
                if(userNumber == -1){
                    std::cout << "Please login first \n";
                    break;
                }

                //Prompt for amount the user wishes to withdraw from their account, after telling them how much they have in their account
                std::cout << "Your current account balance is: $" << system[userNumber].getBalance() << std::endl;
                double amountW;
                std::cout << "How much would you like to withdraw from your account? $";
                std::cin >> amountW;
                
                system[userNumber].withdrawMoney(amountW);
                break;

            case 5: //If the user chooses to delete their account
                if(userNumber == -1){
                    std::cout << "Please login first \n";
                    break;
                }

                //Asks the user for their name
                std::cin.ignore();
                std::cout << "Please enter your name: ";
                getline(std::cin, userName);

                //Prompt the user for their pin
                std::cout << "Please enter your special PIN code: ";
                std::cin >> PIN;
                //Deletes the account the user logined to earlier
                system[userNumber].setStatus(PIN, userName);

                break;

            default:
                std::cout << "Invalid user choice, exiting the program";
                exit(1);
        }

        std::cout << "Would you like to rerun the program? [Y/N]";
        std:: cin >> rerun;
    }


}
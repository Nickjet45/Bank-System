#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include "Banking.hpp"

int menu(){
    int userChoice = 0;

    std::cout << "Please enter your choice: \n"
              << "1- Create Account \n"
              << "2- Login to Account \n"
              << "3- Deposit Money \n"
              << "4- Withdraw Money \n"
              << "5- Delete Account \n"
              << "6- Exit Program \n";
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
    //Opens the output file
    outStream.open("Bankbackup.txt");

    if(outStream.fail()){
        std::cout << "Failed to generate backup file, exiting program";
        exit(1);
    }
}

int main(){
    std::ifstream inStream;
    std::ofstream outStream;
    std::string userName;
    int numOfusers=0, PIN, userChoice, userNumber = -1; //Sets the user number to -1 to see if the user has logined yet
    char rerun = 'Y';
    bool hasDeleted = false;

    BankSystem *system; //Creation of pointer to allow dynamic array of the system

    //Opens the input  stream
    openInput(inStream);

    //Reads in the number of users from the input file to determine if the program needs to fill objects before continuing
    inStream >> numOfusers;

    //Creates an array of BankSystems whose size is the imported number of users + 20
    int sizeOfArray = numOfusers + 20;
    system = new BankSystem[sizeOfArray];

    for(int i = 0; i < numOfusers; i++){
        system[i].import(inStream); //Imports the required data from the input file
    }

    //After the program has imported the nessecary users, ask what the user would like to do
    //While the user has not chosen to exit the program
    while(true){
        userChoice = menu();
        switch(userChoice){
            case 1:
                //Access the array with the index of number of users, as the array will be empty at number of users
                //Since an array starts at 0
                system[numOfusers].getName();

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

                    //If the program has looped over the entire size of the array, and the program has been unable to successfully log the user in
                    //Then the user has entered an invalid credential and should be notified

                    if(i==(sizeOfArray -1))
                        std::cout << "You have entered an invalid user name or PIN code, please try again \n";
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

                //Asks the user for their name
                std::cin.ignore();
                std::cout << "Please enter your name: ";
                getline(std::cin, userName);

                //Prompt the user for their pin
                std::cout << "Please enter your special PIN code: ";
                std::cin >> PIN;

                //Deletes the account the user logined to earlier
                system[userNumber].setStatus(PIN, userName);

                //Lowers the number of users in the system by 1, due to an account being deleted

                numOfusers--;

                break;
            
            case 6: //If the user chooses to exit the program
                //Send a good bye message, export data to binary file, delete all pointers, and then exit the program
                std::cout << "Thank you for using our system, good bye \n";

                std::cout << "Storing user information... \n";

                //Opens the output file, to prepare the program to write to it

                openOutput(outStream);

                //Output the number of users currently in the system to the output file
                outStream << numOfusers << std::endl;


                //Loop over the number of users and then output all of their information if they have not been set to be deleted

                for(int i = 0; i < numOfusers; i++){
                    system[i].exportUser(outStream);
                } 

                delete[] system;

                exit(1);
            default:
                std::cout << "Invalid user choice, exiting the program";

                delete[] system;
                
                exit(1);
        }

    }


}
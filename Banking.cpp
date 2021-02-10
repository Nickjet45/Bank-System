#include "Banking.hpp"
#include <iostream>
#include <fstream>
#include <string>

//Returns the username of the object
std::string BankSystem::outputName(){
    return userName;
}

//Retrieves the username from standard input and stores it into the string userName
void BankSystem::getName(){
    std::cin.ignore();
    std::cout << "What is your name? ";

    //Stores the user's firstName and lastName into their respective variables
    std::cin >> firstName >> lastName;

    //The username is the combination of the first name and their last name, with a space separating them
    userName = firstName + " " + lastName;

    //Prompts the user for their special PIN
    std::cout << "Please enter what you wish for your special PIN to be: ";
    std::cin >> PIN;
}

//Increases the object's currentBalance based off of the number passed through
void BankSystem::depositMoney(int amountToDeposit){
    if(amountToDeposit < 0)
        std::cout << "You have entered an invalid amount \n";
    else{
        currentBalance += amountToDeposit;
        std::cout << "Sucessfully deposited into your account \n";
    }


}

//Decreases the object's currentBalance based off of the amount passed into the function
void BankSystem::withdrawMoney(int amountToWithdraw){
    int withdrawAmount = amountToWithdraw;

    //While the user has yet to entered an invalid amount, loop over until they enter a valid amount
    while(true){
        if((currentBalance - withdrawAmount) < 0){
            std::cout << "The amount you have entered would put your balance in the negative, please enter a valid amount \n";
            std::cout << "How much would you like to withdraw? ";
            std::cin >> withdrawAmount;
        }
        //Once a valid amount has been entered, subtract it from their current balance and log a message to console, then break the loop
        else{
            currentBalance -= withdrawAmount;
            std::cout << "You have successfully withdrawn: $" << withdrawAmount << std::endl;
            break;
        }
    }
}

void BankSystem::import(std::ifstream& inStream){

    //Imports the user's information
    inStream >> firstName >> lastName >> PIN >> currentBalance;

    //Sets the user name to be equal to the first name + the last name, with a space inbetween
    userName = firstName + " " + lastName;
}

void BankSystem::exportUser(std::ofstream& outStream){

    //If the user has set to be deleted ,do not store their information into the output file
    if(isDeleted) return;
    else{

        //Else store the information into the output file, in this order
        outStream << firstName << " " << lastName << std::endl;
        outStream << PIN << " "<< currentBalance << std::endl;
    }
}

bool BankSystem::setStatus(int enteredPIN, std::string enteredUserName){
    //If the entered PIN and username is correct, set the user account to be deleted
    //Else tell the user they have entered an invalid credential
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
    //If the entered PIN and username matches the current user being indexed, the user has successfully logined
    //Else they have yet to login
    if((enteredPIN == PIN) && (enteredName == userName)) return true;
    else return false;
}

double BankSystem:: getBalance(){
    return currentBalance;
}
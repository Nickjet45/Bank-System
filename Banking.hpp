#ifndef BANKING
#define BANKING
#include <fstream>
#include <string>

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
        void exportUser(std::ofstream& inStream);
    
    private:
        std::string userName, firstName, lastName;
        long double currentBalance = 0; //Initalizes at zero, long double incase they wish to store a large amount of money
        bool isDeleted = false; //Checks to see if the user has wished to delete their account
        int PIN;
};

#endif
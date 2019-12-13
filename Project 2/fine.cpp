//
//  fine.cpp
//  Proj2
//
//  Created by David Deng on 10/10/19.
//  Copyright © 2019 David Deng. All rights reserved.
//  UID: 305382790

#include <iostream>
#include <string>
using namespace std;

int main() {
    //constant values
    const double smallFine = 0.66; //the amount fined for payment up to 40k to Stinger
    const double largeFine = 0.14; //the amount fined for payment above 250k to Stinger
    const int smallFineMax = 40; //up to 40k is the max amount to give small fine
    const int mediumFineMax = 250; //from 40k up to 250k is the max amount to give medium fine

    //values that change in the program
    double mediumFine; //the amount fined for payment from 40k to 250k to Stinger
    double fine = 20; //every fine starts at 20k minimum

    //values that take input
    string defendantName;
    double amountPaid;
    string athlete;

    cout << "Defendant: ";
    getline(cin, defendantName);
    cout << "Amount paid (in thousands): ";
    cin >> amountPaid;
    cin.ignore(100000, '\n');
    cout << "Fake athlete? (y/n): ";
    getline(cin, athlete);
    cout << "---" << endl;

    if (defendantName.empty()) {
        cout << "You must enter a defendant name." << endl;
        return 1;
    }
    else if (amountPaid < 0) {
        cout << "The amount paid must not be negative." << endl;
        return 1;
    }
    else if (athlete != "y" && athlete != "n") {
        cout << "You must enter y or n." << endl;
        return 1;
    }
    else {
        if (athlete == "y") {
            mediumFine = 0.22; //fine is 22% if athlete status is yes
        }
        else {
            mediumFine = 0.10; //if it's no, then the fine is 10%
        }

        if (amountPaid <= smallFineMax) {
            fine = fine + amountPaid * smallFine; //all payment is subject to small fine
        }
        else {
            if (amountPaid <= mediumFineMax) {
                fine = fine + (smallFineMax * smallFine) + ((amountPaid - smallFineMax) * mediumFine); //maximum small fine payment, medium fine payment varies based on amountPaid
            }
            else {
                fine = fine + (smallFineMax * smallFine) + ((mediumFineMax - smallFineMax) * mediumFine) + ((amountPaid - mediumFineMax) * largeFine); //maximum small and medium fine payment, large fine payment varies based on amountPaid
            }
        }
        cout.setf(ios::fixed);
        cout.precision(1);
        cout << "The suggested fine for " << defendantName << " is $" << fine << " thousand." << endl;
    }
    return 0;
}

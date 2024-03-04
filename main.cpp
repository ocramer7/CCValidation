/* Owen Cramer
 * FRCC CSC2034
 * February, 12 2023
 * Program used the Hans Luhn's algorithm to validate a credit card number.
 */

#include <iostream>
using namespace std;

/*
* A program using Hans Luhn's algorithm to validate a c/c number.
*/

// Header functions

// return true if the argument is a valid card number
bool isValid(unsigned long int);

// get the result from step 2
int sumOfDoubleEvenPlace(unsigned long int number);

/* return this number if argument is a single digit, otherwise
 * return the sum of the two digit argument
 */
int getDigit(int);

// return sum of odd placed digits in argument
int sumOfOddPlace(unsigned long int);

// return true if prefix d is a prefix for number
bool prefixMatched(unsigned long int number, int d);

// return the number of digits in argument
int getSize(unsigned long int);

/* return the first k number of digits from number.  If the
 * number of digits in number is less than k, return number.
 */
unsigned long int getPrefix(unsigned long int number, int k);

int main() {
    unsigned long long int ccNum;// = 4388576018410707; //4388576018410707--is valid; 4388576018402626--is invalid ;
    char input;
    do { // Loops until the user enters 'n'
        cout << "Enter a credit card number: ";
        cin >> ccNum;
        cout << ccNum << " is " << (isValid(ccNum) ? "a valid credit card number.\n" : "an invalid credit card number.\n");

        if (isValid(ccNum)) { // Checks if card is valid and returns what card manufacturer it was from.
            if (prefixMatched(ccNum, 4)) cout << "VISA" << endl;
            else if (prefixMatched(ccNum, 5)) cout << "MASTERCARD" << endl;
            else if (prefixMatched(ccNum, 37)) cout << "AMERICAN EXPRESS" << endl;
            else if (prefixMatched(ccNum, 6)) cout << "DISCOVER" << endl;
            else cout << "Unknown credit card manufacturer" << endl;
        } else {
            cout << "INVALID" << endl;
        }

        cout << "Enter another number? (type 'n' to stop) [y|n]: ";
        cin >> input;
    } while (input != 'n');


}

bool isValid(unsigned long int num) { // Returns if the entered credit card number is valid
    return (getSize(num) >= 13 && getSize(num) <= 16) && (prefixMatched(num, 4) || prefixMatched(num, 5) ||
            prefixMatched(num, 37) || prefixMatched(num, 6)) && ((sumOfDoubleEvenPlace(num) +
            sumOfOddPlace(num)) % 10 == 0);
}
int sumOfDoubleEvenPlace(unsigned long int number) { // Double every second digit from right to left
    int sum = 0;
    string num = to_string(number);
    for (int i = getSize(number) - 2; i >= 0; i -= 2) {
        sum += getDigit(int(num[i] - '0') * 2);
    }
    return sum;
}

int getDigit(int number) { // Return credit card number from dividing and MOD 10
    if (number < 9)
        return number;
    return number / 10 + number % 10;
}

int sumOfOddPlace(unsigned long int number) { // Add all digits in the odd places from right to left
    int sum = 0;
    string num = to_string(number);
    for (int i = getSize(number) - 1; i >= 0; i -= 2) {
        sum += num[i] - '0';
    }
    return sum;
}

bool prefixMatched(unsigned long int number, int d) { // Return the beginning digit.
    return getPrefix(number, getSize(d)) == d;
}

int getSize(unsigned long int d) { // Get the size of the credit card number (e.i. 16 digits)
    string num = to_string(d);
    return num.length();
}

unsigned long int getPrefix(unsigned long int number, int k) { // Get first digit to evaluate from what manufacturer.
    if (getSize(number) > k) {
        string num = to_string(number);
        return stol(num.substr(0,k));
    }
    return number;
}
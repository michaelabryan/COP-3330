/*Name: Michael Bryan
Date : June 19, 2017
Section : 1
Assignment : HW #3
Due Date : June 18, 2018 */

//-------------------------mixed.h--------------------
#include <iostream>
using namespace std;

class Mixed
{
	//
	//Operator Overload Functions
	//     VVVVVVVVVVVVVVV

	//Stream Manipulators
	friend istream& operator>>(istream& in, Mixed& numNum);
	friend ostream& operator<<(ostream& out, const Mixed& numNum);

	//Comparison Checkers
	friend bool operator<(const Mixed& num1, const Mixed& num2);
	friend bool operator<=(const Mixed& num1, const Mixed& num2);
	friend bool operator>(const Mixed& num1, const Mixed& num2);
	friend bool operator>=(const Mixed& num1, const Mixed& num2);
	friend bool operator==(const Mixed& num1, const Mixed& num2);
	friend bool operator!=(const Mixed& num1, const Mixed& num2);

	//Arithmetic Operations
	friend Mixed operator+(const Mixed& num1, const Mixed& num2);
	friend Mixed operator-(const Mixed& num1, const Mixed& num2);
	friend Mixed operator*(const Mixed& num1, const Mixed& num2);
	friend Mixed operator/(const Mixed& num1, const Mixed& num2);
	
public:

	//Constructors
	Mixed(int wN=0);
	Mixed(int whole, int n, int d);

	//Member Functions
	double Evaluate();		//
	void ToFraction();		//Mutator functions
	void Simplify();		//

	int getwholeNum() const;		//
	int getNumerator() const;		//Accesor Functions
	int getDenominator() const;		//

	//
	//  Operator Overload Functions
	//     VVVVVVVVVVVVVVV

	//Incrementors/Decrementors
	Mixed& operator++();
	Mixed operator++(int);
	Mixed& operator--();
	Mixed operator--(int);



private:

	//Data members
	int wholeNum;
	int numerator;
	int denominator;
	static bool isNegative;


	//Helper functions
	void negFlipper(int wn, int n);
	bool negChecker(int numNum);
};

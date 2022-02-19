/*Name: Michael Bryan
Date : June 19, 2017
Section : 1
Assignment : HW #3
Due Date : June 18, 2018 */

//-------------------------mixed.cpp--------------------
#include "mixed.h"
#include <iomanip>

Mixed::Mixed(int wN)
{
	wholeNum = wN;
	numerator = 0;
	denominator = 1;

}

Mixed::Mixed(int whole, int n, int d)
{
	if ((negChecker(whole) == true && negChecker(n) == true) || (negChecker(d) == true) || (wholeNum > 0 && negChecker(n)))
	{
		wholeNum = 0;
		numerator = 0;
		denominator = 1;
	}
	else
	{
		
		if (whole < 0)
			wholeNum = whole * (-1);
		else
			wholeNum = whole;
		if (n < 0)
			numerator = n * (-1);
		else
			numerator = n;

		denominator = d;
	}
 
    Simplify();

}

bool Mixed::isNegative = NULL;

double Mixed::Evaluate()
{
	cout << setprecision(3);
	double decimalNum = (denominator * wholeNum + numerator)/(denominator*(1.0));
	if (isNegative == true)
		decimalNum = decimalNum * (-1);

	return decimalNum;
}

void Mixed::ToFraction()
{
	numerator = wholeNum * denominator + numerator;
	wholeNum = 0;	
}

void Mixed::Simplify()
{

	//This block of code changes any improper fraction into a proper unreduced mixed fraction
	if (numerator >= denominator && wholeNum == 0)
	{
		for (int i = 1; i < numerator*denominator; i++)
		{
			if (numerator >= denominator)
			{
				numerator -= denominator;
				wholeNum += 1;
			}
			else
				break;
		}
	}
	else if (numerator <= denominator && wholeNum == 0);
	else if (numerator >= denominator && wholeNum != 0)
	{
		for (int i = 1; i < numerator*denominator; i++)
		{
			if (numerator >= denominator)
			{
				numerator -= denominator;
				wholeNum += 1;
			}
			else
				break;
		}
	}


	//This block of code reduces the numerator and denominator to their lowest forms
	for (int i = denominator * numerator; i > 1; i--)
	{
		if (denominator%i == 0 && numerator%i == 0)
		{
			numerator = numerator / i;
			denominator = denominator / i;
		}
	}

}

int Mixed::getwholeNum() const
{
	return wholeNum;
}

int Mixed::getNumerator() const
{
	return numerator;
}

int Mixed::getDenominator() const
{
	return denominator;
}


bool Mixed::negChecker(int numNum)
{
	if (numNum < 0)
		return true;
	else
		return false;
}

void Mixed::negFlipper(int wn, int n)
{
    
	if ((wn < 0 && n>0) || (wn>0 && n<0))
	{
        if(wn < 0)
            isNegative = true;
        else if (n <0)
            isNegative = true;
	}
	else
		isNegative = false;
}



//
//Operator Overload Functions
//

//Incrementors/Decrementors
Mixed & Mixed::operator++() //prefix
{
	if (isNegative == true)
	{
		if (wholeNum == 0)
		{
			numerator = (1 * denominator) - numerator;
			negFlipper(wholeNum,numerator);
		}
		else
			wholeNum = wholeNum - 1;
		return *this;
	}
	else
	{
		wholeNum = wholeNum + 1;
		return *this;
	}
	return *this;
}

Mixed Mixed::operator++(int) //postfix
{
	Mixed temp = *this;
	if (isNegative == true)
	{
		if (wholeNum == 0)
		{
			numerator = (1 * denominator) - numerator;
			negFlipper(wholeNum, numerator);
		}
		else
			wholeNum = wholeNum - 1;
	}
	else
		wholeNum = wholeNum + 1;
	return temp;
}

Mixed & Mixed::operator--() //prefix
{
	if (isNegative == true)
		wholeNum = wholeNum + 1;
	else
	{
		if (wholeNum == 0)
			numerator = (1 * denominator) - numerator;
		else
			wholeNum = wholeNum - 1;
	}
	return *this;
}

Mixed Mixed::operator--(int) //postfix
{
	Mixed temp = *this;

	if (isNegative == true)
	{
		if (wholeNum == 0)
		{
			numerator = (1 * denominator) + numerator;
		}
		else
			wholeNum = wholeNum - 1;
	}
	else
		wholeNum = wholeNum - 1;
	
	Mixed::Simplify();

	return temp;
}


//Stream Manipulators
istream& operator>>(istream & in, Mixed& numNum)
{
	char divSign;

	int tempwholeNum, tempNumerator, tempDenominator;

	in >> tempwholeNum >> tempNumerator >> divSign >> tempDenominator;
	
	Mixed N1(tempwholeNum, tempNumerator, tempDenominator);
	numNum = N1;

	return in;
}

ostream& operator<<(ostream& out,const Mixed& numNum)
{
	if (numNum.wholeNum == 0)
	{
		if (numNum.isNegative)
			out << numNum.wholeNum << ' ' << '-' << numNum.numerator << '/' << numNum.denominator;
		else
			out << numNum.wholeNum << ' ' << numNum.numerator << '/' << numNum.denominator;
	}
	else if (numNum.isNegative)
		out << '-' << numNum.wholeNum << ' ' << numNum.numerator << '/' << numNum.denominator;
	else
		out << numNum.wholeNum << ' ' << numNum.numerator << '/' << numNum.denominator;

	return out;
}


//Comparison Checkers
bool operator<(const Mixed& num1, const Mixed& num2)
{
	int tempNumeratorNum1;
	int tempNumeratorNum2;

	if (num1.wholeNum == 0 && num2.wholeNum == 0)
	{
		tempNumeratorNum1 = num1.numerator * num2.denominator;
		tempNumeratorNum2 = num2.numerator * num1.denominator;

		if (tempNumeratorNum1 < tempNumeratorNum2)
		{
			if (num1.isNegative == false && num2.isNegative == false)
				return true;
			if (num1.isNegative == true && num2.isNegative == false)
				return true;
			if (num1.isNegative == false && num2.isNegative == true)
				return false;
			if (num1.isNegative == true && num2.isNegative == true)
				return false;
		}
		else if (tempNumeratorNum1 >= tempNumeratorNum2)
		{
			if (num1.isNegative == false && num2.isNegative == false)
				return false;
			if (num1.isNegative == true && num2.isNegative == false)
				return true;
			if (num1.isNegative == false && num2.isNegative == true)
				return false;
			if (num1.isNegative == true && num2.isNegative == true)
			{
				if (tempNumeratorNum1 > tempNumeratorNum2)
					return true;
				else if (tempNumeratorNum1 == tempNumeratorNum2)
					return false;
			}
		}
	}
	else if (num1.wholeNum == 0 && num2.wholeNum != 0)
	{
		tempNumeratorNum1 = num1.numerator * num2.denominator;
		tempNumeratorNum2 = num2.denominator*num2.wholeNum + num2.numerator; //Converts mixed number into impromper fraction
		tempNumeratorNum2 = tempNumeratorNum2 * num1.denominator;

		if (tempNumeratorNum1 < tempNumeratorNum2)
		{
			if (num1.isNegative == false && num2.isNegative == false)
				return true;
			if (num1.isNegative == true && num2.isNegative == false)
				return true;
			if (num1.isNegative == false && num2.isNegative == true)
				return false;
			if (num1.isNegative == true && num2.isNegative == true)
				return false;
		}
		else if (tempNumeratorNum1 >= tempNumeratorNum2)
		{
			if (num1.isNegative == false && num2.isNegative == false)
				return false;
			if (num1.isNegative == true && num2.isNegative == false)
				return true;
			if (num1.isNegative == false && num2.isNegative == true)
				return false;
			if (num1.isNegative == true && num2.isNegative == true)
			{
				if (tempNumeratorNum1 > tempNumeratorNum2)
					return true;
				else if (tempNumeratorNum1 == tempNumeratorNum2)
					return false;
			}
		}

	}
	else if (num1.wholeNum != 0 && num2.wholeNum == 0)
	{
		tempNumeratorNum1 = num1.denominator*num1.wholeNum + num1.numerator;
		tempNumeratorNum1 = tempNumeratorNum1 * num2.denominator;
		tempNumeratorNum2 = num2.numerator * num1.denominator;

		if (tempNumeratorNum1 < tempNumeratorNum2)
		{
			if (num1.isNegative == false && num2.isNegative == false)
				return true;
			if (num1.isNegative == true && num2.isNegative == false)
				return true;
			if (num1.isNegative == false && num2.isNegative == true)
				return false;
			if (num1.isNegative == true && num2.isNegative == true)
				return false;
		}
		else if (tempNumeratorNum1 >= tempNumeratorNum2)
		{
			if (num1.isNegative == false && num2.isNegative == false)
				return false;
			if (num1.isNegative == true && num2.isNegative == false)
				return true;
			if (num1.isNegative == false && num2.isNegative == true)
				return false;
			if (num1.isNegative == true && num2.isNegative == true)
			{
				if (tempNumeratorNum1 > tempNumeratorNum2)
					return true;
				else if (tempNumeratorNum1 == tempNumeratorNum2)
					return false;
			}
		}
	}
	else if (num1.wholeNum != 0 && num2.wholeNum != 0)
	{
		tempNumeratorNum1 = num1.denominator*num1.wholeNum + num1.numerator;
		tempNumeratorNum1 = tempNumeratorNum1 * num2.denominator;
		tempNumeratorNum2 = num2.denominator*num2.wholeNum + num2.numerator;
		tempNumeratorNum2 = tempNumeratorNum2 * num1.denominator;

		if (tempNumeratorNum1 < tempNumeratorNum2)
		{
			if (num1.isNegative == false && num2.isNegative == false)
				return true;
			if (num1.isNegative == true && num2.isNegative == false)
				return true;
			if (num1.isNegative == false && num2.isNegative == true)
				return false;
			if (num1.isNegative == true && num2.isNegative == true)
				return false;
		}
		else if (tempNumeratorNum1 >= tempNumeratorNum2)
		{
			if (num1.isNegative == false && num2.isNegative == false)
				return false;
			if (num1.isNegative == true && num2.isNegative == false)
				return true;
			if (num1.isNegative == false && num2.isNegative == true)
				return false;
			if (num1.isNegative == true && num2.isNegative == true)
			{
				if (tempNumeratorNum1 > tempNumeratorNum2)
					return true;
				else if (tempNumeratorNum1 == tempNumeratorNum2)
					return false;
			}
		}
	}





	return false;
}

bool operator<=(const Mixed& num1, const Mixed& num2)
{
	if (operator>(num1, num2) == true)
		return false;
	else
		return true;
}

bool operator>(const Mixed& num1, const Mixed& num2)
{
	int tempNumeratorNum1;
	int tempNumeratorNum2;

	if (num1.wholeNum == 0 && num2.wholeNum == 0)
	{
		tempNumeratorNum1 = num1.numerator * num2.denominator;
		tempNumeratorNum2 = num2.numerator * num1.denominator;

		if (tempNumeratorNum1 > tempNumeratorNum2)
		{
			if (num1.isNegative == false && num2.isNegative == false)
				return true;
			if (num1.isNegative == true && num2.isNegative == false)
				return false;
			if (num1.isNegative == false && num2.isNegative == true)
				return true;
			if (num1.isNegative == true && num2.isNegative == true)
				return false;
		}
		else if (tempNumeratorNum1 <= tempNumeratorNum2)
		{
			if (num1.isNegative == false && num2.isNegative == false)
				return false;
			if (num1.isNegative == true && num2.isNegative == false)
				return false;
			if (num1.isNegative == false && num2.isNegative == true)
				return true;
			if (num1.isNegative == true && num2.isNegative == true)
			{
				if (tempNumeratorNum1 < tempNumeratorNum2)
					return true;
				else if (tempNumeratorNum1 == tempNumeratorNum2)
					return false;
			}
		}
	}
	else if (num1.wholeNum == 0 && num2.wholeNum != 0)
	{
		tempNumeratorNum1 = num1.numerator * num2.denominator;
		tempNumeratorNum2 = num2.denominator*num2.wholeNum + num2.numerator; //Converts mixed number into impromper fraction
		tempNumeratorNum2 = tempNumeratorNum2 * num1.denominator;

		if (tempNumeratorNum1 > tempNumeratorNum2)
		{
			if (num1.isNegative == false && num2.isNegative == false)
				return true;
			if (num1.isNegative == true && num2.isNegative == false)
				return false;
			if (num1.isNegative == false && num2.isNegative == true)
				return true;
			if (num1.isNegative == true && num2.isNegative == true)
				return false;
		}
		else if (tempNumeratorNum1 <= tempNumeratorNum2)
		{
			if (num1.isNegative == false && num2.isNegative == false)
				return false;
			if (num1.isNegative == true && num2.isNegative == false)
				return false;
			if (num1.isNegative == false && num2.isNegative == true)
				return true;
			if (num1.isNegative == true && num2.isNegative == true)
			{
				if (tempNumeratorNum1 < tempNumeratorNum2)
					return true;
				else if (tempNumeratorNum1 == tempNumeratorNum2)
					return false;
			}
		}
	}
	else if (num1.wholeNum != 0 && num2.wholeNum == 0)
	{
		tempNumeratorNum1 = num1.denominator*num1.wholeNum + num1.numerator;
		tempNumeratorNum1 = tempNumeratorNum1 * num2.denominator;
		tempNumeratorNum2 = num2.numerator * num1.denominator;

		if (tempNumeratorNum1 > tempNumeratorNum2)
		{
			if (num1.isNegative == false && num2.isNegative == false)
				return true;
			if (num1.isNegative == true && num2.isNegative == false)
				return false;
			if (num1.isNegative == false && num2.isNegative == true)
				return true;
			if (num1.isNegative == true && num2.isNegative == true)
				return false;
		}
		else if (tempNumeratorNum1 <= tempNumeratorNum2)
		{
			if (num1.isNegative == false && num2.isNegative == false)
				return false;
			if (num1.isNegative == true && num2.isNegative == false)
				return false;
			if (num1.isNegative == false && num2.isNegative == true)
				return true;
			if (num1.isNegative == true && num2.isNegative == true)
			{
				if (tempNumeratorNum1 < tempNumeratorNum2)
					return true;
				else if (tempNumeratorNum1 == tempNumeratorNum2)
					return false;
			}
		}
	}
	else if (num1.wholeNum != 0 && num2.wholeNum != 0) // Not done yet
	{
		tempNumeratorNum1 = num1.denominator*num1.wholeNum + num1.numerator;
		tempNumeratorNum1 = tempNumeratorNum1 * num2.denominator;
		tempNumeratorNum2 = num2.denominator*num2.wholeNum + num2.numerator;
		tempNumeratorNum2 = tempNumeratorNum2 * num1.denominator;

		if (tempNumeratorNum1 > tempNumeratorNum2)
		{
			if (num1.isNegative == false && num2.isNegative == false)
				return true;
			if (num1.isNegative == true && num2.isNegative == false)
				return false;
			if (num1.isNegative == false && num2.isNegative == true)
				return true;
			if (num1.isNegative == true && num2.isNegative == true)
				return false;
		}
		else if (tempNumeratorNum1 <= tempNumeratorNum2)
		{
			if (num1.isNegative == false && num2.isNegative == false)
				return false;
			if (num1.isNegative == true && num2.isNegative == false)
				return false;
			if (num1.isNegative == false && num2.isNegative == true)
				return true;
			if (num1.isNegative == true && num2.isNegative == true)
			{
				if (tempNumeratorNum1 < tempNumeratorNum2)
					return true;
				else if (tempNumeratorNum1 == tempNumeratorNum2)
					return false;
			}
		}
	}





	return false;
}

bool operator>=(const Mixed& num1, const Mixed& num2)
{
	if (operator<(num1, num2) == true)
		return false;
	else
		return true;
}

bool operator==(const Mixed& num1, const Mixed& num2)
{
	int tempNumeratorNum1;
	int tempNumeratorNum2;

	tempNumeratorNum1 = num1.denominator*num1.wholeNum + num1.numerator;
	tempNumeratorNum1 = tempNumeratorNum1 * num2.denominator;
	tempNumeratorNum2 = num2.denominator*num2.wholeNum + num2.numerator;
	tempNumeratorNum2 = tempNumeratorNum2 * num1.denominator;

	if (num1.isNegative == false && num2.isNegative == false)
	{
		if (tempNumeratorNum1 == tempNumeratorNum2)
			return true;
	}
	if (num1.isNegative == true && num2.isNegative == false)
	{
		if (tempNumeratorNum1 == tempNumeratorNum2)
			return false;
	}
	if (num1.isNegative == false && num2.isNegative == true)
	{
		if (tempNumeratorNum1 == tempNumeratorNum2)
			return false;
	}
	if (num1.isNegative == true && num2.isNegative == true)
	{
		if (tempNumeratorNum1 == tempNumeratorNum2)
			return true;
	}

	return false;
}

bool operator!=(const Mixed& num1, const Mixed& num2)
{
	if (operator==(num1, num2) == true)
		return false;
	else
		return true;
}


//Arithmetic Operations
Mixed operator+(const Mixed& num1, const Mixed& num2)
{
	Mixed M;

	int tempNumeratorNum1;
	int tempNumeratorNum2;
	int tempDenominatorNum;

	tempNumeratorNum1 = num1.denominator*num1.wholeNum + num1.numerator;
	tempNumeratorNum1 = tempNumeratorNum1 * num2.denominator;
	tempNumeratorNum2 = num2.denominator*num2.wholeNum + num2.numerator;
	tempNumeratorNum2 = tempNumeratorNum2 * num1.denominator;
	tempDenominatorNum = num1.denominator*num2.denominator;

	if (num1.isNegative == false && num2.isNegative == false)
	{
		Mixed N1(0, tempNumeratorNum1 + tempNumeratorNum2, tempDenominatorNum);
		M = N1;
	}
	if (num1.isNegative == true && num2.isNegative == false)
	{
		if (num1 > num2)
		{
			Mixed N1(0, tempNumeratorNum1 - tempNumeratorNum2, tempDenominatorNum);
			M = N1;
		}
		else if (num1 <= num2)
		{
			if (num1 < num2)
			{
				Mixed N1(0, tempNumeratorNum2 - tempNumeratorNum1, tempDenominatorNum);
				M = N1;
			}
			else if (num1 == num2)
			{
				Mixed N1(0, tempNumeratorNum2 - tempNumeratorNum1, tempDenominatorNum);
				M = N1;
			}
		}
	}
	if (num1.isNegative == false && num2.isNegative == true)
	{
		if (num1 > num2)
		{
			Mixed N1(0, tempNumeratorNum1 - tempNumeratorNum2, tempDenominatorNum);
			M = N1;
		}
		else if (num1 <= num2)
		{
			if (num1 < num2)
			{
				Mixed N1(0, tempNumeratorNum2 - tempNumeratorNum1, tempDenominatorNum);
				M = N1;
			}
			else if (num1 == num2)
			{
				Mixed N1(0, tempNumeratorNum2 - tempNumeratorNum1, tempDenominatorNum);
				M = N1;
			}
		}
	}
	if (num1.isNegative == true && num2.isNegative == true)
	{
		Mixed N1(0, tempNumeratorNum1 + tempNumeratorNum2, tempDenominatorNum);
		M = N1;
	}

	return M;
}

Mixed operator-(const Mixed& num1, const Mixed& num2)
{
	Mixed M;

	int tempNumeratorNum1;
	int tempNumeratorNum2;
	int tempDenominatorNum;

	tempNumeratorNum1 = num1.denominator*num1.wholeNum + num1.numerator;
	tempNumeratorNum1 = tempNumeratorNum1 * num2.denominator;
	tempNumeratorNum2 = num2.denominator*num2.wholeNum + num2.numerator;
	tempNumeratorNum2 = tempNumeratorNum2 * num1.denominator;
	tempDenominatorNum = num1.denominator*num2.denominator;

	if (num1.isNegative == false && num2.isNegative == false)
	{
		if (num1 > num2)
		{
			Mixed N1(0, tempNumeratorNum1 + tempNumeratorNum2, tempDenominatorNum);
			M = N1;
		}
		else if (num1 <= num2)
		{
			if (num1 < num2)
			{
				Mixed N1(0, tempNumeratorNum2 - tempNumeratorNum1, tempDenominatorNum);
				M = N1;
			}
			else if (num1 == num2)
			{
				Mixed N1(0, tempNumeratorNum2 - tempNumeratorNum1, tempDenominatorNum);
				M = N1;
			}
		}
	}
	if (num1.isNegative == true && num2.isNegative == false)
	{
		Mixed N1(0, tempNumeratorNum1 + tempNumeratorNum2, tempDenominatorNum);
		M = N1;
	}
	if (num1.isNegative == false && num2.isNegative == true)
	{
		Mixed N1(0, tempNumeratorNum1 + tempNumeratorNum2, tempDenominatorNum);
		M = N1;
	}
	if (num1.isNegative == true && num2.isNegative == true)
	{
		if (num1 > num2)
		{
			Mixed N1(0,tempNumeratorNum2 - tempNumeratorNum1, tempDenominatorNum);
			M = N1;
		}
		else if (num1 <= num2)
		{
			if (num1 < num2)
			{
				Mixed N1(0, tempNumeratorNum1 - tempNumeratorNum2, tempDenominatorNum);
				M = N1;
			}
			else if (num1 == num2)
			{
				Mixed N1(0, 0, tempDenominatorNum);
				M = N1;
			}
		}
	}
	return M;
}

Mixed operator*(const Mixed& num1, const Mixed& num2)
{
	Mixed M;

	int tempNumeratorNum1;
	int tempNumeratorNum2;
	int tempDenominatorNum;

	tempNumeratorNum1 = num1.denominator*num1.wholeNum + num1.numerator;
	tempNumeratorNum2 = num2.denominator*num2.wholeNum + num2.numerator;
	tempDenominatorNum = num1.denominator*num2.denominator;

	if (num1.isNegative == false && num2.isNegative == false)
	{
		Mixed N1(0, tempNumeratorNum1*tempNumeratorNum2, tempDenominatorNum);
		M = N1;
	}
	else if (num1.isNegative == true && num2.isNegative == false)
	{
		Mixed N1(0, (tempNumeratorNum1*tempNumeratorNum2)*(-1), tempDenominatorNum);
		M = N1;
	}
	else if (num1.isNegative == false && num2.isNegative == true)
	{
		Mixed N1(0, (tempNumeratorNum1*tempNumeratorNum2)*(-1), tempDenominatorNum);
		M = N1;
	}
	else if (num1.isNegative == true && num2.isNegative == true)
	{
		Mixed N1(0, tempNumeratorNum1*tempNumeratorNum2, tempDenominatorNum);
		M = N1;
	}

	return M;
}

Mixed operator/(const Mixed& num1, const Mixed& num2)
{
	Mixed M;

	int tempNumeratorNum1;
	int tempNumeratorNum2;
	int tempDenominatorNum;

	tempNumeratorNum1 = num1.denominator*num1.wholeNum + num1.numerator;
	tempNumeratorNum2 = num2.denominator*num2.wholeNum + num2.numerator;
	tempDenominatorNum = tempNumeratorNum2 * num1.denominator;

	if (num1.isNegative == false && num2.isNegative == false)
	{
		Mixed N1(0, tempNumeratorNum1*num2.denominator, tempDenominatorNum);
		M = N1;
	}
	else if (num1.isNegative == true && num2.isNegative == false)
	{
		Mixed N1(0, (tempNumeratorNum1*num2.denominator)*(-1), tempDenominatorNum);
		M = N1;
	}
	else if (num1.isNegative == false && num2.isNegative == true)
	{
		Mixed N1(0, (tempNumeratorNum1*num2.denominator)*(-1), tempDenominatorNum);
		M = N1;
	}
	else if (num1.isNegative == true && num2.isNegative == true)
	{
		Mixed N1(0, tempNumeratorNum1*tempNumeratorNum2, tempDenominatorNum);
		M = N1;
	}

	return M;
}

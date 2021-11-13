#include "BooleanLoginElements.h"
#include <iostream>
#include <bitset>
using namespace std;

bitset<4> doubleBitsNumbersMultiply(const bitset<2>& left, const bitset<2>& right)
{
	bitset<4> result;
	auto bit_1 = And(Fasting(left[0]), Fasting(right[0]));
	auto bit_2 = And(Fasting(left[1]), Fasting(right[0]));
	auto bit_3 = And(Fasting(left[0]), Fasting(right[1]));
	auto bit_4 = And(Fasting(left[1]), Fasting(right[1]));
	auto and_2_3 = And(bit_2, bit_3);

	result[0] = bit_1.value();
	result[1] = Xor(bit_2, bit_3).calculateExpression();
	result[2] = Xor(and_2_3, bit_4).calculateExpression();
	result[3] = And(and_2_3, bit_4).calculateExpression();

	return result;
}

int main()
{
	cout << boolalpha << doubleBitsNumbersMultiply(2, 0) << endl;
}
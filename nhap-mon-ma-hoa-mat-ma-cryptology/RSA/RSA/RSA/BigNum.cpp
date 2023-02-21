#include "BigNum.h"


//-----------
BigBin generateBin(int bits)
{
	BigBin binary(bits);
	binary[0] = binary[bits - 1] = 1;

	for (int i = 1; i < bits - 1; i++) {
		binary[i] = rand() % 2;
	}
	return binary;
}
// Big Interger
BigInt binToInt(BigBin bin)
{
	BigInt integer;
	integer.push_back(0);
	for (int i = 0; i < bin.size(); i++)
	{
		integer = sumBI(integer, integer);
		if (bin[i])
		{
			integer = sumBI(integer, { 1 });
		}
	}
	return integer;
}



BigInt sumBI(BigInt a, BigInt b)
{
	BigInt big = a;
	BigInt small = b;
	if (a.size() < b.size())
	{
		big = b;
		small = a;
	}
	BigInt sum;
	int temp;
	for (int i = small.size(); i < big.size(); i++)
		small.push_back(0);

	int extra = 0;
	for (int i = 0; i < big.size(); i++)
	{
		temp = big[i] + small[i] + extra;
		sum.push_back(temp % 10);
		extra = temp / 10;
	}
	if (extra > 0)
		sum.push_back(extra);


	return sum;
}
//
BigInt subBI(BigInt a, BigInt b)
{
	if (a == b)
		return { 0 };
	else if (!isPgreaterQ(a, b))
		return { -1 };

	for (int i = b.size(); i < a.size(); i++)
		b.push_back(0);

	BigInt sub;
	int extra = 0;
	for (int i = 0; i < a.size(); i++)
	{
		if (a[i] < b[i] + extra)
		{
			sub.push_back(a[i] - b[i] - extra + 10);
			extra = 1;
		}
		else
		{
			sub.push_back(a[i] - b[i] - extra);
			extra = 0;
		}
	}
	while (1)
	{
		if (sub[sub.size() - 1] == 0)
			sub.pop_back();
		else
			break;
	}
	return sub;
}
//
BigInt mulBI(BigInt a, BigInt b) {
	BigInt big = a;
	BigInt small = b;
	if (a.size() < b.size())
	{
		big = b;
		small = a;
	}

	BigInt result = { 0 };

	for (int i = 0; i < small.size(); i++)
	{
		BigInt step = { 0 };
		int t = small[i];
		for (int j = 0; j < t; j++) {
			step = sumBI(big, step);
		}
		for (int k = 0; k < i; k++) {
			step.insert(step.begin(), 0);

		}
		result = sumBI(step, result);
	}
	return result;
}

BigInt divBI(BigInt a, BigInt b)
{
	BigInt t1, t2, result;
	int count = b.size();

	while (count)
	{
		int t = a.back();
		a.pop_back();
		t1.insert(t1.begin(), t);
		count--;
	}
	if (compare(t1, b) == -1) {
		int t = a.back();
		a.pop_back();
		t1.insert(t1.begin(), t);
	}
	while (1)
	{

		t2 = divBasic(t1, b);

		result.insert(result.begin(), t2[0]);
		t2 = mulBI(b, t2);
		t1 = subBI(t1, t2);

		if (a.size() == 0)
			break;
		int t = a.back();
		a.pop_back();
		t1.insert(t1.begin(), t);

		while (1)
		{
			if (t1[t1.size() - 1] == 0 && t1.size() > 1)
				t1.erase(t1.begin() + 1);
			else
				break;
		}
	};

	if (result[result.size() - 1] == 0 && result.size() != 1)
		result.pop_back();
	//result.insert(t1.begin(), 0);
	return result;
}
BigInt divBasic(BigInt a, BigInt b) {
	if (a == b)
		return { 1 };
	if (a == BigInt{ 0 })
		return { 0 };
	if (!isPgreaterQ(a, b))
		return { 0 };

	BigInt temp = a;

	BigInt result = { -1 };
	int count = 0;
	while (true)
	{

		if (temp[0] == -1)
		{
			//result = sumBI(result, { -1 });
			break;
		}
		temp = subBI(temp, b);
		result = sumBI(result, { 1 });
	}
	return result;
}
//
BigInt remainderBI(BigInt num, BigInt m) {
	BigInt res = { 0 };

	reverse(num.begin(), num.end());
	for (int i = 0; i < num.size(); i++) {
		res = remainderBasic(sumBI(mulBI(res, { 0,1 }), { num[i] }), m);
	}
	return res;
}
BigInt remainderBasic(BigInt a, BigInt b) {
	if (!isPgreaterQ(a, b))
		return a;
	BigInt temp = a;
	BigInt result;
	while (true)
	{
		temp = subBI(temp, b);
		if (temp[0] == -1)
			break;
		else
		{
			result.clear();
			result = temp;
		}
	}
	return result;
}
//
BigInt subExtended(BigInt a, BigInt b)
{
	BigInt result;
	int t1Sign = 1;
	int t2Sign = 1;

	a[a.size() - 1] < 0 ? t1Sign = -1 : t1Sign = 1;
	b[b.size() - 1] < 0 ? t2Sign = -1 : t2Sign = 1;

	a[a.size() - 1] = abs(a[a.size() - 1]);
	b[b.size() - 1] = abs(b[b.size() - 1]);

	t2Sign = -t2Sign;
	if (t1Sign == t2Sign)
	{
		result = sumBI(a, b);
		result[result.size() - 1] *= t1Sign;

		return result;
	}
	else
	{
		if (isPgreaterQ(a, b)) {
			result = subBI(a, b);
			result[result.size() - 1] *= t1Sign;
		}
		else
		{
			result = subBI(b, a);
			result[result.size() - 1] *= t2Sign;
		}
		return result;

	}
}

BigInt mulExtended(BigInt a, BigInt b)
{
	BigInt t1 = a;
	BigInt t2 = b;
	BigInt result;
	int t1Sign = 1;
	int t2Sign = 1;

	t1[a.size() - 1] < 0 ? t1Sign = -1 : t1Sign = 1;
	t2[b.size() - 1] < 0 ? t2Sign = -1 : t2Sign = 1;
	t1[a.size() - 1] = abs(t1[a.size() - 1]);
	t2[b.size() - 1] = abs(t2[b.size() - 1]);

	result = mulBI(t1, t2);
	if (t1Sign == t2Sign)
	{
		result[result.size() - 1] = abs(result[result.size() - 1]);
		return result;
	}
	if (t1Sign != t2Sign)
	{
		result[result.size() - 1] = -result[result.size() - 1];
		return result;
	}
}

BigInt divExtended(BigInt a, BigInt b)
{
	BigInt t1 = a;
	BigInt t2 = b;
	BigInt result;
	int t1Sign = 1;
	int t2Sign = 1;

	t1[a.size() - 1] < 0 ? t1Sign = -1 : t1Sign = 1;
	t2[b.size() - 1] < 0 ? t2Sign = -1 : t2Sign = 1;


	t1[a.size() - 1] = abs(t1[a.size() - 1]);
	t2[b.size() - 1] = abs(t2[b.size() - 1]);

	if (t1Sign == t2Sign)
	{
		result = divBasic(t1, t2);
		return result;
	}
	if (t1Sign != t2Sign)
	{
		result = divBasic(t1, t2);
		result[result.size() - 1] *= -1;
		return result;
	}

}
//

//
void printBin(BigBin a)
{
	for (auto i : a)
		cout << i;
}
void printInt(BigInt a) {
	reverse(a.begin(), a.end());
	for (auto i : a)
		cout << i;
}
bool isPgreaterQ(BigInt& p, BigInt& q) {

	if (p.size() < q.size())
	{
		return 0;
	}
	if (p.size() > q.size())
	{
		return 1;
	}
	if (p.size() == q.size())
	{
		if (p.size() == 1) {
			return p[0] > q[0] ? 1 : 0;
		}
		for (int i = p.size() - 1; i > 0; i--) {
			if (p[i] < q[i] || (p[i] == q[i] && p[i - 1] < q[i - 1]))
			{
				return 0;
			}
			else if (p[i] > q[i])
			{
				return 1;
			}
		}
	}
	return 1;
}
void swapBI(BigInt& a, BigInt& b)
{
	BigInt temp = a;
	a = b;
	b = temp;
}
int compare(BigInt a, BigInt b)
{
	reverse(a.begin(), a.end());
	reverse(b.begin(), b.end());
	if (a.size() > b.size())
		return 1;
	if (a.size() < b.size())
		return -1;
	for (int i = 0; i < a.size() - 1; i++)
	{
		if (a[i] > b[i])
			return 1;
		if (a[i] < b[i])
			return -1;
	}
	return 0;
}
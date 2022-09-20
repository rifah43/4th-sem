#include <bits/stdc++.h>
using namespace std;

unsigned long long int Message[80];

const unsigned long long int K[80]= { 0x428a2f98d728ae22, 0x7137449123ef65cd,
		0xb5c0fbcfec4d3b2f, 0xe9b5dba58189dbbc,
		0x3956c25bf348b538, 0x59f111f1b605d019,
		0x923f82a4af194f9b, 0xab1c5ed5da6d8118,
		0xd807aa98a3030242, 0x12835b0145706fbe,
		0x243185be4ee4b28c, 0x550c7dc3d5ffb4e2,
		0x72be5d74f27b896f, 0x80deb1fe3b1696b1,
		0x9bdc06a725c71235, 0xc19bf174cf692694,
		0xe49b69c19ef14ad2, 0xefbe4786384f25e3,
		0x0fc19dc68b8cd5b5, 0x240ca1cc77ac9c65,
		0x2de92c6f592b0275, 0x4a7484aa6ea6e483,
		0x5cb0a9dcbd41fbd4, 0x76f988da831153b5,
		0x983e5152ee66dfab, 0xa831c66d2db43210,
		0xb00327c898fb213f, 0xbf597fc7beef0ee4,
		0xc6e00bf33da88fc2, 0xd5a79147930aa725,
		0x06ca6351e003826f, 0x142929670a0e6e70,
		0x27b70a8546d22ffc, 0x2e1b21385c26c926,
		0x4d2c6dfc5ac42aed, 0x53380d139d95b3df,
		0x650a73548baf63de, 0x766a0abb3c77b2a8,
		0x81c2c92e47edaee6, 0x92722c851482353b,
		0xa2bfe8a14cf10364, 0xa81a664bbc423001,
		0xc24b8b70d0f89791, 0xc76c51a30654be30,
		0xd192e819d6ef5218, 0xd69906245565a910,
		0xf40e35855771202a, 0x106aa07032bbd1b8,
		0x19a4c116b8d2d0c8, 0x1e376c085141ab53,
		0x2748774cdf8eeb99, 0x34b0bcb5e19b48a8,
		0x391c0cb3c5c95a63, 0x4ed8aa4ae3418acb,
		0x5b9cca4f7763e373, 0x682e6ff3d6b2b8a3,
		0x748f82ee5defb2fc, 0x78a5636f43172f60,
		0x84c87814a1f0ab72, 0x8cc702081a6439ec,
		0x90befffa23631e28, 0xa4506cebde82bde9,
		0xbef9a3f7b2c67915, 0xc67178f2e372532b,
		0xca273eceea26619c, 0xd186b8c721c0c207,
		0xeada7dd6cde0eb1e, 0xf57d4f7fee6ed178,
		0x06f067aa72176fba, 0x0a637dc5a2c898a6,
		0x113f9804bef90dae, 0x1b710b35131c471b,
		0x28db77f523047d84, 0x32caab7b40c72493,
		0x3c9ebe0a15c9bebc, 0x431d67c49c100d4c,
		0x4cc5d4becb3e42b6, 0x597f299cfc657e2a,
		0x5fcb6fab3ad6faec, 0x6c44198c4a475817 };
    unsigned long long int A = 0x6a09e667f3bcc908;
	unsigned long long int B = 0xbb67ae8584caa73b;
	unsigned long long int C = 0x3c6ef372fe94f82b;
	unsigned long long int D = 0xa54ff53a5f1d36f1;
	unsigned long long int E = 0x510e527fade682d1;
	unsigned long long int F = 0x9b05688c2b3e6c1f;
	unsigned long long int G = 0x1f83d9abfb41bd6b;
	unsigned long long int H = 0x5be0cd19137e2179;

    unsigned long long int a,b,c,d,e,f,g,h;

string gethex(string bin)
{
	if (bin == "0000")
		return "0";
	if (bin == "0001")
		return "1";
	if (bin == "0010")
		return "2";
	if (bin == "0011")
		return "3";
	if (bin == "0100")
		return "4";
	if (bin == "0101")
		return "5";
	if (bin == "0110")
		return "6";
	if (bin == "0111")
		return "7";
	if (bin == "1000")
		return "8";
	if (bin == "1001")
		return "9";
	if (bin == "1010")
		return "a";
	if (bin == "1011")
		return "b";
	if (bin == "1100")
		return "c";
	if (bin == "1101")
		return "d";
	if (bin == "1110")
		return "e";
	if (bin == "1111")
		return "f";
}

string decimaltohex(unsigned long long int deci)
{
	string binEqui = bitset<64>(deci).to_string();

	string hexstring = "";
	string temp;

	for (unsigned int i = 0;i < binEqui.length(); i += 4)
    {
		temp = binEqui.substr(i, 4);
		hexstring += gethex(temp);
	}
	return hexstring;
}

unsigned long long int BintoDec(string bin)
{
	unsigned long long int value = bitset<64>(bin).to_ullong();
	return value;
}

unsigned long long int rotR(unsigned long long int n, int x)
{
	return (n >> x) | (n << (64 - x));
}

unsigned long long int shiftR(unsigned long long int n, int x)
{
	return (n >> x);
}

void separator(string getBlock)
{
	int chunknum = 0;

	for (unsigned int i = 0;i < getBlock.length();i += 64, ++chunknum)
    {
        Message[chunknum] = BintoDec(getBlock.substr(i, 64));
	}
	for (int g = 16; g < 80; ++g)
    {
		unsigned long long int WordA = rotR(Message[g - 2], 19)	^ rotR(Message[g - 2], 61)^ shiftR(Message[g - 2], 6);
		unsigned long long int WordB = Message[g - 7];
		unsigned long long int WordC = rotR(Message[g - 15], 1)	^ rotR(Message[g - 15], 8)^ shiftR(Message[g - 15], 7);

		unsigned long long int WordD = Message[g - 16];
        unsigned long long int T = WordA + WordB + WordC + WordD;
        Message[g] = T;
	}
}

unsigned long long int sumA(unsigned long long int a)
{
    unsigned long long int rot28 = rotR(a, 28);
    unsigned long long int rot34 = rotR(a, 34);
    unsigned long long int rot39 = rotR(a, 39);
    return rot28 ^ rot34 ^ rot39;
}

unsigned long long int sumE(unsigned long long int e)
{
    unsigned long long int rot14 = rotR(a, 15);
    unsigned long long int rot18 = rotR(a, 18);
    unsigned long long int rot41 = rotR(a, 41);
    return rot14 ^ rot18 ^ rot41;
}

unsigned long long int Ch(unsigned long long int e, unsigned long long int f, unsigned long long int g)
{
	return (e & f) ^ (~e & g);
}

unsigned long long int maj(unsigned long long int a, unsigned long long int b, unsigned long long int c)
{
	return (a & b) ^ (b & c) ^ (c & a);
}

unsigned long long int sigma1(unsigned long long int e)
{
	return rotR(e, 14)^ rotR(e, 18)^ rotR(e, 41);
}

unsigned long long int sigma0(unsigned long long int a)
{
    unsigned long long int rot1 = rotR(a, 1);
    unsigned long long int rot8 = rotR(a, 8);
    unsigned long long int sh7 = shiftR(a, 7);
    return rot1 ^ rot8 ^ sh7;
}

void Func()
{
	unsigned long long int T1,T2;

    T1 = h + Ch(e, f, g) + sumE(e) + w[i] + K[i];
    T2 = sumA(a) + maj(a, b, c);
    h=g;
    g=f;
    f=e;
    e=(d + T1);
    d=c;
    c=b;
    b=a;
    a=(T1+T2);
    
}

string SHA512(string myString)
{
	stringstream fixedstream;

	for (int i = 0;i < myString.size(); ++i)
    {
		fixedstream << bitset<8>(myString[i]);
	}
	string s1024;
	s1024 = fixedstream.str();
	int orilen = s1024.length();
	int tobeadded;

	int modded = s1024.length() % 1024;

	if (1024 - modded >= 128) {
		tobeadded = 1024 - modded;
	}

	else if (1024 - modded < 128) {
		tobeadded = 2048 - modded;
	}

	s1024 += "1";
	for (int y = 0; y < tobeadded - 129; y++) {
		s1024 += "0";
	}
	string lengthbits = std::bitset<128>(orilen).to_string();
	s1024 += lengthbits;
	int blocksnumber = s1024.length() / 1024;
	int chunknum = 0;
	string Blocks[blocksnumber];
	for (int i = 0; i < s1024.length();
		i += 1024, ++chunknum) {
		Blocks[chunknum] = s1024.substr(i, 1024);
	}

	for (int letsgo = 0;letsgo < blocksnumber;++letsgo)
    {
    	separator(Blocks[letsgo]);
        a = A;
        b = B;
        c = C;
        d = D;
        e = E;
        f = F;
        g = G;
        h = H;
		int count = 0;
		for (int i = 0; i < 10; i++)
        {
        	Func(A, B, C, D, E, F, G, H, count);
			count++;
			Func(H, A, B, C, D, E, F, G, count);
			count++;
			Func(G, H, A, B, C, D, E, F, count);
			count++;
			Func(F, G, H, A, B, C, D, E, count);
			count++;
			Func(E, F, G, H, A, B, C, D, count);
			count++;
			Func(D, E, F, G, H, A, B, C, count);
			count++;
			Func(C, D, E, F, G, H, A, B, count);
			count++;
			Func(B, C, D, E, F, G, H, A, count);
			count++;
		}

		A += a;
		B += b;
		C += c;
		D += d;
		E += e;
		F += f;
		G += g;
		H += h;
	}

	stringstream output;

	output << decimaltohex(A);
	output << decimaltohex(B);
	output << decimaltohex(C);
	output << decimaltohex(D);
	output << decimaltohex(E);
	output << decimaltohex(F);
	output << decimaltohex(G);
	output << decimaltohex(H);

	return output.str();
}

int main()
{
	string inMessage = "This is SHA-512";

	cout << inMessage << ": " << SHA512(inMessage);

	return 0;
}

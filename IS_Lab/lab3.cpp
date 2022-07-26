#include <bits/stdc++.h>
using namespace std;

string input,output_1, output_2;
int x[150],pos=3,cpos=128,rem;
char refTable[128][10];

char finding(char a,int pos)
{
    for(int i=0;i<cpos;i++)
    {
        if(refTable[i][pos]==a)
        {
            return i;
        }
    }
}

string encrypt(string input)
{
    string output="";
    for(int i=0;i<input.size();i++)
    {
        output+=((refTable[input[i]][i%pos])+13000000)%128;
        rem=((refTable[input[i]][i%pos])+13000000)/128;
    }
    cout<<"The encrypted string is: "<<endl;
    cout<<output<<endl;
    return output;
}

void decrypt(string input)
{
    string output="";
    for(int i=0;i<input.size();i++)
    {
        output+=((finding(input[i], i%pos))+(rem*128))-13000000;
    }
    cout<<"The decrypted string is: "<<endl;
    cout<<output<<endl;
}

int main()
{
    cout<<"Enter the string: "<<endl;
    getline(cin, input,'\n');

    for(int i=0;i<cpos;i++)
    {
        for(int j=0;j<pos;j++)
        {
            refTable[i][j]=(i+j)%cpos+13;
        }
    }
    string out = encrypt(input);
    decrypt(out);
}


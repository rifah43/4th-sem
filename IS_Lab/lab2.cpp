#include <bits/stdc++.h>
using namespace std;

string input,output_1, output_2;
int x[150],pos=3,cpos=128;
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
        output+=refTable[input[i]][i%pos];
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
        output+=finding(input[i], i%pos);
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

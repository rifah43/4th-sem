#include <bits/stdc++.h>
using namespace std;

string input,output_1, output_2;
int x[150];
vector<pair<char,int> > refTable;

void encrypt()
{
    for(int i=0;i<input.size();i++)
    {
        for(int j=0;j<95;j++)
        {
            if(input[i]==refTable[j].first)
            {
                if(refTable[j].second>126)
                {
                    output_1.push_back(refTable[j].second-126+32);
                }
                else
                {
                    output_1.push_back(refTable[j].second);
                }
            }
        }
    }
}

void decrypt()
{
    for(int i=0;i<output_1.size();i++)
    {
        for(int j=0;j<95;j++)
        {
            if(output_1[i]==refTable[j].first)
            {
                if((refTable[j].second-20)<32)
                {
                    output_2.push_back(refTable[j].second+126-52);
                }
                else
                {
                    output_2.push_back(refTable[j].second-20);
                }
            }
        }
    }
}

int main()
{
    cout<<"Enter the string: "<<endl;
    getline(cin, input,'\n');

    for(int i=0;i<95;i++)
    {
        char a= ' '+i;
        refTable.push_back({a,a+10});
    }
    encrypt();
    cout<<"The encrypted message is: "<<endl;
    cout<<output_1<<endl;
    decrypt();
    cout<<"The decrypted message is: "<<endl;
    cout<<output_2<<endl;
}

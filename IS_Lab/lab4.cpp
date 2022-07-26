#include<bits/stdc++.h>

using namespace std;

int refTable[128][20];

void tableGenerator(int key){
    for (int i = 0; i < 128; i++)
    {
        for (int j = 0; j < 20; j++)
        {
            hashTable[i][j] = (i + j + key) % 128;
        }
    }
}

int findKey(int ch, int position){
    for (int i = 0; i < 128; i++)
    {
        if(refTable[i][position]==ch){
            return i;
        }
    }
    return 0;
}

void decrypt(string str)
{
     for (int i = 0; str[i] != '\0'; i++)
    {
        int ch = (int)str[i];
        int position = i % 20;
        int key = findKey(ch,position);
        str[i]= (char)key;
    }
    cout << "PlainText :" << str << endl;
}

void encrypt(string str)
{
    for (int i = 0; str[i] != '\0'; i++)
    {
        int ch = (int)str[i];
        int position = i % 20;
        str[i] = refTable[ch][position];
    }
    cout << "CipherText :" << str << endl;
    decrypt(str);
}




int main()
{


    int choice;

    cout << "Enter PLainText: ";
    string input;
    getline(cin, input);

    cout << "Enter the Key: ";
    int key;
    cin >> key;

    tableGenerator(key);
    encrypt(input);
}

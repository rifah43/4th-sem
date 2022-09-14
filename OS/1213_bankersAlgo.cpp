#include<bits/stdc++.h>
using namespace std;
int maxi[5][4] = {{0, 0, 1, 2},{ 1, 7, 5, 0},{ 2, 3, 5, 6}, {0, 6, 5, 2},{ 0, 6, 5, 6}};
int allocation[5][4] = {{0, 0 , 1, 2}, {1, 0, 0, 0}, {1, 3, 5, 4}, {1, 3, 5, 4}, {0, 0, 1, 4}};
int available[4] = {1, 5, 2, 0};
int need[5][4];
int work[4];
int finish[5]={};

bool isSafe()
{
    int x = 0;
    bool found = false;
    for(int i=0;i<4;i++)
    {
        work[i]= available[i];
    }
    for(int i=0;i<5;i++)
    {
        for(int j=0;j<4;j++)
        {
            need[i][j] = maxi[i][j]-allocation[i][j];
        }
    }
    
    while(x<5)
    {
        for(int i=0;i<5;i++)
        {
            if(finish[i]==0)
            {
                for(int j=0;j<4;j++)
                {
                    if(need[i][j]>work[j])
                    {
                        break;
                    }

                    if(j==3)
                    {
                        for(int k=0; k<4;k++)
                        {
                            work[k] = work[k]+allocation[i][k];
                            finish[i]= 1;
                            found = true;
                        }
                        cout<<i<<endl;
                    }
                }
            }
        }
        x++;
    }
    for (int i = 0; i < 5; i++)
    {
       if(finish[i]==0)
       {
            cout<<"Not Possible"<<endl;
            return false;
       }
    }
    
    cout<<"safe"<<endl;
    

    return true;
}

int main()
{
cout<<"Safe sequence ";
isSafe();

}
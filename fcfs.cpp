#include<iostream>
#include<bits/stdc++.h>
using namespace std;

vector <int> completion(vector<int> &arrival,vector<int> &burst){
    int n=burst.size();
    vector <int> c(n,0);
    int i=0;
    if(i==0){
        c[i]=burst[i];
    }
    for (i = 1; i < n; i++)
    {
        c[i]=max(c[i-1],arrival[i])+burst[i];
    }

    return c;
    
}

vector <int> waiting(vector <int> &arrival , vector <int> &ct){
    int n=arrival.size();
    vector <int> wt(n,0);
    int i=0;
    if(i==0){
        wt[i]=0;
    }

    for(int i=1;i<n;i++){
        
        wt[i]=ct[i-1]-arrival[i];
        if(wt[i]<0){
            wt[i]=0;
        }
    }

    return wt;

}

vector <int> turnaround(vector <int> &arrival , vector <int> &ct){
    int n=arrival.size();
    vector <int> tnt(n,0);

    for(int i=0;i<n;i++){
        tnt[i]=ct[i]-arrival[i];
    }

    return tnt;
}


int main(){
    int n;
    cin>>n;
    vector <int> at,bt,pid;
    
    
    at.resize(n);
    bt.resize(n);
    pid.resize(n);
    for (int i = 0; i < n; i++)
    {
        /* code */
        pid[i]=i+1;
    }

    cout<<"Now enter arrival time and burst time in each process "<<endl;
    for(int i=0;i<n;i++){
        cin>>at[i]>>bt[i];
    }

    // sort(at.begin(),at.end());

    for (int i = 0; i < n; i++)
    {
        /* code */
        for (int j = 0; j < n; j++)
        {
            /* code */
            if (at[j]>at[i]){
                swap(at[i],at[j]);
                swap(bt[i],bt[j]);
                swap(pid[i],pid[j]);
            }
            
        }
        
    }
    

    vector <int> ct(n,0);
    ct=completion(at,bt);

    for(int i=0;i<n;i++){
        cout<<ct[i]<<" ";
        cout<<"\n";
    }

    vector <int> wt;
    wt.resize(n);
    wt=waiting(at,ct);

    vector <int> tnt(n,0);
    tnt=turnaround(at,ct);

    for (int i = 0; i < n; i++)
    {
        /* code */
        for (int j = 0; j < n; j++)
        {
            /* code */
            if (pid[j]>pid[i]){
                swap(at[i],at[j]);
                swap(bt[i],bt[j]);
                swap(pid[i],pid[j]);
                swap(ct[i],ct[j]);
                swap(wt[i],wt[j]);
                swap(tnt[i],tnt[j]);
            }
            
        }
        
    }

    cout<<"Process\t\t"<<"arrival time\t"<<"burst time\t"<<"waiting time\t"<<"completion time\t"<<"Turn around"<<endl;

    for(int i=0;i<n;i++){
        cout<<pid[i]<<"\t\t";
        cout<<at[i]<<"\t\t";
        cout<<bt[i]<<"\t\t";
        cout<<wt[i]<<"\t\t";
        cout<<ct[i]<<"\t\t";
        cout<<tnt[i]<<"\t\t";
        cout<<endl;
    }



    return 0;
}
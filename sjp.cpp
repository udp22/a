>>>>>>>>>>>>>>>>>   SJF  Preemptive Code<<<<<<<<<<<<<

#include<iostream>
#include<vector>
#include<map>
#include<algorithm>
using namespace std;

struct process {
    int id;
    int arrivalTime;
    int burstTime;
    int completionTime;  
    int turnAroundTime;
    int waitingTime;
};


bool compare( process a,process b){
    if(a.arrivalTime == b.arrivalTime ){
        return a.burstTime < b.burstTime;
    }
    return a.arrivalTime <b.arrivalTime;

}

bool comp_Burst(process a ,process b){
    if( a.burstTime == b.burstTime)
    {
        return a.arrivalTime < b.arrivalTime;
    }
    return a.burstTime<b.burstTime;
}

bool cmpid(process a , process b){
    return a.id < b.id;
}


int main(){
    int n ;
    cout<<"Enter the number of process:"<<endl;
    cin>>n;

    process p[n];

   
    map<int,int> mapTempBurst;

    for (int  i = 0; i < n; i++)
    {
        p[i].id=i+1;
        cout<<"Enter the arrival time for P"<<i+1<<endl;
        cin>>p[i].arrivalTime;
        
    }
    for (int  i = 0; i < n; i++)
    {
        
        cout<<"Enter the burst time for P"<<i+1<<endl;
        cin>>p[i].burstTime;
       
        mapTempBurst[p[i].id]=p[i].burstTime;
    }

    sort(p,p+n,compare);


    int count=0;
    int currentTime=p[0].arrivalTime;
    
    while (count<n)     
    {
        currentTime+=1;
        if (p[count].arrivalTime < currentTime)
        {
            p[count].burstTime--;

        }
        if(p[count].burstTime==0){
            p[count].completionTime=currentTime;
            count++;
        }
        int j =count;
        for(int i=count+1;i<n;i++){
            if(p[i].arrivalTime<=currentTime){
                j++;
            }

        }
        if(j!=count){
            sort(p+count,p+j+1,comp_Burst);
            
        }
    }

    
    for (int i = 0; i < n; i++)
    {
        p[i].turnAroundTime=p[i].completionTime-p[i].arrivalTime;
        p[i].waitingTime=p[i].completionTime-mapTempBurst[p[i].id];
        
    }
    
        sort(p,p+n,cmpid);
    cout<<"Process"<<"\t\t"<<"Arrival"<<"\t\t"<<"Burst"<<"\t\t"<<"Completion"<<"\t\t"<<"TAT"<<"\t\t"<<"Waiting"<<endl;
    cout<<endl;
    for (int i = 0; i < n; i++)
    {
        cout<<"P"<<p[i].id<<"\t\t"<<p[i].arrivalTime<<"\t\t"<<p[i].burstTime<<"\t\t"<<p[i].completionTime<<"\t\t\t"<<p[i].turnAroundTime<<"\t\t"<<p[i].waitingTime<<endl;

    }
    
    return 0;
}
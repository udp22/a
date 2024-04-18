//  >>>>>>>>>>>>>>>>>>Priority Non Preemptive<<<<<<<<<







#include<iostream>
#include<algorithm>
using namespace std;



struct process {
    int id;
    int priority;
    int arrivalTime;
    int burstTime;
    int waitingTime;
    int completionTime;
    int turnAroundTime;
    
};

bool compare(process a,process b){
    if (a.arrivalTime == b.arrivalTime){
        return a.priority < b.priority;
    }
   
    
    return a.arrivalTime<b.arrivalTime;
}

bool cmpid(process a,process b){
    return a.id <b.id;
}
int main(){
    int n;
    cout<<"Enter the no of process:"<<endl;
    cin>>n;
    process p[n];
    for (int  i = 0; i < n; i++)
    {
        p[i].id=i+1;
        cout<<"Enter the  arrival, burst time andpriority for each P"<<p[i].id<<":";
        cin>>p[i].arrivalTime>>p[i].burstTime>>p[i].priority;
    }

     sort(p,p+n,compare);

    int currentTime=0;
    // currentTime+=p[0].completionTime;
    
    int idleTime=0;
    for (int i = 0; i < n; i++)
    {   
        if(p[i].arrivalTime>currentTime){
            idleTime=p[i].arrivalTime-currentTime;
            currentTime=p[i].arrivalTime;
        }
       
        for (int  j = i+1; j < n; j++)
        {
            if(p[j].priority<p[i].priority && p[j].arrivalTime<=currentTime){
                swap(p[j],p[i]);
            }
        }
        
        currentTime+=p[i].burstTime;
            
    }
    p[0].waitingTime=0;
    p[0].completionTime=p[0].arrivalTime+p[0].burstTime;
    p[0].turnAroundTime=p[0].burstTime;
    for(int i=1;i<n;i++){
    p[i].completionTime=max(p[i-1].completionTime,p[i].arrivalTime)+p[i].burstTime;
    p[i].turnAroundTime=p[i].completionTime-p[i].arrivalTime;
    p[i].waitingTime=max(0,p[i-1].completionTime-p[i].arrivalTime);
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
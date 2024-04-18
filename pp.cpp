#include<iostream>
#include<algorithm>
#include<map>
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
bool cmppri(process a, process b){
    if (a.priority == b.priority)
    {
        return a.arrivalTime <b.arrivalTime;
    }
    return a.priority <b.priority;
    
}
bool cmpid(process a,process b){
    return a.id <b.id;
}

int main(){

    int n;
    cout<<"Enter the no of process:"<<endl;
    cin>>n;
    process p[n];
    map<int,int>  mapTempBurst;

    for (int  i = 0; i < n; i++)
    {
        p[i].id=i+1;
        cout<<"Enter the  arrival, burst time and priority for each P"<<p[i].id<<":";
        cin>>p[i].arrivalTime>>p[i].burstTime>>p[i].priority;
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

        // This is important ithe fakt tula pahaych aahe ki kiti process currentTime chya aat aahet
        for(int i=count+1;i<n;i++){
            if(p[i].arrivalTime<=currentTime){
                j++;
            }

        }
        if(j!=count){
            sort(p+count,p+j+1,cmppri);
            
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
//Preemptive Priority
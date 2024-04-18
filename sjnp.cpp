<<<<<<<<<<<<<<<<<<<SJF Non Preemptive>>>>>>>>>>>>>>>>>>>>>>>>>>>>

#include<iostream>
using namespace std;

struct process {
    int id;
    int arrivalTime;
    int burstTime;
    int compeltionTime;
    int turnaroundTime;
    int waitingTime;
};

bool compare(process a,process b){
        if(a.arrivalTime==b.arrivalTime){
            return a.burstTime<b.burstTime;
        }
        return a.arrivalTime<b.arrivalTime;
}

bool compBurst(process a,process b){
    if(a.burstTime==b.burstTime){
        return a.arrivalTime < b.arrivalTime;
    }
    return a.burstTime<b.burstTime;
}

bool cmpid(process a,process b){
    return a.id<b.id;
}
int main(){
    int n ;
    cout<<"Enter the no of process :"<<endl;
    cin>>n;
    process p[n];
    for (int  i = 0; i <n; i++)
    {
        p[i].id=i+1;
        cout<<"Enter the arrival times for P"<<i+1<<":"<<endl;
        cin>>p[i].arrivalTime;

    }
    for (int  i = 0; i <n; i++)
    {
        
        cout<<"Enter the burst times for P"<<i+1<<":"<<endl;
        cin>>p[i].burstTime;

    }
    
    sort(p,p+n,compare);
    // sort(p,p+n,compBurst);
    int currentTime=0;
    // currentTime+=p[0].compeltionTime;
    
    int idleTime=0;
    for (int i = 0; i < n; i++)
    {   
        if(p[i].arrivalTime>currentTime){
            idleTime=p[i].arrivalTime-currentTime;
            currentTime=p[i].arrivalTime;
        }
       
        for (int  j = i+1; j < n; j++)
        {
            if(p[j].burstTime<p[i].burstTime && p[j].arrivalTime<=currentTime){
                swap(p[j],p[i]);
            }
        }
        
        currentTime+=p[i].burstTime;
            
    }
    p[0].waitingTime=0;
    p[0].compeltionTime=p[0].arrivalTime+p[0].burstTime;
    p[0].turnaroundTime=p[0].burstTime;
    for(int i=1;i<n;i++){
    p[i].compeltionTime=max(p[i-1].compeltionTime,p[i].arrivalTime)+p[i].burstTime;
    p[i].turnaroundTime=p[i].compeltionTime-p[i].arrivalTime;
    p[i].waitingTime=max(0,p[i-1].compeltionTime-p[i].arrivalTime);
    }

    sort(p,p+n,cmpid);
    cout<<"Process"<<"\t\t"<<"Arrival"<<"\t\t"<<"Burst"<<"\t\t"<<"Completion"<<"\t\t"<<"TAT"<<"\t\t"<<"Waiting"<<endl;
    cout<<endl;
    for (int i = 0; i < n; i++)
    {
        cout<<"P"<<p[i].id<<"\t\t"<<p[i].arrivalTime<<"\t\t"<<p[i].burstTime<<"\t\t"<<p[i].compeltionTime<<"\t\t\t"<<p[i].turnaroundTime<<"\t\t"<<p[i].waitingTime<<endl;

    }




    
    return 0;
}


>>>>>>>>>>>>>>>>>   LJF  Preemptive Code<<<<<<<<<<<<<

#include<iostream>
#include<map>
using namespace std;

struct process {
    int id,
    arrivalTime,
    burstTime,
    completionTime,
    turnaroundTime,
    waitingTime;
};

bool compare (process a,process b){
    if(a.arrivalTime == b.arrivalTime){
            return a.burstTime > b.burstTime;
    }
    return a.arrivalTime <b.arrivalTime;
} 
bool cmpid (process a,process b){
    
    return a.id < b.id;
} 

bool comp_Burst(process a,process b){
    if (a.burstTime == b.burstTime)
    {
      return a.arrivalTime < b.arrivalTime;

    }
    return a.burstTime > b.burstTime;
    
}

int main(){
    int n;
    cout<<"Enter the no of process"<<endl;
    cin>>n;
    process p[n];
    map<int,int> temp_burst;
    for(int i =0;i<n;i++){
        p[i].id=i+1;

        cout<<"Enter the arrival Time for P"<<p[i].id<<" :"<<endl;
        cin>>p[i].arrivalTime;
    }
    for(int i =0;i<n;i++){
    
        cout<<"Enter the Time for P"<<p[i].id<<" :"<<endl;
        cin>>p[i].burstTime;
        temp_burst[p[i].id]=p[i].burstTime;
    }

    sort(p,p+n,compare);

    int count=0;
    int currentTime=p[0].arrivalTime;

    while (count<n)
    {
        currentTime+=1;
        if(p[count].arrivalTime<currentTime){
            p[count].burstTime--;
            
        }

        if(p[count].burstTime==0){
            p[count].completionTime=currentTime;
            count++;
        }
        int j=count;
        for (int i = count+1; i < count; i++)
        {
            if(p[i].arrivalTime<=currentTime){
                j++;
            }
        }
        if(j!=count){
            int ans=p[count].burstTime;
            for (int  i = count; i <= j; i++)
            {
                if(p[i].burstTime>ans){
                    ans=p[i].burstTime;
                }

            }
            if(ans!=p[count].burstTime){
                sort(p+count,p+j+1,comp_Burst);
            }
            
        }
        
        

    }

     for (int i = 0; i < n; i++) {
        p[i].turnaroundTime =p[i].completionTime -p[i].arrivalTime;
        p[i].waitingTime =p[i].turnaroundTime - temp_burst[p[i].id];
    }


    sort(p,p+n,cmpid);
    cout<<"Process"<<"\t\t"<<"Arrival"<<"\t\t"<<"Burst"<<"\t\t"<<"Completion"<<"\t\t"<<"TAT"<<"\t\t"<<"Waiting"<<endl;
    cout<<endl;
    for (int i = 0; i < n; i++)
    {
        cout<<"P"<<p[i].id<<"\t\t"<<p[i].arrivalTime<<"\t\t"<<temp_burst[p[i].id]<<"\t\t"<<p[i].completionTime<<"\t\t\t"<<p[i].turnaroundTime<<"\t\t"<<p[i].waitingTime<<endl;

    }
    
    
    

    return 0;
}
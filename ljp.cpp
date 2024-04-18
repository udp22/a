#include<iostream>
#include<algorithm>
#include<map>
using namespace std;
struct process {
    int id;
    int priority;
    int arivaltime;
    int bursttime;
    int waitingtime;
    int compeltiontime;
    int turnaroundtime;
};


bool compare(process a,process b){
    if(a.arivaltime==b.arivaltime){
        return a.bursttime>b.bursttime;
    }
    return a.arivaltime<b.arivaltime;
}

bool burst_cmp(process a,process b){
    if(a.bursttime==b.bursttime){
        return a.arivaltime<b.arivaltime;
    }
    return a.bursttime>b.bursttime;
}

int main(){
    int n;
    cout<<"enter the no of process :";
    cin>>n;
    process arr[n];
    map<int,int>temp_burst_time;
    for(int i=0;i<n;i++){
        cin>>arr[i].id>>arr[i].arivaltime>>arr[i].bursttime;
        temp_burst_time[arr[i].id]=arr[i].bursttime;
    }
    sort(arr,arr+n,compare);
    int time=arr[0].arivaltime;
    int count=0;
    int j;
    while(count<n){
        time+=1;
        if(arr[count].arivaltime<time){
            arr[count].bursttime--;
        }
        if(arr[count].bursttime==0){
            arr[count].compeltiontime=time;
            count++;
        }
        j=count;
        for(int i=count+1;i<n;i++){
            if(arr[i].arivaltime<=time){
                j++;
            }
        }
        if(j!=count){
            sort(arr+count,arr+j+1,burst_cmp);
        }
    }
    for(int i=0;i<n;i++){
        arr[i].turnaroundtime=arr[i].compeltiontime-arr[i].arivaltime;
        arr[i].waitingtime=arr[i].turnaroundtime-temp_burst_time[arr[i].id];
    }
    sort(arr,arr+n,compare);
    cout<<"process\t arival tiime\t  burst time\t compeltion time\t turn aroundtime\t waiting time"<<endl;
    for(int i=0;i<n;i++){
        cout<<" p"<<arr[i].id<<"\t\t"<<arr[i].arivaltime<<"\t\t"<<temp_burst_time[arr[i].id]<<"\t\t"<<arr[i].compeltiontime<<"\t\t\t"<<arr[i].turnaroundtime<<"\t\t\t"<<arr[i].waitingtime<<endl;
    }
}
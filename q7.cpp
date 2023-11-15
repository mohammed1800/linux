#include<iostream>
#include<algorithm>
using namespace std;

// fcfs
int main(){
    
    cout<<"Enter the process:";
    int process,p=1;
    cin>>process;
    
    int arrival[process],burst[process],comp[process],wat[process],tat[process],temp[process],temp1[process];
    
    for(int i=0;i<process;i++){
        cout<<"Enter the arrival time of "<<p++<<":";
        cin>>arrival[i];
        temp[i]=arrival[i];
    }
    
    sort(temp,temp+process);
    p=1;
    for(int i=0;i<process;i++){
        cout<<"Enter the burst time of "<<p++<<":";
        cin>>burst[i];
    }
    
    for(int i=0;i<process;i++){
        int value=temp[i],steps=0;
        
        for(int i=0;i<process;i++){
            if(value==arrival[i]){
                break;
            }
            steps++;
                
        }
        
        comp[i]=burst[steps];
        if(i!=0){
            comp[i]+=comp[i-1];
        }
        
        if(i!=0 && temp[i]>comp[i-1]){
            comp[i]+=temp[i]-comp[i-1];
        }
        
        temp1[i]=burst[steps];
    }
    float sum=0,sum1=0;
    for(int i=0;i<process;i++){
        tat[i]=comp[i]-temp[i];
        wat[i]=tat[i]-temp1[i];
        sum+=tat[i];
        sum1+=wat[i];
    }
    cout<<"The average tat time is :"<<sum/process<<endl;
    cout<<"The average wat time is :"<<sum1/process<<endl;
    
    return 0;
}

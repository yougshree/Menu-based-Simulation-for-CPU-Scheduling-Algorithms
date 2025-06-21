#include<bits/stdc++.h>
using namespace std;

int  arrlen = 30;

map<string, float> wait_time;

vector<pair<string, float>> vec;


bool cmp(const pair<string, int> &a, const pair<string, int> &b)
{
    return (a.second < b.second);
}

void sortByVal(map<string, float>& mymap)
{

    // Copy key-value pair from Map
    map<string, float> :: iterator it2;
    for (it2=mymap.begin(); it2!=mymap.end(); it2++)
    {
        vec.push_back(make_pair(it2->first, it2->second));
    }

    // Sort using comparator function
    sort(vec.begin(), vec.end(), cmp);

    // Print the sorted value
    cout << "\nWaiting times after sort: \n" << endl;
    for (int i = 0; i < vec.size(); i++)
    {
        cout << vec[i].first << ": " << vec[i].second << endl;
    }
}


void FCFC_Output(int n, int bt[], int wt[])
{
    int i;
    float awt;
    printf("\nProcesses\tBurst Time\tWaiting Time");

    for(i=0; i<n; i++)
    {
        awt+=wt[i];
        printf("\nP[%d]\t\t%d\t\t%d",i+1,bt[i],wt[i]);
    }

    awt/=n;
    printf("\nAverage waiting time = %f millisecond.", awt);

    wait_time["FCFS"] = awt;

}

void FCFS(int n, int bt[])
{
    printf("\nFCFS CPU Scheduling----\n");
    int i,j,wt[arrlen];
    float awt;

    wt[0]=0;

    for(i=1; i<n; i++)
    {
        wt[i]=0;
        for(j=0; j<i; j++)
            wt[i]+=bt[j];
    }

    FCFC_Output(n, bt, wt);

}

void SJF_preemptive(int n, int bt[], int at[])
{
    printf("\n\nSJF-preemptive CPU Scheduling----\n");
    int rt[arrlen],endTime,i,smallest; //at[arrlen],

    int remain=0,time;
    float awt;


    for(i=0; i<n; i++)
    {

        rt[i]=bt[i];
    }

    printf("\nProcess\tWaiting Time");
    rt[9]=9999;

    for(time=0; remain!=n; time++)
    {
        smallest=9;

        for(i=0; i<n; i++)
        {
            if(at[i]<=time && rt[i]<rt[smallest] && rt[i]>0)
            {

                smallest=i;

            }
        }

        rt[smallest]--;

        if(rt[smallest]==0)
        {

            remain++;

            endTime=time+1;

            printf("\nP[%d]\t\t%d",smallest+1,endTime-bt[smallest]-at[smallest]);

            awt+=endTime-bt[smallest]-at[smallest];
        }
    }
    awt/=n;
    printf("\nAverage waiting time = %f millisecond.", awt);

    wait_time["SJF_p"] = awt;


}
void SJF_nonpreemptive(int n, int bt[])
{
    printf("\n\nSJF-nonpreemptive CPU Scheduling----\n");
    int i,j,total=0,pos,temp,p[arrlen],wt[arrlen];
    float awt;

    for(i=0; i<n; i++)
    {

        p[i]=i+1;
    }

    for(i=0; i<n; i++)
    {
        for(j=0; j<n-1; j++)
        {
            if(bt[j]>bt[j+1])
            {
                temp=bt[j];
                bt[j]=bt[j+1];
                bt[j+1]=temp;

                temp=p[j];
                p[j]=p[j+1];
                p[j+1]=temp;
            }
        }
    }
    printf("\nProcess\tBurst Time\tWaiting Time");

    for(i=0; i<n; i++)
    {
        wt[i]=0;

        for(j=0; j<i; j++)
        {
            wt[i]+=bt[j];
        }
        awt+=wt[i];
        printf("\np[%d]\t\t%d\t\t%d ",p[i],bt[i],wt[i]);

    }
    awt=awt/n;
    printf("\nAverage Waiting Time = %f millisecond.",awt);
    wait_time["SJF_np"] = awt;
}

void Round_Robin_preemptive(int n, int bt[], int at[])
{

    printf("\n\nRound Robin_Preemptive CPU Scheduling----\n\n");
    int i, sum=0,count=0, j, quant, wt=0, temp[arrlen];
    float awt;

    j =n;

    for(i=0; i<n; i++)
    {

        temp[i] = bt[i];
    }
    printf("Enter the Time Quantum for the process: ");
    scanf("%d", &quant);
    printf("Process No \tArrival Time \t Burst Time \t Waiting Time ");
    for(sum=0, i = 0; j!=0; )
    {
        if(temp[i] <= quant && temp[i] > 0)
        {
            sum = sum + temp[i];
            temp[i] = 0;
            count=1;
        }
        else if(temp[i] > 0)
        {
            temp[i] = temp[i] - quant;
            sum = sum + quant;
        }
        if(temp[i]==0 && count==1)
        {
            j--;
            printf("\nProcess No[%d]\t%d\t\t %d\t\t %d",i+1,at[i],bt[i],sum-at[i]-bt[i]);
            wt = wt+sum-at[i]-bt[i];

            count =0;
        }
        if(i==n-1)
        {
            i=0;
        }
        else if(at[i+1]<=sum)
        {
            i++;
        }
        else
        {
            i=0;
        }
    }
    awt= wt/n;
    printf("\nAverage waiting time = %f millisecond.", awt);
    wait_time["RR_P"] = awt;
}
void Round_Robin_nonpreemptive(int n, int bt[])
{
    printf("\n\nRound Robin-nonpreemptive CPU Scheduling----\n\n");
    int i, qt, count = 0, temp, sq = 0,wt[arrlen], rem_bt[arrlen],tat[arrlen];
    float awt = 0;


    for (i = 0; i < n; i++)
    {


        rem_bt[i] = bt[i];

    }

    printf ("Enter the quantam time: ");
    scanf ("%d", &qt);

    while (1)

    {
        for (i = 0, count = 0; i < n; i++)
        {
            temp = qt;
            if (rem_bt[i] == 0)

            {
                count++;
                continue;
            }

            if (rem_bt[i] > qt)
                rem_bt[i] = rem_bt[i] - qt;

            else if (rem_bt[i] >= 0)

            {
                temp = rem_bt[i];
                rem_bt[i] = 0;
            }
            sq = sq + temp;
            tat[i] = sq;
        }

        if (n == count)
            break;
    }
    printf("\nProcess \tBurst Time\tTurn around time\tWaiting Time");

    for (i = 0; i < n; i++)
    {
        wt[i]=tat[i]-bt[i];
        awt=awt+wt[i];
        printf ("\nP[%d]\t\t%d\t\t%d\t\t\t%d",i + 1, bt[i],tat[i],wt[i]);

    }

    awt /= n;
    printf("\nAverage waiting time = %f millisecond.", awt);
    wait_time["RR_np"] = awt;

}
void Priority_Scheduling_preemptive(int n, int bt[],int at[])
{


    printf("\nPriority Scheduling_Preemptive CPU Scheduling----\n");
    int pt[arrlen],wt[arrlen],temp[arrlen],t,count=0,short_p;
    float awt;

    printf("Enter Priority of the process: ");
    printf(" Priority\n");

    for(int i=0; i<n; i++)
    {

        temp[i]=bt[i];
    }
    printf("\nPriority:\n");
    for(int i=0; i<n; i++)
    {
        printf("P[%d]:",i+1);
        scanf("%d",&pt[i]);

    }

    pt[9]=10000;

    for(t=0; count!=n; t++)
    {
        short_p=9;
        for(int i=0; i<n; i++)
        {
            if(pt[short_p]>pt[i] && at[i]<=t && bt[i]>0)
            {
                short_p=i;
            }
        }

        bt[short_p]=bt[short_p]-1;


        if(bt[short_p]==0)
        {
            count++;
            wt[short_p]=t+1-at[short_p]-temp[short_p];
            awt=awt+wt[short_p];
        }
    }

    awt=awt/n;
    printf("Process_ID Arrival Time Priority Wating Time\n");
    for(int i=0; i<n; i++)
    {
        printf("%d\t\t%d\t%d\t%d\n",i+1,at[i],pt[i],wt[i]);
    }

    printf("\nAverage waiting time = %f millisecond.", awt);
    wait_time["Prio_P"] = awt;
}

void Priority_Scheduling_nonpreemptive(int n, int bt[])
{
    printf("\n\nPriority Scheduling_Nonpreemptive CPU Scheduling----\n");
    int p[arrlen],wt[arrlen],pr[arrlen],i,j,pos,temp;
    float awt;


    printf("\nEnter Priority:\n");
    for(i=0; i<n; i++)
    {

        printf("P[%d]:",i+1);
        scanf("%d",&pr[i]);
        p[i]=i+1;
    }

    for(i=0; i<n; i++)
    {
        pos=i;
        for(j=i+1; j<n; j++)
        {
            if(pr[j]<pr[pos])
                pos=j;
        }

        temp=pr[i];
        pr[i]=pr[pos];
        pr[pos]=temp;

        temp=bt[i];
        bt[i]=bt[pos];
        bt[pos]=temp;

        temp=p[i];
        p[i]=p[pos];
        p[pos]=temp;
    }

    wt[0]=0;
    for(i=1; i<n; i++)
    {
        wt[i]=0;
        for(j=0; j<i; j++)
            wt[i]+=bt[j];

        awt+=wt[i];
    }



    printf("\nProcess\tBurst Time\tWaiting Time");
    for(i=0; i<n; i++)
    {

        printf("\nP[%d]\t\t%d\t\t%d\t\t\t",p[i],bt[i],wt[i]);
    }

    awt/=n;

    printf("\nAverage Waiting Time=%f millisecond.",awt);
    wait_time["Prio_np"] = awt;

}
void algo_choice(int ch, int n, int bt[], int at[])
{
    switch(ch)
    {
    case 1:
        FCFS(n,bt);
        break;
    case 2:
        SJF_preemptive(n,bt, at);
        break;
    case 3:
        SJF_nonpreemptive(n,bt);
        break;
    case 4:
        Round_Robin_preemptive (n,bt,at);
        break;
    case 5:
        Round_Robin_nonpreemptive(n,bt);
        break;
    case 6:
        Priority_Scheduling_preemptive(n,bt,at);
        break;
    case 7:
        Priority_Scheduling_nonpreemptive(n,bt);
        break;
    case 8:
        printf("ALL----\n");

        FCFS(n,bt);
        SJF_preemptive(n,bt,at);
        SJF_nonpreemptive(n,bt);
        Round_Robin_preemptive (n,bt,at);
        Round_Robin_nonpreemptive(n,bt);
        Priority_Scheduling_preemptive(n,bt,at);
        Priority_Scheduling_nonpreemptive(n,bt);

        cout << "\n\nWaiting times before sort: \n" << endl;
        for (auto i = wait_time.begin(); i != wait_time.end(); i++)
            cout << i->first << "      " << i->second << endl;

        //Sort wait_time map in ascending order
        sortByVal(wait_time);

        //Print best one acc to avg waiting time, Fist element from map
        cout << "\nThe best algorithm acc to avg waiting time is :  " << vec[0].first << "    " << vec[0].second << endl;

        //Print worst one acc to avg waiting time, Last element from map
        cout << "\nThe worst algorithm acc to avg waiting time is :  " << vec[vec.size()-1].first << "    " << vec[vec.size()-1].second << endl;

        break;

    default:
        printf("Invalid choice!!");
        break;

    }
    int c;
    printf("\nDo u want to countinue?(1/0)");
    printf("\npress '1' to countinue and press '0' to exit-");
    scanf("%d",&c);
    if (c == 1)
    {
        printf("\nChoose your option below\n");
        printf("1.FCFS\n2.SJF_preemptive\n3.SJF_nonpreemptive\n4.Round_Robin_preemtive\n5.Round_Robin_nonpreemtive\n6.Priority_Scheduling_preemptive\n7.Priority_Scheduling_nonpreemptive\n8.All\n");

        printf("\nOption: ");
        int choice;
        scanf("%d",&choice);
        algo_choice(choice, n, bt,at);
    }
}

int main()
{
    //int c;

    //------modify----------//
    int n;
    printf("Enter Total Number of Process: ");
    scanf("%d",&n);

    int burst_time[n];
    printf("\nEnter The Processes Burst Time:\n");
    for (int i = 0; i < n; i++)
    {
        printf("P[%d]:",i+1);
        int bt;
        scanf("%d",&bt);
        burst_time[i] = bt;
    }

    int Arrival_time[n];
    printf("\nEnter The Processes Arrival time Time:\n");
    for (int i = 0; i < n; i++)
    {
        printf("P[%d]:",i+1);
        int at;
        scanf("%d",&at);
        Arrival_time[i] = at;
    }

    printf("\nChoose your option below\n");
    printf("1.FCFS\n2.SJF_preemptive\n3.SJF_nonpreemptive\n4.Round_Robin_preemptive\n5.Round_Robin_nonpreemtive\n6.Priority_Scheduling_preemptive\n7.Priority_Scheduling_nonpreemptive\n8.All\n");

    printf("\nOption: ");
    int choice;
    scanf("%d",&choice);
    algo_choice(choice, n, burst_time, Arrival_time);

    return 0;

}





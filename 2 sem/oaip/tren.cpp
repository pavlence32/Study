#include <iostream>
#include <ctime>
using namespace std;                     
struct Stack{
int data;
struct Stack * next;
};

Stack * push(struct Stack * nach,int data)
{
Stack * ptr = new struct Stack; 
ptr->data=data;
ptr->next=nach;
return ptr;
}
void pros(Stack * nach)
{
    Stack * t =nach;

while(t!=NULL)
{
    cout<<t->data<<endl;
    t=t->next;
}
}
Stack * del(Stack * nach)
{
 if(nach==NULL)
    return nach;
Stack * t=nach->next;
delete nach;
return t;
}
void indiv(Stack * nach)
{
Stack * ptr = nach;
int max = ptr->data;
while(ptr!=NULL)
{
    if(ptr->data>max)
    max=ptr->data;
    ptr=ptr->next;
}
Stack *nach_2=NULL;
ptr=nach->next;
while(ptr->data!=max)
{   
    nach_2=push(nach_2,ptr->data);
    ptr=ptr->next;
    }
pros(nach_2);
}
void Sort1(Stack ** p)
{
 Stack * t=NULL,*t1,*r1;
 if ((*p)->next->next==NULL)
     return;
*p=push(*p,1);
do
{
   for(t1=*p;t1->next->next!=t;t1=t1->next)
   {
    if(t1->next->data>t1->next->next->data)
    {
        r1 = t1->next->next;
        t1 -> next -> next = r1 -> next;
        r1-> next =t1-> next;
        t1-> next = r1;
    }
   }
   t= t1-> next;
} while ((*p)-> next -> next != t);
*p=(*p)->next;
}
void sortinfo(Stack * p)
{
    Stack * t=NULL,*t1;
    int buf;
do 
{
    for(t1=p;t1->next!=t;t1=t1->next)
    {
        if(t1->data>t1->next->data)
        {
        buf=t1->next->data;
        t1->next->data=t1->data;
        t1->data=buf;
        }
    }
    t=t1;
} while (p -> next != t);
}
int main()
{
srand(time(NULL));
Stack * nach=NULL;
int chos=0,n=0,chos1;
while(true)
{
cout<<"1-Creat"<<endl;
cout<<"2-Add"<<endl;
cout<<"3-View"<<"\n";
cout<<"4-Del"<<endl;
cout<<"5-Individa"<<endl;
cout<<"6-Sortadress"<<endl;
cout<<"7-Sortinfo"<<endl;
cout<<"0-Exit"<<endl;
cin>>chos;
switch (chos)
{
    case 1:
    int m;
    cout<<"how many members: ";
    cin>>m;
    for(int i=0;i<m;i++)
    nach=push(nach,rand() % 101-30);
    break;
    case 2:
    cout<<"what add"<<"\n";
    cin>>n;
    nach=push(nach,n);
    break;
    case 3:
    pros(nach);
    break;
    case 4:
    del(nach);
    break;
    case 5:
    indiv(nach);
    break;
    case 6:
    Sort1(&nach);
    break;
    case 7:
    sortinfo(nach);
    break;
    case 0:
    cout<<"exit";
    return 0;
    default:
    cout<<"Error";
    break;
}
}
return 0;
}
#include <iostream>
#include <cmath>
using namespace std;
double raschet(double a,double x,double xpref)
{
    x=0.5*(x+a/x);
     if (xpref==x)
    return x;
    xpref=x;
    return raschet(a,x,xpref);
}
double raschet2(double a1,double x1,double xpref1)
{
    for(int i=0;i<100;i++)
    {
       x1=0.5*(x1+a1/x1);
         if (xpref1==x1)
         return x1;
         xpref1=x1;
    }
}
int main()
{
    double y1,a1,xpref=0,a,x,xpref1=0,x1;
    cout<<"enter a"<<endl;
    cin>>a;
    if(a==0)
    {
        cout<<"no correct";return 0;
    }
    if(!cin.good()){
    cout<<"mistake";return 0;}
    a1=a;
    x=0.5*(1+a);
    x1=x;
    y1=raschet2(a1,x1,xpref1);
    x=raschet(a,x,xpref);
    cout<<"x="<<x<<" "<<"x1="<<y1<<endl;
    if(x>y1)
    {
        cout<<"x>x1";return 0;
    }
    if (x<y1)
    {
        cout<<"x1>x";return 0;
    }
    else{
        cout<<"x1=x";return 0;
    }
    cout<<sqrt(a);
}
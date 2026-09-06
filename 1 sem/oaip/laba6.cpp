#include <iostream>
#include <cstring>
using namespace std;
int main()
{ 
    int nachalo=0;
    int konec=0;
    int g=0;
    char string[20];
    char a[20];
    bool foundchislo=false;
    bool point=false;
cout<<"enter symbols"<<endl;
cin.getline(string, 20);
for(int k=0;k<20;k++)
{
   if((string[k]>='0'&&string[k]<='9')||string[k]=='-')
   {
  nachalo=k;
  g=k;
  foundchislo=true;
  break;
   }
}
if(foundchislo==false)
{
    cout<<"no members";
    return 0;
}
int u=g+1;
   while(string[u] !='\0'  && 
      ((string[u] >= '0' && string[u] <= '9') || string[u] == '.'))
   {
konec=u;
u++;
   }
  
strncpy(a, string + nachalo, konec - nachalo + 1);
    a[konec - nachalo + 1] = '\0';
cout<<a<<endl;
   return 0;
}
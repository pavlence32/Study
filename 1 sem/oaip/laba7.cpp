#include <iostream>
#include <cstring>
using namespace std;
struct Students{
    char surname[30];
    int nomer;
    int ocenfiz;
    int ocenmatem;
    int oceninfo;
    float average;
};
int createfile(const char* filename)
{
    FILE *p;
    p=fopen(filename,"w");
    if(p==NULL){
    cout<<"error";return 1;}
    int n=0;
    cout<<" enter number of students"<<'\n';
    cin >> n;
    for (int i=0;i<n;i++)
    {
        Students s;
        cout<<"surname"<<'\n';
        cin>>s.surname;
        cout<<"group"<<'\n';
        cin>> s.nomer;
        cout<<"otmetka matem"<<'\n';
        cin>>s.ocenmatem;
        cout<<"otmetka fizika"<<'\n';
        cin>>s.ocenfiz;
        cout<<"otmetka informatika"<<'\n';
        cin>>s.oceninfo;

        s.average=(s.ocenfiz+s.ocenmatem+s.oceninfo)/3.0;

    
    fprintf(p,"%s %d %d %d %d %.2f\n",
    s.surname,s.nomer,
    s.ocenmatem,s.ocenfiz,s.oceninfo,
    s.average);
    }
if(fclose(p)==EOF){
cout<<"error";return 1;}
return 0;

}
int prosmotr(const char * filename)
{
    FILE * p;
    p=fopen(filename,"r");
    if(p==NULL)
    {cout<<"error";return 1;}
    Students s;
   while( fscanf(p,"%s %d %d %d %d %f",
    s.surname,&s.nomer,
    &s.ocenmatem,&s.ocenfiz,&s.oceninfo,
    &s.average)==6){
        cout<<"surname "<<s.surname<<endl;
        cout<<"nomer "<<s.nomer<<endl;
        cout<<"otmetka matem "<<s.ocenmatem<<endl;
        cout<<"otmetka fizika "<<s.ocenfiz<<endl;
        cout<<"otmetka info "<<s.oceninfo<<endl;
        cout<<"sredniy "<<s.average<<endl;
       

    }
     if(fclose(p)==EOF){
        cout<<"error";return 1;}
        return 0;
}
int dobav(const char * filename)
{
    FILE * p;
    p=fopen(filename,"a");
    if(p==NULL){
        cout<<"error";return 1;
    }
    int n=0;
    cout<<"how many students you would like to add?"<<'\n';
    cin>>n;
    for(int i=0;i<n;i++)
    {Students s;
    cout<<"surname"<<'\n';
    cin>>s.surname;
    cout<<"group"<<'\n';
    cin>>s.nomer;
    cout<<"otmetka matem"<<'\n';
    cin>>s.ocenmatem;
    cout<<"otmetka fizika"<<'\n';
    cin>>s.ocenfiz;
    cout<<"otmetka informatika"<<'\n';
    cin>>s.oceninfo;
     s.average=(s.ocenfiz+s.ocenmatem+s.oceninfo)/3.0;

    
    fprintf(p,"%s %d %d %d %d %.2f\n",
    s.surname,s.nomer,
    s.ocenmatem,s.ocenfiz,s.oceninfo,
    s.average);
    }
    
if(fclose(p)==EOF){
cout<<"error";return 1;}
return 0;
}
int poisk(const char * filename)
{
    FILE *p;
    p=fopen(filename,"r");
    if(p==NULL){
        cout<<"error";return 1;

    }
    Students s;
    bool found=false;
     while (fscanf(p,"%s %d %d %d %d %f",
                  s.surname, &s.nomer,
                  &s.ocenmatem, &s.ocenfiz,
                  &s.oceninfo, &s.average) == 6){
    if(s.oceninfo>4 && s.ocenmatem>4)
    {
        cout<<s.surname<<endl;
        found=true;
    }
    
    }
    if(found==false)
    {cout<<"no one";return 0;}
        if(fclose(p)==EOF){
        cout<<"error";return 1;}
        
return 0;
}
int redaktir(const char * filename)
{
    FILE *p;
    p=fopen(filename,"r+");
    Students arr[100];
    int n=0;
    while(fscanf(p,"%s %d %d %d %d %f",arr[n].surname,&arr[n].nomer,&arr[n].ocenmatem,&arr[n].ocenfiz,&arr[n].oceninfo,&arr[n].average)==6)
    {
        n++;
    }
    fclose(p);
    char izmen[13];
    cout<<"kogo menyem"<<endl;
    cin.ignore();
    cin.getline(izmen,13);
    for(int i=0;i<n;i++)
    {
        if(strcmp(arr[i].surname,izmen)==0)
        {
            cout<<"what will we changed?"<<endl;
            int choice;
            cout<<"1-surname "<<endl;
            cout<<"2-group "<<endl;
            cout<<"3-ocen matem "<<endl;
            cout<<"4-ocen fiz "<<endl;
            cout<<"5-ocen info "<<endl;
            cin>>choice;
            switch (choice){
                case 1:
                cout<<"new surname:";
                cin>>arr[i].surname;
                break;
                case 2:
                cout<<"new group:";
                cin>>arr[i].nomer;
                break;
                case 3:
                cout<<"new mark";
                cin>>arr[i].ocenmatem;
                cout<<"new mark"<<arr[i].ocenmatem;
                break;
                case 4:
                cout<<"new mark";
                cin>>arr[i].ocenfiz;
                cout<<"new mark"<<arr[i].ocenfiz;
                break;
                case 5:
                cout<<"new mark";
                cin>>arr[i].oceninfo;
                cout<<"new mark"<<arr[i].oceninfo;
                break;
            }
            arr[i].average=(arr[i].ocenmatem+arr[i].ocenfiz+arr[i].oceninfo)/3;
        }
    }
        p=fopen(filename,"w");
        for(int i=0;i<n;i++){
        fprintf(p,"%s %d %d %d %d %.2f\n",
    arr[i].surname,arr[i].nomer,
    arr[i].ocenmatem,arr[i].ocenfiz,arr[i].oceninfo,
    arr[i].average);
        }
    if(fclose(p)==EOF){
cout<<"error";return 1;}
    
   return 0;
}
int ydalen(const char * filename)
{
    FILE * p;
    p=fopen(filename,"r+");
   Students arr[100];
   int n=0;
   while(fscanf(p,"%s %d %d %d %d %f",arr[n].surname,&arr[n].nomer,
              &arr[n].ocenmatem, &arr[n].ocenfiz,
              &arr[n].oceninfo, &arr[n].average) == 6){
n++;
              }
              char izmen[30];
              cout<<"enter which student we will changed: ";
              cin.ignore();
              cin.getline(izmen,30);
              
               p = fopen(filename,"w");
    for(int i=0;i<n;i++){if(strcmp(arr[i].surname,izmen)!=0)
        {fprintf(p,"%s %d %d %d %d %.2f\n",
                arr[i].surname, arr[i].nomer,
                arr[i].ocenmatem, arr[i].ocenfiz,
                arr[i].oceninfo, arr[i].average);
        }
    }
   if(fclose(p)==EOF){
cout<<"error";return 1;}
    
return 0;

}
int sortfam(const char * filename)
{
    FILE * p;
    p=fopen(filename,"r+");
    Students arr[100];
    int n=0;
    while(fscanf(p,"%s %d %d %d %d %f",
              arr[n].surname, &arr[n].nomer,
              &arr[n].ocenmatem, &arr[n].ocenfiz,
              &arr[n].oceninfo, &arr[n].average) == 6){
                n++;
              }
     if(fclose(p)==EOF){
        cout<<"error";return 1;} 
        for(int i=0;i<n;i++)
        {
            for(int j=0;j<n-1;j++)
            {
                if(strcmp(arr[j].surname,arr[j+1].surname)>0)
                {
                    Students temp=arr[j];
                    arr[j]=arr[j+1];
                    arr[j+1]=temp;
                }
            }
        } 

        p=fopen(filename,"r+");
 for(int i=0;i<n;i++){
        fprintf(p,"%s %d %d %d %d %.2f\n",
                arr[i].surname, arr[i].nomer,
                arr[i].ocenmatem, arr[i].ocenfiz,
                arr[i].oceninfo, arr[i].average);
    }
       if(fclose(p)==EOF){
cout<<"error";return 1;}
        return 0;
}
int sortmark(const char * filename)
{
    FILE * p;
    p=fopen(filename,"r");
    Students arr [100];
    int n=0;
     while(fscanf(p,"%s %d %d %d %d %f",
              arr[n].surname, &arr[n].nomer,
              &arr[n].ocenmatem, &arr[n].ocenfiz,
              &arr[n].oceninfo, &arr[n].average) == 6){
                n++;
              }
              fclose(p);
              for (int i = 0; i < n; i++) {
    int a = arr[i].ocenmatem;
    int b = arr[i].ocenfiz;
    int c = arr[i].oceninfo;


    
    if (a < b) {
            int temp = a;
            a = b;
            b = temp;
        }
        if (b < c) {
            int temp = b;
            b = c;
            c = temp;
        }
        if (a < b) {  
            int temp = a;
            a = b;
            b = temp;
        }

    
   

    
    arr[i].ocenmatem = a;
    arr[i].ocenfiz   = b;
    arr[i].oceninfo  = c;
    arr[i].average   = (a + b + c) / 3.0;
 
    
    
}
p=fopen(filename,"w");
 for(int i=0;i<n;i++){
        fprintf(p,"%s %d %d %d %d %.2f\n",
                arr[i].surname, arr[i].nomer,
                arr[i].ocenmatem, arr[i].ocenfiz,
                arr[i].oceninfo, arr[i].average);


}
if(fclose(p)==EOF){
cout<<"error";return 1;}
return 0;
}



int main()
{int choice_vod=0;
    int choose=0;
    bool prodolsh=true;
    do{
    cout<<"choose operations"<<endl;
    cout<<"1-Create"<<endl;
    cout<<"2-prosmotr"<<endl;
    cout<<"3-dobavlenie"<<endl;
    cout<<"4-ucpevaemost"<<endl;
    cout<<"5-redakt"<<endl;
    cout<<"6-delete"<<endl;
    cout<<"7-sortfam"<<endl;
    cout<<"8-sortmark"<<endl;
    cin>>choice_vod;
    switch(choice_vod){
        case 1:
        createfile("laba.txt");
        break;
        case 2:
        prosmotr("laba.txt");
        break;
        case 3:
        dobav("laba.txt");
        break;
        case 4:
        poisk("laba.txt");
        break;
        case 5:
        redaktir("laba.txt");
        break;
        case 6:
        ydalen("laba.txt");
        break;
        case 7:
        sortfam("laba.txt");
        break;
        case 8:
        sortmark("laba.txt");
        break;
    }
    cout<<endl;
cout<<"would like to continue"<<endl;
cout<<"1-yes"<<endl;
cout<<"2-no"<<endl;
cin>>choose;
if(choose==2)
prodolsh=false;
    

    
} while(prodolsh==true);
return 0;
}
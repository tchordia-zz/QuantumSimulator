#include <iostream>
#include <string>

using namespace std;

int size = 6 * 8;

char *start = (char*) calloc(size, 1);
char *p = start;

char z = '\0';
char o  = '\377';


void l()
{
    p--;
}

void r()
{
    p++;
}
void r(int a){
    p = p + a;
}

void f()
{
    *p = ~*p;
}
void s(){
    p = start;
}

void e(){
    p = start + size;
}

void in(string command)
{
    //char* start = (char*) malloc(command.length)
    
    int i=0;
    while(i < command.length())
    {
        char temp = command[i];
        
        if(temp == 'f'){f();}
        else if(temp == 'r'){r();}
        else if(temp == 'l'){l();}
        else if(temp == 's'){s();}
        else if(temp == 'e'){e();}

        
        i++;
    }
    
    
}


void initAdder()
{
    string command = "11111111 00000010";
    int i=0;
    in("s");
    while(i < command.length())
    {
        char temp = command[i];
        
        if(temp == '1'){in("fr");}
        else if(temp == '0'){in("r");}
       
        
        
        i++;
    }

    
}

void printVal(string s, char* c)
{
    if(*c == o)
    {
        cout<< s << "" << 1 << "";
    }
    else if (*c == z)
    {
        cout << s << ""<< 0 << "";
    }
    else {
        cout << s << ">" << *c << "<";
    }
    
}

void printVal(string s, char c)
{
    if(c == o)
    {
        cout<< s << "" << 1 << "\n";
    }
    else if (c == z)
    {
        cout << s << ""<< 0 << "\n";
    }
    else {
        cout << s << ">" << c << "<";
    }
    
}

void printTape()
{
    char* temp = p;
    in("s");
    
    for(int i = 0; i < size; i++)
    {
        printVal("",p);
        in("r");
        if(i%8 == 7)
        {
            cout<< " ";
        }
    }
    cout << "\n";
    p = temp;
}


void add()
{
    char t3 = '\0';
    for(int j = 7; j > -1; j--)
    {
        s();
    
        r(j);
    
    
        char t1 = *p;
        char t2 = *(p + 8);
        
    
        char x = t1 ^ t2 ^ t3;
        t3 = (t1 & t2) ^ ((t1^t2) & t3);
    
        printVal("x ", x);
        printVal("a ", t3);
    
        r(16);
    
        *p = x;
    
        
    }
    
    
}

void hC( char a, char b)
{
    
}
void addBit(int* point)
{
    
}
//
//int main()
//{
//    
//    
////    in("fr");
//    initAdder();
//    printTape();
//    add();
//    printTape();
//    
//    
//}

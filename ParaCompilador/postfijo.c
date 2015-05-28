/*24/06/05 10:54*/

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <time.h>

/* 
  elaborado por harvin toledo 
  harvintoledo@gmail.com
  

**    **   ******   *******   **    **  ********  **    **     ******** 
**    **  ********  **    **  **    **     **     ***   **     ******** 
**    **  **    **  **    **  **    **     **     ****  **        ** 
********  **    **  ********  **    **     **     ** ** **        ** 
********  ********  *******   ***  ***     **     **  ****        ** 
**    **  ********  *****      ******      **     **   ***        ** 
**    **  **    **  ** **       ****       **     **    **        **  ** 
**    **  **    **  **   ***     **     ********  **    **        **  ** 

*/ 
/*
XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
XXXXXXXXXXXXXXXXXXXXXXXXXXX.XXXXXXXXXXXXXXXXXXXXXX.XXXXXXXXXXXXXXXXXXXXXXXX
XXXXXXXXXXXXXXXXXXXXXXX.XXX..XX.X..XXXXXXXXXXXXXX..XX.XXXXXXXXXXXXXXXXXXXXX
XXXXXXXXXXXXXXXXXXXXXXX...X.X.......XX.XXXXXXXXXX.X...XXX..XXXXXXXXXXXXXXXX
XXXXXXXXXXXXXXXXXXX.XXX........X..X..XXXXXXXX.X........XX..XXXXXXXXXXXXXXXX
XXXXXXXXXXXXXXXXXXX...............XX.XXXXXXX.....X....XXX..XXXXXXXXXXXXXXXX
XXXXXXXXX.XXXXXXX............X..X.XXXXXXXXXX.....X...XXXX..XXXXXXXXXXXXXXXX
XXXXXXX.XX....X................XXXXXXXXXXXXXX...XX.........XXXXXXXXXXXXXXXX
XXXXXXXXXX.................X.X.XXXXXXXXXXXXXX..XXXX..XXXX..XXXXXXXXXXXXXXXX
XXXXXXXXXX..X................X.XXXXXXXXXXXXX....XXX..XXXX..XXXXXXXXXXXXXXXX
XXXXXXXXXXXX.............X..X.XXXXXXXXXXXXXXX...XXX..XXXX..XXXXXXXXXXXXXXXX
XXXXXXXX..XX............X...X.XXXXXXXXXXXXXXXX..XX...XXXX..XXXXXXXXXXXXXXXX
XXXXXXXX...............XXX.X.X.XXXXXX.XXXXXXXXXXXXX..XXXX..XXXXXXXXXXXXXXXX
XXXXXXX................X...X..XXXXXXX.XXXXXXXXXX..XXXXXXXXXXXXXXXXXXXXXXXXX
XXXXXXX.......................XXXXXX.XXXXXXXXX.X..XXXXXXXXXXXXXXXXXXXXXXXXX
XXXXXX..................X.X..XXXXXXXXXXXXXXXXXX....XXXXXXXXXXXXXXXXXXXXXXXX
XXXXXX................X.XXX..XXXXXXXXXXXXXXXXXX....XXXXXXXXXXXXXXXXXXXXXXXX
XXXXXXX..............X..XXXXXXXXXXXXXXXXXXXXXXX..X.XXXXXXXXXXXXXXXXXXXXXXXX
XXXXXXX.................XXXXXXXXXXXXXXXXXXXXXX..XX..XXXXXXXXXXXXXXXXXXXXXXX
XXXXXXX.................XXXXXXXXXXXXXXXXXXXXXX..X...XXXXXXXXXXXXXXXXXXXXXXX
XXXXXXX................XXXXXXXXXXXXXXXXXXXXXXX......XXXXXXXXXXXXXX.XXXXXXXX
XXXXXXX...XX............XXXXXXXXXXXXXXXXXXXXX..XXXX..XXXXXXXXXXXXX.........
XXXXXX...................XXXXXXXXXXXXXXXXXXXX..XXXX..XXXXXXXXXXX...........
XXXXXX..................XXXXXXXXXXXXXXXXXXXXXXXXXXX.......XXXXXXX.X........
XXXXXX.............XXX..XXXXXXXXXXXXXXXXXXXXXXXXXXX..XXXX..XXXXXXXX........
XXXXXX...........XX....XXXXXXXXXXXXXXXXXXXXXXXXXXXX..XXXX..XXXXXXXX........
XXXXXX...........X..XX...XXXXXXXXXXXXXXXXXXXXXXXXXX..XXXX..XXXXXXXX........
XXXXXX............X...XXXXXXXXXXXXXXXXXXXXXXXXXXXXX..XXXX..XXXXXX.XX.......
XXXX....X........X.....XXXXXXXXXXXXXXXXXXXXXXXXXXXX.......XXXXXXX.X........
XXXX....X.........XXXXXXXXXXXXXXXXXX.........XXXXXX..XXX....X.XXXXXX.......
XXXXX....XX.....X.X...XXXXXXXXXXX.XXXXX......XX.XXX..XXXX....XXXXXXX.......
XXXXXX...XX.....X...X.XXXXX.XXXXX......XXX...XXXXXX..XXXX..................
XXXXX....XX....X...XXXXXXXX..XX..XX........X..X..X...XXXXX..XXXX...........
XXXX.....XX...XX...XXXXXXX...XXXX............XX..XXXXXX.XX...XXXXX.........
XXXX...X.XXX......XXXXXXXXX...XXX............XXX..XXXX...X...XXXXXX........
XXXXX....XXXX....XXXXXXXXX.....XXX........X...XXXXXXXX...XX.....XXXX.......
XXXXX....X.XX...XXXXXXXXXX.......X.....X....XXXX.XXXX......XXXXXXXXXX......
XXXXX....X.X....XXXXXXXXXX........XX..........XX.XXXX........XXXX..........
XXXXXX.....X...XXXXXXXXXXXX....................X.XXX.......................
XXXXXX.........XXXXXXXXXXXX....................XXXX...............X........
XXXXXX.........XXXXXXXXXXXXX.........XXX.......XXXX...............X........
XXXXXX....X....XXXXXXXX.XXXXX.......XXXXXXXX....XX.............X...X.......
XXXXXX.........XX.XX.....XXX........XXXXXXXXX..XXX.............XX..........
XXXXXXX...........XXX...X.XX.....XXXXXXXXXX.X...X..XX......................
XXXXXXX..........XXXXXXX.XXX...X.XX.XXXXX..........XX.............X........
XXXXXXX........X..X......XXX.....XXXXXXXXXX........XX..............X.......
XXXXXXXXXX....XXX......XXXX........X.XXX..X........XX......................
XXXXXXXXXX...XXXXX...X.XXXX..........XXXXX.X.X.....XX......................
XXXXXXXXX....XXXX...X.XXXX............X..X.X.......XX......................
XXXXXXXXXX...XXXXXX.X.XXX..........XX......X.......XX......................
XXXXXXXXXX..XXXXXXX..XX..............XX.X..........XX......................
XXXXXXXXXX..XXX......X.............................XXX.....................
XXXXXXXXXX..XX.......XX............................XX....XX................
XXXXXXXXXX..X.......XX........................XX....XX..X.X................
XXXXXXXXX...........X.........................XXX...XX.X..X..X.............
XXXXXXXX...........X..........................XXXX..XX.X.XX..XX............
XXXXXXX.......X...XX..........................XXXX..XXX..XXX.X..X..........
XXXXXX............XX..........................XX.XX.XXX.X.X................
XXXXXX.......X.....XX.........................XX.XX.XXX.XX.................
XXXXX........XX....XXXX.......................XX..XXXX.XX..................
XXXX........XX...X...XXXX...X...............X.XX..XXXX...X.................
XXX.......XXXX..XX.....XX.....................XX...XXX..XX.................
XX........XXXXX.XXX.XXX.X.....................XX..X.XXX....................
X.........XXX.XXXXXXXXXXX..X........................XXXXX..................
..........XXX..XXXXXXXXXXXXX.................X....X.XX..XX.................
..........XXX.XXXXXXXXXXXXXX......................XXX....X....XX......XX...
..........XXXXXXXXXXXXXXXXXX.......................XX.........XX......XX...
..........XXXXXXXXXXX..XXXXXXXX....................XX.........XX......XX...
..........XXXXXX..XXXX....XXXXX....................XX.......XXXXXX..XXXXXX.
...........XXX.......XX...XXXX.....................XX.........XX......XX...
...........XXX...........XXXXX.....................XX....X....XX......XX...
...........XXXX..........XXXXXX.....................XX..XX....XX......XX...
............XXXX..........XXXXX......................XXXX..................
............XXXXXX........XXXXXX...........................................
...........................................................................

*/
#define  PI  3.14159265358979323846
#define  E   2.71828182845904523536
#define  R2  1.41421356237309504880

#define ELEMENTOS 65535 
#define PAREN_DER 0 
#define PAREN_IZ  1 
#define FUNCION   4
#define VARIABLE  6 
#define si        1
#define no        0
#define ALFABETO  26
#define MAXTERM   50
double res=0.0;
char expr[ELEMENTOS],expr1[ELEMENTOS], expr2[ELEMENTOS], 
     nuevaC[ELEMENTOS], num[30];
double var[ALFABETO];
int    chk[ALFABETO];
typedef double dato;
struct pila
{
  dato d;
  struct pila *siguiente;
};
typedef struct pila nodo;

struct stCom
{
  double re;
  double im;
};

typedef struct stCom complex;
struct stPilaComp
{
  complex d;
  struct stPilaComp *siguiente;
};
typedef struct stPilaComp nodoComplex;

struct stString
{
  char elem[200];
  struct stString *siguiente;
};

typedef struct stString String;

complex iPos={0.0,1.0}; 
complex iNeg={0.0,-1.0}; 
complex unoPos={1.0,0.0};
complex unoNeg={-1.0,0.0};


nodoComplex *NuevoElementoComplex()
{
  nodoComplex *p;
  p=(nodoComplex *)malloc(sizeof(nodoComplex));
  return(p);
}

void pushComplex(nodoComplex **p, complex x)
{
  nodoComplex *q, *r;
  r=*p;
  q=NuevoElementoComplex();
  q->d=x;
   
  q->siguiente=r;
  r=q;
  *p=r;
}

complex popComplex(nodoComplex **p)
{
  nodoComplex *q;
  complex x;
  q=*p;
  if(q==NULL)
  {
    printf("\nPILA VACIA!, PRESIONE CUALQUIER TECLA PARA SALIR DE PROGRAMA");
    getchar();
    exit(0);
  }
  else
  {
    x=q->d;
    *p=q->siguiente;
    free(q);
    return(x);
  }
}

String *NuevoElementoString()
{
  String *p;
  p=(String *)malloc(sizeof(String));
  return(p);
}

void pushString(String **p, char x[])
{
  String *q, *r;
  r=*p;
  q=NuevoElementoString();
  strcpy(q->elem,x); 
  q->siguiente=r;
  r=q;
  *p=r;
}

void popString(String **p,char x[])
{
  String *q;
  
  q=*p;
  if(q==NULL)
  {
    printf("\nPILA VACIA!, PRESIONE CUALQUIER TECLA PARA SALIR DE PROGRAMA");
    getchar();
    exit(0);
  }
  else
  {
    strcpy(x,q->elem);
    *p=q->siguiente;
    free(q);
    return;
  }
}


void Presentacion()
{
  printf("**    **  ********   ******    ******   **    **   ******   ********  **    **\n");
  printf("***  ***  ********  ********  ********  ***  ***  ********  ********  **    **\n");
  printf("********  **        **        **    **  ********  **    **     **     **    **\n");
  printf("** ** **  ******    **        **    **  ** ** **  **    **     **     ********\n");
  printf("**    **  ******    **  ****  ********  **    **  ********     **     ********\n");
  printf("**    **  **        **    **  ********  **    **  ********     **     **    **\n");
  printf("**    **  ********  ********  **    **  **    **  **    **     **     **    **\n");
  printf("**    **  ********   ******   **    **  **    **  **    **     **     **    **\n");

}

nodo *NuevoElemento()
{
  nodo *p;
  p=(nodo *)malloc(sizeof(nodo));
  return(p);
}

void push(nodo **p, dato x)
{
  nodo *q, *r;
  r=*p;
  q=NuevoElemento();
  q->d=x;
   
  q->siguiente=r;
  r=q;
  *p=r;
}

dato pop(nodo **p)
{
  nodo *q;
  dato x;
  q=*p;
  if(q==NULL)
  {
    printf("\nPILA VACIA!, PRESIONE CUALQUIER TECLA PARA SALIR DE PROGRAMA");
    getchar();
    exit(0);
  }
  else
  {
    x=q->d;
    *p=q->siguiente;
    free(q);
    return(x);
  }
}

int check_parent(char *s)
{
    unsigned int i=0, cnt=0, correcto=si;
    while( s[i] != '\0')
    {	
			if(s[i] == '(')
			  cnt++;
	    else
	      if( s[i] == ')' )
	        cnt--;
      if(cnt < 0)
      {
        correcto=no;
        return(correcto);
			}
      i++;
    }
    
    if(cnt==0)
      correcto=si;
    else
      correcto=no;
    return(correcto);
}

unsigned int  check_string(char *s, char *searchS, int esta)
{
  unsigned int n, i=0, j=0;
  n=strlen(searchS);
  while(s[i]!='\0')
  {
    if(strnicmp(&s[i], searchS, n)==0)
    {
	    esta=si;
      return(i);
		}
    i++;
	}
	return(i);
}

int check_expr()
{
  return(0);
}

int  present_string(char *s, char *searchS)
{
  unsigned int n, i=0, j=0;
  n=strlen(searchS);
  while(s[i]!='\0')
  {
    if(strnicmp(&s[i], searchS, n)==0)
    {
      return(si);
	}
    i++;
	}
	return(no);
}

int esFuncion(char c)
{ 
  if((c>='a' && c<='z' && c!='i') || c=='!')
    return(si);
  else
    return(no);
}

int esOperador(char c)
{
  switch(c)
  {
	  case '+':case '-':case '*':case '/':case '^':
		  return(si);
		  break;
	  default:
			return(no);
  }
}
int esConstante(char c)
{
  if(c>='A'&& c<='Z')
    return(si);
  else
    return(no);
}
void limpiar_cadena(char *oldS, char *newS)
{
  unsigned int i=0, j=0;
  while(oldS[i]!= '\0')
  {
    if(oldS[i]  == ' ')
      i++;
    else
    if(oldS[i]  == '\t')
      i++;
    else
    if(oldS[i]  == '\n')
      i++;
    else
      newS[j++]=oldS[i++];
  }
  newS[j]='\0';
}


void pretraducir(char *origS, char *newS)
{
  unsigned int i=0, j=0;
  
  while(origS[i] != '\0')
  {
    if(origS[i]=='i')
    {
      if(!esOperador(origS[i+1])&& origS[i+1]!='\0' && origS[i+1]!=')' && origS[i+1]!='!')
      {
        newS[j++]=origS[i++];
        newS[j++]='*';
      }
      else
        newS[j++]=origS[i++];  
    }
    else
    if(strnicmp(&origS[i], "resComp", strlen("resComp"))==0)
    {
      strncpy(&newS[j], "resComp", strlen("resComp"));
      j+=strlen("resComp");
      i+=strlen("resComp");
    }
    else
    if(strnicmp(&origS[i], "res", strlen("res"))==0 || strnicmp(&origS[i], "ans", strlen("ans"))==0)
    {
      
      strncpy(&newS[j],"res",strlen("res"));
      j+=strlen("res");
      i+= strlen("res");
    }
    else
    if(strnicmp(&origS[i], "sqrt", strlen("sqrt"))==0)
    {
      newS[j++]='a';
      i+= strlen("sqrt");
    }
    else
    if(strnicmp(&origS[i], "sin",  strlen("sin"))==0 || strnicmp(&origS[i], "sen",  strlen("sen"))==0)
    {
      newS[j++]='b';
      i+=strlen("sin");
    }
    else
    if(strnicmp(&origS[i], "cos", strlen("cos"))==0 )
    {
      newS[j++]='c';
      i+=strlen("cos");
    }
    else
    if(strnicmp(&origS[i], "tan", strlen("tan"))==0 )
    {
      newS[j++]='d';
      i+=strlen("tan");
    }
    else
    if(strnicmp(&origS[i], "asin", strlen("asin"))==0  || strnicmp(&origS[i], "asen", strlen("asen"))==0)
    {
      newS[j++]='e';
      i+=strlen("asin");
    }
    else
    if(strnicmp(&origS[i], "acos", strlen("acos"))==0)
    {
      newS[j++]='f';
      i+=strlen("acos");
    }
    else
    if(strnicmp(&origS[i], "atan", strlen("atan"))==0)
    {
      newS[j++]='g';
      i+=strlen("atan");
    }
    else    
    if(strnicmp(&origS[i], "exp", strlen("exp"))==0)
    {
      newS[j++]='h';
      i+=strlen("exp");
    }
    else
    if(strnicmp(&origS[i], "ln", strlen("ln"))==0)
    {
      newS[j++]='z';
      i+=strlen("ln");
    }
    else
    if(strnicmp(&origS[i], "log", strlen("log"))==0)
    {
      newS[j++]='k';
      i+=strlen("log");
    }
    else
    if(strnicmp(&origS[i], "sh", strlen("sh"))==0)
    {
      newS[j++]='l';
      i+=strlen("sh");
    }
    else
    if(strnicmp(&origS[i], "ch", strlen("ch"))==0)
    {
      newS[j++]='m';
      i+=strlen("ch");
    }
    else
    if(strnicmp(&origS[i], "th", strlen("th"))==0)
    {
      newS[j++]='n';
      i+=strlen("th");
    }
    else
    if(strnicmp(&origS[i], "ash", strlen("ash"))==0)
    {
      newS[j++]='o';
      i+=strlen("ash");
    }
    else
    if(strnicmp(&origS[i], "ach", strlen("ach"))==0)
    {
      newS[j++]='p';
      i+=strlen("ach");
    }
    else
    if(strnicmp(&origS[i], "ath", strlen("ath"))==0)
    {
      newS[j++]='q';
      i+=strlen("ath");
    }
    else
    if(strnicmp(&origS[i], "pow", strlen("pow"))==0)
    {
      newS[j++]='r';
      i+=strlen("pow");
    }
    else
    if(strnicmp(&origS[i], "gamma'", strlen("gamma'"))==0)
    {
      newS[j++]='w';
      i+=strlen("gamma'");
    }
    else
    if(strnicmp(&origS[i], "factorial", strlen("factorial"))==0)
    {
      newS[j++]='t';
      i+=strlen("factorial");
    }
    else
    if(strnicmp(&origS[i], "betha", strlen("betha"))==0)
    {
      newS[j++]='u';
      i+=strlen("betha");
    }
    else
    if(strnicmp(&origS[i], "prim", strlen("prim"))==0)
    {
      newS[j++]='v';
      i+=strlen("prim");
    }
    else
    if(strnicmp(&origS[i], "gamma", strlen("gamma"))==0)
    {
      newS[j++]='s';
      i+=strlen("gamma");
    }
    else
    if(strnicmp(&origS[i], "pi", strlen("pi"))==0)
    {
      newS[j]='U';
      j++;
      i+=strlen("pi");
    }
    else
    if(strnicmp(&origS[i], "e", strlen("e"))==0)
    {
      newS[j]='V';
      j++;
      i+=strlen("e");
    }
    else
    if(strnicmp(&origS[i], "r2", strlen("r2"))==0)
    {
      newS[j]='W';
      j++;
      i+=strlen("r2");
    }
    else
    if(i==0 && origS[i]=='-')
    {
      newS[j++]='0';
      newS[j++]=origS[i++];
    }
    else
    if(origS[i]=='(' && origS[i+1]=='-')
    {
      newS[j++]=origS[i++];
      newS[j++]='0';
      newS[j++]=origS[i++];
    }
    else
    if( (origS[i]==')') && (origS[i+1]=='('))
    {
      newS[j++]=origS[i++];
      newS[j++]='*';
    }
    else
    if(isalpha(origS[i])  && isalpha(origS[i+1]))
    {
      newS[j++]=toupper(origS[i++]);
      newS[j++]='*';
    }
    else
    if(isalpha(origS[i]) && origS[i+1]=='(')
    {
      newS[j++]=toupper(origS[i++]);
      newS[j++]='*';
    }
    else
    if(origS[i]==')' && isalpha(origS[i+1]))
    {
      newS[j++]=origS[i++];
      newS[j++]='*';
    }
    else
    if(isdigit(origS[i]) && origS[i+1]=='(' )
    {
      newS[j++]=origS[i++];
      newS[j++]='*';
    }
    else
    if(isdigit(origS[i]) && isalpha(origS[i+1]) )
    {
      newS[j++]=origS[i++];
      newS[j++]='*';
    }
    else
    if(isalpha(origS[i]) && isdigit(origS[i+1]))
    {
      newS[j++]=origS[i++];
      newS[j++]='*';
    }  
    else
    if(isalpha(origS[i]))
    {
      newS[j++]=toupper(origS[i++]);
    }
    else
      newS[j++]=origS[i++];
  }
  newS[j]='\0';
  return;
}

void reset_var(int chk[])
{
  long i;
  for(i=0; i<ALFABETO; i++)
    chk[i]=no;  
}

void check_var(char *s, double var[], int chk[])
{
  long i=0;
  chk['U'-'A']=si;
  chk['V'-'A']=si;
  chk['W'-'A']=si;
  while(s[i]!='\0')
  {
    if(esConstante(s[i]) && !chk[s[i]-'A'])
    {
      printf("\n%c=?", tolower(s[i]));
      scanf("%lf", &var[s[i]-'A']);
      chk[s[i]-'A']=si;
    }
    i++;
  }
  return;
}

double factorial(double n)
{
  double t, asintotica, aproximacion, suma=0.0, producto=1.0, func, funcn;
  unsigned int i;
  t=50.0+n;
  asintotica=pow(t,t)*exp(-t)*sqrt(2*PI*t);
  aproximacion=exp(1.0/(12.0*t)-1.0/(360.0*pow(t,3.0))+1.0/(1260*pow(t,5.0))-1.0/(1680.0*pow(t, 7.0)));
  func=asintotica*aproximacion;
  for(i=1; i<=50;i++)
    producto*=(n+(double)i);
  funcn=func/producto;
  return(funcn);
}

double gamma(double x)
{
  double r;
  r=factorial(x-1.0);
  return(r);
}

double w(double x)
{
  double val;
  val=-1.0/(12*pow(x,2.0))+1.0/(120*pow(x,4.0))-1.0/(252*pow(x,6.0))+1.0/(240*pow(x,8.0));
  return(val);
}

double gamma_der(double x)
{
  double t, suma=0.0;
  long i;
  t=x+MAXTERM;
  for(i=0; i<=MAXTERM;i++)
    suma+=1.0/(x+i);
  return(gamma(x)*(log(t)+1/(2*t)+w(t)-suma));
}

double betha(double x, double y)
{
  double r;
  r=factorial(x-1.0)*factorial(y-1.0)/factorial(x+y-1.0);
  return(r);
}

int esPrimo(long n)
{
  long i, r;
  r=(long)sqrt((double)n);
  if(n<=1)
    return(no);
  else
  if(n==2)
    return(si);
  else
  if(n%2==0)
    return(no);
  else
    for(i=3; i<=r; i+=2)
      if(n%i==0)
        return(no);
  return(si);
}

double prim(double k)
{
  long cnt=0, i=1, n;
  n=(long)k;
  while(cnt<n)
  {
    if(esPrimo(i))
      cnt++;
    i++;
  }
  i--;
  return((double)i);
}

double eval_func(char *s, double var[])
{
  double  x, y;
  char cad_num[30];
  unsigned int i=0, j;
  nodo *opndstk;
  fflush(stdin);

  opndstk=NULL;

  while(s[i]!= '\0')
  {
    if(strnicmp(&s[i],"res",strlen("res"))==0)
    {
      push(&opndstk, res);
      i+=strlen("res");
    }
    else
    if(isdigit(s[i]) )
    {
      j=0;
      do
      {
        cad_num[j]=s[i];
        j++;
        i++;
      }
      while(s[i]!=',');
      cad_num[j]='\0';
      x=atof(cad_num);
      push(&opndstk, x);
    }
    else
    if(esOperador(s[i]))
    {
      switch(s[i])
      {
        case '+':
        y=pop(&opndstk);
        x=pop(&opndstk);
        push(&opndstk, x+y);
        break;
        case '-':
        y=pop(&opndstk);
        x=pop(&opndstk);
        push(&opndstk, x-y);
        break;
        case '*':
        y=pop(&opndstk);
        x=pop(&opndstk);
        push(&opndstk, x*y);
        break;
        case '/':
        y=pop(&opndstk);
        x=pop(&opndstk);
        push(&opndstk, x/y);
        break;
        case '^':
        y=pop(&opndstk);
        x=pop(&opndstk);
        push(&opndstk, pow(x,y));
        break;
      }
      i++;
    }
    else
    if(esFuncion(s[i]))
    {
      switch(s[i])
      {
        case 'a':
          x=pop(&opndstk);
          push(&opndstk, sqrt(x));
          break;
        case 'b':
          x=pop(&opndstk);
          push(&opndstk, sin(x));
          break;
        case 'c':
          x=pop(&opndstk);
          push(&opndstk, cos(x));
          break;
        case 'd':
          x=pop(&opndstk);
          push(&opndstk, tan(x));
          break;
        case 'e':
          x=pop(&opndstk);
          push(&opndstk, asin(x));
          break;
        case 'f':
          x=pop(&opndstk);
          push(&opndstk, acos(x));
          break;
        case 'g':
          x=pop(&opndstk);
          push(&opndstk, atan(x));
          break;
        case 'h':
          x=pop(&opndstk);
          push(&opndstk, exp(x));
          break;
        case 'z':
          x=pop(&opndstk);
          push(&opndstk, log(x));
          break;
        case 'k':
          x=pop(&opndstk);
          push(&opndstk, log10(x));
          break;
        case 'l':
          x=pop(&opndstk);
          push(&opndstk, sinh(x));
          break;
        case 'm':
          x=pop(&opndstk);
          push(&opndstk, cosh(x));
          break;
        case 'n':
          x=pop(&opndstk);
          push(&opndstk, tanh(x));
          break;
        case 'o':
          x=pop(&opndstk);
          y=sqrt(x*x+1.0);
          push(&opndstk, log(x+y));
          break;
        case 'p':
          x=pop(&opndstk);
          y=sqrt(x*x-1.0);
          push(&opndstk, log(x+y));
          break;
        case 'q':
          x=pop(&opndstk);
          y=(1.0+x)/(1.0-x);
          push(&opndstk, 0.5*log(y));
          break;
        case 'r':
          y=pop(&opndstk);
          x=pop(&opndstk);
          push(&opndstk, pow(x,y));
          break;
        case 's':
          x=pop(&opndstk);
          push(&opndstk, gamma(x));
          break;
        case 't':case '!':
          x=pop(&opndstk);
          push(&opndstk, factorial(x));
          break;
        case 'u':
          y=pop(&opndstk);
          x=pop(&opndstk);
          push(&opndstk, betha(x,y));
          break;
        case 'v':
          x=pop(&opndstk);
          push(&opndstk, prim(x));
          break;
        case 'w':
          x=pop(&opndstk);
          push(&opndstk, gamma_der(x));
          break;
      }
      i++;
    }
    else
    if(esConstante(s[i]))
    {
      switch(s[i])
      {
        case 'U':
          push(&opndstk, PI);
          break;
        case 'V':
          push(&opndstk, E);
          break;
        case 'W':
          push(&opndstk, R2);
          break;
        default:
          push(&opndstk, var[s[i]-'A']);
      }
      i++;
    }
    else
    if(s[i]==',')
      i++;
  }
  res=pop(&opndstk);
  return(res);
/***/
}


double absoluto(complex z)
{
  double x;
  x=sqrt(z.re*z.re+z.im*z.im);
  return(x);
}

double modulo(complex z)
{
  double angulo;
  angulo=asin(z.im/absoluto(z));
  if(z.re>=0 && z.im>=0)
    return(angulo);
  else
  if(z.re<0 && z.im>=0)
    return(PI-angulo);
  else
  if(z.re<0 && z.im<0)
    return(PI-angulo);
  else
    return(2*PI+angulo);
}

complex realToCom(double x)
{
  complex z;
  z.re=x;
  z.im=0.0;
  return(z);
}

complex conjugado(complex z) 
{ 
  complex x; 
  x.re=z.re; 
  x.im=-z.im; 
  return(x); 
} 

complex neg(complex z) 
{ 
complex x; 
x.re=-z.re; 
x.im=-z.im; 
return(x); 
} 

complex suma(complex a, complex b) 
{ 
complex x; 
x.re=a.re+b.re; 
x.im=a.im+b.im; 
return(x); 
} 

complex resta(complex a, complex b) 
{ 
complex x; 
x.re=a.re-b.re; 
x.im=a.im-b.im; 
return(x); 
} 

complex multiplica(complex a, complex b) 
{ 
complex x; 
x.re=a.re*b.re-a.im*b.im; 
x.im=a.re*b.im+a.im*b.re; 
return(x); 
} 

complex divide(complex a, complex b) 
{ 
complex x; 
x.re=(a.re*b.re+a.im*b.im)/(b.re*b.re+b.im*b.im); 
x.im=(a.im*b.re-a.re*b.im)/(b.re*b.re+b.im*b.im); 
return(x); 
} 
complex SIN(complex z) 
{ 
complex x; 
x.re=sin(z.re)*cosh(z.im); 
x.im=cos(z.re)*sinh(z.im); 
return(x); 
} 

complex COS(complex z) 
{ 
complex x; 
x.re=cos(z.re)*cosh(z.im); 
x.im=(-1.0)*sin(z.re)*sinh(z.im); 
return(x); 
} 

complex TAN(complex z) 
{ 
complex x; 
x=divide(SIN(z), COS(z)); 
return(x); 
} 

complex SINH(complex z) 
{ 
complex x;
complex EXP(complex ); 
x=resta(EXP(z), EXP(neg(z))); 
x.re=(0.5)*x.re; 
x.im=(0.5)*x.im; 
return(x); 
} 

complex COSH(complex z) 
{ 
complex x;
complex EXP(complex); 
x=suma(EXP(z), EXP(neg(z))); 
x.re=(0.5)*x.re; 
x.im=(0.5)*x.im; 
return(x); 
} 

complex TANH(complex z) 
{ 
complex x; 
x=divide(SINH(z), COSH(z)); 
return(x); 
} 

complex EXP(complex z) 
{ 
  complex x; 
  x.re=exp(z.re)*cos(z.im); 
  x.im=exp(z.re)*sin(z.im); 
  return(x); 
} 

complex LOG(complex z) 
{ 
  complex x;
  double p;
  p=absoluto(z); 
  x.re=log(p); 
  x.im=modulo(z); 
  return(x); 
}

complex LOG10(complex z) 
{ 
  complex x;
  x=divide(LOG(x),realToCom(10));
 
  return(x); 
}  

complex POW(complex u, complex w) 
{ 
complex x; 
x=LOG(u); 
x=multiplica(w, x); 
x=EXP(x); 
return(x); 
} 

complex SQRT(complex z) 
{ 
complex x;
x.re=0.5;
x.im=0.0; 
x=multiplica(x,LOG(z));  
x=EXP(x); 
return(x); 
} 

complex ASIN(complex z) 
{ 
complex x; 
x=multiplica(z, z);  
x=resta(unoPos, x); 
x=SQRT(x); 
x=suma(multiplica(iPos, z), x); 
x=LOG(x); 
x=multiplica(iNeg, x); 
return(x); 
} 

complex ACOS(complex z) 
{ 
complex x; 
x=multiplica(z, z); 
x=neg(x); 
x=suma(unoPos, x); 
x=SQRT(x); 
x=multiplica(iPos, x); 
x=suma(z, x); 
x=LOG(x); 
x=multiplica(iNeg, x); 
return(x); 
} 

complex ATAN(complex z) 
{ 
complex x; 
x=multiplica(iNeg,multiplica(realToCom(0.5),LOG(divide(suma(unoPos,multiplica(iPos,z)),resta(unoPos,multiplica(iPos,z))))));
return(x); 
} 

complex ASINH(complex z) 
{ 
complex x; 
x=multiplica(iPos, z); 
x=ASIN(x); 
x=multiplica(iNeg, x); 
return(x); 
} 

complex ACOSH(complex z) 
{ 
complex x; 
x=multiplica(iNeg, ACOS(z)); 
return(x); 
} 

complex ATANH(complex z) 
{ 
complex x; 
x=multiplica(iNeg, ATAN(multiplica(iPos, z) ) ); 
return(x); 
} 
/* convierte cadena en formato a+bi a una estructura del tipo complex*/
complex string_to_complex(char s[])
{
  complex x;
  long i=0, j;
  char numRe[80], numIm[80];
  j=0;
  while(s[i++]!='+')
    numRe[j++]=s[i];
  numRe[j]='\0';
  j=0;
  while(s[i++]!='i')
    numIm[j++]=s[i];
  numIm[j]='\0';
  x.re=atof(numRe);
  x.im=atof(numIm);
  return(x);
  
}



complex FACTORIAL(complex n)
{
  unsigned int i;
  complex t, asintotica, aproximacion, producto, func, funcn;
  producto.re=1.0;
  producto.im=0.0;


  t=suma(realToCom(50.0),n);
  asintotica=multiplica(POW(t,t),multiplica(EXP(neg(t)),SQRT(multiplica(realToCom(2),multiplica(realToCom(PI),t)))));
  aproximacion=EXP(suma(resta(divide(unoPos,multiplica(realToCom(12.0),t)),divide(unoPos,multiplica(realToCom(360.0),POW(t,realToCom(3.0))))),resta(divide(unoPos,multiplica(realToCom(1260),POW(t,realToCom(5.0)))),divide(unoPos,multiplica(realToCom(1680.0),POW(t, realToCom(7.0)))))));
  func=multiplica(asintotica,aproximacion);
  for(i=1; i<=50;i++)
    producto=multiplica(producto,suma(n,realToCom((double)i)));
  funcn=divide(func,producto);
  return(funcn);
}

complex GAMMA(complex x)
{
  complex r;
  r=FACTORIAL(resta(x,unoPos));
  return(r);
}

complex W(complex x)
{
  complex resComp;
    resComp=resta(suma(divide(unoNeg,multiplica(realToCom(12),POW(x,realToCom(2.0)))),divide(unoPos,multiplica(realToCom(120),POW(x,realToCom(4.0))))),suma(divide(unoPos,multiplica(realToCom(252),POW(x,realToCom(6.0)))),divide(unoPos,multiplica(realToCom(240),POW(x,realToCom(8.0))))));
  return(resComp);
}

complex GAMMA_DER(complex x)
{
  long i;
  complex t, sumaCero;
  sumaCero.re=0.0;
  sumaCero.im=0.0;

  t=suma(x,realToCom(MAXTERM));
  for(i=0; i<=MAXTERM;i++)
    sumaCero=suma(sumaCero,divide(unoPos,suma(x,realToCom(i))));
  return(multiplica(GAMMA(x),suma(suma(LOG(t),divide(unoPos,multiplica(realToCom(2),t))),resta(W(t),sumaCero))));
}

complex BETA(complex x, complex y)
{
  complex r;
  r=divide(multiplica(FACTORIAL(resta(x,unoPos)),FACTORIAL(resta(y,unoPos))),FACTORIAL(resta(suma(x,y),unoPos)));
  return(r);
}

//La máxima expresión de la matemática, evaluar una expresión
//algebráica con variables complejas, y debolver el resultado
complex eval_funcComp(char *s, double var[])
{
  complex  x, y, c, resComp;
  char cad_num[30];
  unsigned int i=0, j;
  nodoComplex *opndstkComp;
  double real;
  fflush(stdin);

  opndstkComp=NULL;
  //Mientras la expresion evaluada caracter a caracter
  //no tenga un valor nulo
  while(s[i]!= '\0')
  {
    //si el valor de la expresion es resComp indica que
    //es la respuesta anterior que existe en una variable global
    //llamada igualmente resComp
    //poner este valor en la pila de complejos
    if(strnicmp(&s[i],"resComp",strlen("resComp"))==0)
    {
      pushComplex(&opndstkComp, resComp);
      i+=strlen("resComp");
    }
    else
    //si la expresión es un digito
    //transformarlo a mientras hayan digitos
    //leerlos todos y transformarlos en coma flotante
    //y meterlos a la parte real de la pila de complejos
    if(isdigit(s[i]) )
    {
      j=0;
      do
      {
        cad_num[j]=s[i];
        j++;
        i++;
      }
      while(s[i]!=',');
      cad_num[j]='\0';
      real=atof(cad_num);
      x.re=real;
      x.im=0.0;
      pushComplex(&opndstkComp, x);
    }
    else
    //si la expresíon tiene el representante imaginario i, 
    //meter 1 imaginario en la pila de complejos
    if(s[i]=='i')
    {
      pushComplex(&opndstkComp,iPos);
      i++;
    }
    else
    //tratar como si se esta evaluando una expresión normal
    //sin variable compleja
    if(esOperador(s[i]))
    {
      switch(s[i])
      {
        case '+':
        y=popComplex(&opndstkComp);
        x=popComplex(&opndstkComp);
        pushComplex(&opndstkComp, suma(x,y));
        break;
        case '-':
        y=popComplex(&opndstkComp);
        x=popComplex(&opndstkComp);
        pushComplex(&opndstkComp, resta(x,y));
        break;
        case '*':
        y=popComplex(&opndstkComp);
        x=popComplex(&opndstkComp);
        pushComplex(&opndstkComp, multiplica(x,y));
        break;
        case '/':
        y=popComplex(&opndstkComp);
        x=popComplex(&opndstkComp);
        pushComplex(&opndstkComp, divide(x,y));
        break;
        case '^':
        y=popComplex(&opndstkComp);
        x=popComplex(&opndstkComp);
        pushComplex(&opndstkComp, POW(x,y));
        break;
      }
      i++;
    }
    else
    if(esFuncion(s[i]))
    {
      switch(s[i])
      {
        case 'a':
          x=popComplex(&opndstkComp);
          pushComplex(&opndstkComp, SQRT(x));
          break;
        case 'b':
          x=popComplex(&opndstkComp);
          pushComplex(&opndstkComp, SIN(x));
          break;
        case 'c':
          x=popComplex(&opndstkComp);
          pushComplex(&opndstkComp, COS(x));
          break;
        case 'd':
          x=popComplex(&opndstkComp);
          pushComplex(&opndstkComp, TAN(x));
          break;
        case 'e':
          x=popComplex(&opndstkComp);
          pushComplex(&opndstkComp, ASIN(x));
          break;
        case 'f':
          x=popComplex(&opndstkComp);
          pushComplex(&opndstkComp, ACOS(x));
          break;
        case 'g':
          x=popComplex(&opndstkComp);
          pushComplex(&opndstkComp, ATAN(x));
          break;
        case 'h':
          x=popComplex(&opndstkComp);
          pushComplex(&opndstkComp, EXP(x));
          break;
        case 'z':
          x=popComplex(&opndstkComp);
          pushComplex(&opndstkComp, LOG(x));
          break;
        case 'k':
          x=popComplex(&opndstkComp);
          pushComplex(&opndstkComp, LOG10(x));
          break;
        case 'l':
          x=popComplex(&opndstkComp);
          pushComplex(&opndstkComp, SINH(x));
          break;
        case 'm':
          x=popComplex(&opndstkComp);
          pushComplex(&opndstkComp, COSH(x));
          break;
        case 'n':
          x=popComplex(&opndstkComp);
          pushComplex(&opndstkComp, TANH(x));
          break;
        case 'o':
          x=popComplex(&opndstkComp);
          y=SQRT(suma(multiplica(x,x),unoPos));
          pushComplex(&opndstkComp, LOG(suma(x,y)));
          break;
        case 'p':
          x=popComplex(&opndstkComp);
          y=SQRT(resta(multiplica(x,x),unoPos));
          pushComplex(&opndstkComp, LOG(suma(x,y)));
          break;
        case 'q':
          x=popComplex(&opndstkComp);
          y=divide(suma(unoPos,x),resta(unoPos,x));
          c.re=0.5;
          c.im=0.0;
          pushComplex(&opndstkComp, multiplica(c,LOG(y)));
          break;
        case 'r':
          y=popComplex(&opndstkComp);
          x=popComplex(&opndstkComp);
          pushComplex(&opndstkComp, POW(x,y));
          break;
        case 's':
          x=popComplex(&opndstkComp);
          pushComplex(&opndstkComp, GAMMA(x));
          break;
        case 't':case '!':
          x=popComplex(&opndstkComp);
          pushComplex(&opndstkComp, FACTORIAL(x));
          break;
        case 'u':
          y=popComplex(&opndstkComp);
          x=popComplex(&opndstkComp);
          pushComplex(&opndstkComp, BETA(x,y));
          break;
        case 'w':
          x=popComplex(&opndstkComp);
          pushComplex(&opndstkComp,GAMMA_DER(x));
          break;
      }
      i++;
    }
    else
    if(esConstante(s[i]))
    {
      switch(s[i])
      {
        case 'U':
          c.re=PI;
          c.im=0.0;
          pushComplex(&opndstkComp, c);
          break;
        case 'V':
          c.re=E;
          c.im=0.0;
          pushComplex(&opndstkComp, c);
          break;
        case 'W':
          c.re=R2;
          c.im=0.0;
          pushComplex(&opndstkComp, c);
          break;
        default:
          c.re=var[s[i]-'A'];
          c.im=0.0;
          pushComplex(&opndstkComp, c);
      }
      i++;
    }
    else
    if(s[i]==',')
      i++;
  }
  resComp=popComplex(&opndstkComp);
  return(resComp);
/***/
}

void post_a_entre(char *s, char infix[])
{
  char x[ELEMENTOS], y[ELEMENTOS], res[ELEMENTOS];
  char cad_num[30];
  unsigned int i=0, j;
  String *strstk;
  fflush(stdin);

  strstk=NULL;

  while(s[i]!= '\0')
  {
    if(strnicmp(&s[i],"res",strlen("res"))==0)
    {
      pushString(&strstk, res);
      i+=strlen("res");
    }
    else
    if(isdigit(s[i]) )
    {
      j=0;
      do
      {
        cad_num[j]=s[i];
        j++;
        i++;
      }
      while(s[i]!=',');
      cad_num[j]='\0';
      strcpy(x,cad_num);
      pushString(&strstk, x);
    }
    else
    if(esOperador(s[i]))
    {
      switch(s[i])
      {
        case '+':
        popString(&strstk,y);
        popString(&strstk,x);
        strcpy(res,"(");
        strcat(res,x);
        strcat(res,"+");
        strcat(res,y);
        strcat(res,")");
        pushString(&strstk, res);
        break;
        case '-':
        popString(&strstk,y);
        popString(&strstk,x);
        strcpy(res,"(");
        strcat(res,x);
        strcat(res,"-");
        strcat(res,y);
        strcat(res,")");
        pushString(&strstk, res);
        break;
        case '*':
        popString(&strstk,y);
        popString(&strstk,x);
        strcpy(res,"(");
        strcat(res,x);
        strcat(res,"*");
        strcat(res,y);
        strcat(res,")");
        pushString(&strstk, res);
        break;
        case '/':
        popString(&strstk,y);
        popString(&strstk,x);
        strcpy(res,"(");
        strcat(res,x);
        strcat(res,"/");
        strcat(res,y);
        strcat(res,")");
        pushString(&strstk, res);
        break;
        case '^':
        popString(&strstk,y);
        popString(&strstk,x);
        strcpy(res,"(");
        strcat(res,x);
        strcat(res,"^");
        strcat(res,y);
        strcat(res,")");
        pushString(&strstk, res);
        break;
      }
      i++;
    }
    else
    if(esFuncion(s[i]))
    {
      switch(s[i])
      {
        case 'a':
          popString(&strstk,x);
          strcpy(res,"sqrt(");
          strcat(res,x);
          strcat(res,")");
          pushString(&strstk, res);
          break;
        case 'b':
          popString(&strstk,x);
          strcpy(res,"sin(");
          strcat(res,x);
          strcat(res,")");
          pushString(&strstk, res);
          break;
        case 'c':
          popString(&strstk,x);
          strcpy(res,"cos(");
          strcat(res,x);
          strcat(res,")");
          pushString(&strstk, res);
          break;
        case 'd':
          popString(&strstk,x);
          strcpy(res,"tan(");
          strcat(res,x);
          strcat(res,")");
          pushString(&strstk, res);
          break;
        case 'e':
          popString(&strstk,x);
          strcpy(res,"asin(");
          strcat(res,x);
          strcat(res,")");
          pushString(&strstk, res);
          break;
        case 'f':
          popString(&strstk,x);
          strcpy(res,"acos(");
          strcat(res,x);
          strcat(res,")");
          pushString(&strstk, res);
          break;
        case 'g':
          popString(&strstk,x);
          strcpy(res,"atan(");
          strcat(res,x);
          strcat(res,")");
          pushString(&strstk, res);
          break;
        case 'h':
          popString(&strstk,x);
          strcpy(res,"exp(");
          strcat(res,x);
          strcat(res,")");
          pushString(&strstk, res);
          break;
        case 'z':
          popString(&strstk,x);
          strcpy(res,"ln(");
          strcat(res,x);
          strcat(res,")");
          pushString(&strstk, res);
          break;
        case 'k':
          popString(&strstk,x);
          strcpy(res,"log10(");
          strcat(res,x);
          strcat(res,")");
          pushString(&strstk, res);
          break;
        case 'l':
          popString(&strstk,x);
          strcpy(res,"sh(");
          strcat(res,x);
          strcat(res,")");
          pushString(&strstk, res);
          break;
        case 'm':
          popString(&strstk,x);
          strcpy(res,"ch(");
          strcat(res,x);
          strcat(res,")");
          pushString(&strstk, res);
          break;
        case 'n':
          popString(&strstk,x);
          strcpy(res,"th(");
          strcat(res,x);
          strcat(res,")");
          pushString(&strstk, res);
          break;
        case 'o':
          popString(&strstk,x);
          strcpy(res,"ash(");
          strcat(res,x);
          strcat(res,")");
          pushString(&strstk, res);
          break;
        case 'p':
          popString(&strstk,x);
          strcpy(res,"ach(");
          strcat(res,x);
          strcat(res,")");
          pushString(&strstk, res);
          break;
        case 'q':
          popString(&strstk,x);
          strcpy(res,"ath(");
          strcat(res,x);
          strcat(res,")");
          pushString(&strstk, res);
          break;
        case 'r':
          popString(&strstk,y);
          popString(&strstk,x);
          strcpy(res,"pow(");
          strcat(res,x);
          strcat(res,",");
          strcat(res,y);
          strcat(res,")");
          pushString(&strstk, res);
          break;
        case 's':
          popString(&strstk,x);
          strcpy(res,"gamma(");
          strcat(res,x);
          strcat(res,")");
          pushString(&strstk, res);
          break;
        case 't':case '!':
          popString(&strstk,x);
          strcpy(res,x);
          strcat(res,"!");
          pushString(&strstk, res);
          break;
        case 'u':
          popString(&strstk,y);
          popString(&strstk,x);
          strcpy(res,"beta(");
          strcat(res,x);
          strcat(res,",");
          strcat(res,y);
          strcat(res,")");
          pushString(&strstk, res);
          break;
        case 'v':
          popString(&strstk,x);
          strcpy(res,"prim(");
          strcat(res,x);
          strcat(res,")");
          pushString(&strstk, res);
          break;
        case 'w':
          popString(&strstk,x);
          strcpy(res,"gamma'(");
          strcat(res,x);
          strcat(res,")");
          pushString(&strstk, res);
          break;
      }
      i++;
    }
    else
    if(esConstante(s[i]))
    {
      switch(s[i])
      {
        case 'U':
          pushString(&strstk, "pi");
          break;
        case 'V':
          pushString(&strstk, "e");
          break;
        case 'W':
          pushString(&strstk, "r2");
          break;
        default:
          res[0]=s[i];
          res[1]='\0';
          pushString(&strstk, res);
      }
      i++;
    }
    else
    if(s[i]==',')
      i++;
  }
  popString(&strstk,res);
  strcpy(infix,res);
  return;
/***/
}

unsigned int evaluar_prioridad(char c) 
{ 
unsigned int prioridad; 
if(esFuncion(c))
  prioridad=FUNCION;
else
switch(c) 
{ 
case '(': 
   prioridad=PAREN_IZ; 
   break; 
case ')': 
   prioridad=PAREN_DER; 
   break; 
case '+' :  case '-': 
   prioridad=2;
   break; 
case '*':  case '/': 
   prioridad=3;
   break; 
case '^': 
   prioridad=5;
   break; 
default: 
   prioridad=VARIABLE; 
}
return(prioridad);
} 

void traducir_a_postfijo(char *infijo, char *postfijo) 
{ 
int i=0, k=-1, n=-1; 
unsigned int prioridad; 
char pila[ELEMENTOS]; 

while(infijo[i] != '\0') 
{
   if(strnicmp(&infijo[i],"resComp",strlen("resComp"))==0)
   {
     ++k;
     strncpy(&postfijo[k],"resComp",strlen("resComp"));
     k+=strlen("resComp")-1;
     i+=strlen("resComp")-1;
   }
   else
   if(strnicmp(&infijo[i],"res",strlen("res"))==0)
   {
     ++k;
     strncpy(&postfijo[k],"res",strlen("res"));
     k+=strlen("res")-1;
     i+=strlen("res")-1;
   }
   else
   {
   prioridad=evaluar_prioridad(infijo[i]); 
   switch(prioridad) 
   { 
   case VARIABLE: 
       k++; 
       postfijo[k]=infijo[i];
       if(isdigit(infijo[i]) && (esOperador(infijo[i+1])||( infijo[i+1]==')' ) ||( infijo[i+1]=='\0' ) ||( infijo[i+1]==',' ) || ( infijo[i+1]=='!' ) ))
       {
         k++;
         postfijo[k]=',';
         if(infijo[i+1]==',')
           i++;
       }
     break; 

   case PAREN_IZ: 
     pila[++n]=infijo[i]; 
     break;

   case FUNCION: 
     pila[++n]=infijo[i]; 
     break; 

   case PAREN_DER: 
     while(pila[n] != '(') 
       postfijo[++k]=pila[n--];
     n--; 
     break; 
   default: 
     while( n != -1) 
     { 
       if(evaluar_prioridad(infijo[i]) <= evaluar_prioridad(pila[n]) ) 
         postfijo[++k]=pila[n--];
       else 
         break; 
     }  
     pila[++n]=infijo[i]; 
   }
} 
   i++; 
} 

while( n != -1) 
{
   k++; 
   postfijo[k]=pila[n];
   n--; 
} 

k++; 
postfijo[k]='\0'; 
return; 
} 


double eval_sigma(char *s)
{
  long a, b, n;
  double suma=0.0;
  long i=0, j;

  while(s[i]!='[')
    i++;
  i++;
  j=0;
  while(s[i]!=',')
    expr[j++]=s[i++];
  expr[j]='\0';
  i++;

  j=0;
  while(s[i]!=',')
    num[j++]=s[i++];
  num[j]='\0';
  a=atol(num);
  i++;

  j=0;
  while(s[i]!=']')
    num[j++]=s[i++];
  num[j]='\0';
  b=atol(num);
  i++;

  reset_var(chk);
  chk['N'-'A']=si;

  pretraducir(expr, nuevaC);  
  traducir_a_postfijo(nuevaC, expr);
  check_var(expr, var, chk);
  for(n=a; n<=b; n++)
  {
    var['N'-'A']=(double)n;
    suma+=eval_func(expr, var);
  }
  return(suma);  
}

double eval_pi(char *s)
{
  long a, b, n;
  double producto=1.0;
  long i=0, j;

  while(s[i]!='[')
    i++;
  i++;
  j=0;
  while(s[i]!=',')
    expr[j++]=s[i++];
  expr[j]='\0';
  i++;

  j=0;
  while(s[i]!=',')
    num[j++]=s[i++];
  num[j]='\0';
  a=atol(num);
  i++;

  j=0;
  while(s[i]!=']')
    num[j++]=s[i++];
  num[j]='\0';
  b=atol(num);
  i++;

  reset_var(chk);
  chk['N'-'A']=si;

  pretraducir(expr, nuevaC);  
  traducir_a_postfijo(nuevaC, expr);
  check_var(expr, var, chk);
  for(n=a; n<=b; n++)
  {
    var['N'-'A']=(double)n;
    producto*=eval_func(expr, var);
  }
  reset_var(chk);
  return(producto);  
}

double eval_diff(char *s)
{
  long i=0, j=0;
  double delta, diff, x, a, b;
    
	
  //esta funcion contiene errores
  system("cls");
  printf("esta fucion contiene errores\npresione tecla enter o intro, para salir");
  getchar();
  exit(0);

  system("cls");
  printf("en eval diff");
  getchar();
  while(s[i]!='[')
    i++;
  while( s[i]!=')' && s[i+1]!='/'&& s[i+2]!='d' && s[i+3]!='x')
    expr[j++]=s[i++];
  expr[j]='\0';
  i++;
  j=0;
  while(s[i]!=',')
    num[j++]=s[i++];
  num[j]='\0';
  i++;
  x=atof(num);
  while(s[i]!='=')
    i++;
  i++;
  j=0;
  while(s[i]!=',')
    num[j++]=s[i++];
  num[j]='\0';
  delta=atof(num);
  
  reset_var(chk);
  chk['X'-'A']=si;
  pretraducir(expr, nuevaC);  
  traducir_a_postfijo(nuevaC, expr);
  check_var(expr, var, chk);

  var['X'-'A']=x+delta;
  a=eval_func(expr, var);

  var['X'-'A']=x;
  b=eval_func(expr, var);

  diff=(a-b)/delta;
  return(diff); 
}

double eval_integral(char *s)
{
  long i=0, j=0, n;
  double a, b, h, x=0.0, Area, bas=0.0;
  while(s[i]!='[')
    i++;
  i++;
  j=0;
  while(s[i]!=',')
    expr[j++]=s[i++];
  expr[j]='\0';
  i++;
  j=0;
  while(s[i]!=',')
    expr1[j++]=s[i++];
  expr1[j]='\0';
  i++;
  j=0;
  while(s[i]!=',')
    expr2[j++]=s[i++];
  expr2[j]='\0';
  i++;
  j=0;
  while(s[i]!='d' && s[i+1]!='x')
    num[j++]=s[i++];
  num[j]='\0';
  i++;
  n=atol(num);

  reset_var(chk);
  pretraducir(expr1, nuevaC);  
  traducir_a_postfijo(nuevaC, expr1);
  check_var(expr1, var, chk);
  a=eval_func(expr1, var);
  reset_var(chk);
  pretraducir(expr2, nuevaC);  
  traducir_a_postfijo(nuevaC, expr2);
  check_var(expr2, var, chk);
  b=eval_func(expr2, var);
  
  h=(b-a)/((double)n);

  x=a;
  reset_var(chk);
  chk['X'-'A']=si;
  pretraducir(expr, nuevaC);  
  traducir_a_postfijo(nuevaC, expr);
  check_var(expr, var, chk);
  var['X'-'A']=x;
  Area=eval_func(expr, var)*h/3.0;


  for(i=2; i<n; i++)
  {
    x+=h;
    var['X'-'A']=x;
    if((i%2)==0)
      Area+=2.0*eval_func(expr, var)*h/3.0;
    else 
      Area+=4.0*eval_func(expr, var)*h/3.0;
  }
  x=b;
  var['X'-'A']=x;
  Area+=eval_func(expr, var)*h/3.0;
  return(Area);
}


double eval_continua(char *s)
{
  double manterior, mactual, mnuevo, nanterior, nactual, nnuevo;
  long a, b, n;
  long i=0, j;

  while(s[i]!='[')
    i++;
  i++;
  j=0;
  while(s[i]!=',')
    expr[j++]=s[i++];
  expr[j]='\0';
  i++;

  j=0;
  while(s[i]!=',')
    num[j++]=s[i++];
  num[j]='\0';
  a=atol(num);
  i++;

  j=0;
  while(s[i]!=']')
    num[j++]=s[i++];
  num[j]='\0';
  b=atol(num);
  i++;

  reset_var(chk);
  chk['N'-'A']=si;
  pretraducir(expr, nuevaC);  
  traducir_a_postfijo(nuevaC, expr);
  check_var(expr, var, chk);

  var['N'-'A']=(double)a;
  mactual=eval_func(expr, var);
  nactual=1;
  manterior=1;
  nanterior=0;

  for(n=a+1; n<=b; n++)
  {
    var['N'-'A']=(double)n;
    mnuevo=mactual*eval_func(expr, var)+manterior;
    manterior=mactual;
    mactual=mnuevo;
    nnuevo=nactual*eval_func(expr, var)+nanterior;
    nanterior=nactual;
    nactual=nnuevo;
  }
  
  return(mactual/nactual);  
}

double eval_integrando(char *s)
{
  long i=0, j=0;
  double a, b, x=0.0, valor, low, upp;
  while(s[i]!='[')
    i++;
  i++;
  j=0;
  while(s[i]!=',')
    expr[j++]=s[i++];
  expr[j]='\0';
  i++;
  j=0;
  while(s[i]!=',')
    expr1[j++]=s[i++];
  expr1[j]='\0';
  i++;
  j=0;
  while(s[i]!=']')
    expr2[j++]=s[i++];
  expr2[j]='\0';
  i++;

  reset_var(chk);
  pretraducir(expr1, nuevaC);  
  traducir_a_postfijo(nuevaC, expr1);
  check_var(expr1, var, chk);
  a=eval_func(expr1, var);
  printf("\nLimite inferior= %lf", a);

  reset_var(chk);
  pretraducir(expr2, nuevaC);  
  traducir_a_postfijo(nuevaC, expr2);
  check_var(expr2, var, chk);
  b=eval_func(expr2, var);
  printf("\nLimite superior= %lf", b);

  x=a;
  reset_var(chk);
  chk['X'-'A']=si;
  pretraducir(expr, nuevaC);  
  traducir_a_postfijo(nuevaC, expr);
  check_var(expr, var, chk);
  var['X'-'A']=x;
  low=eval_func(expr, var);

  x=b;
  reset_var(chk);
  chk['X'-'A']=si;
  check_var(expr, var, chk);
  var['X'-'A']=x;
  upp=eval_func(expr, var);

  valor=(upp-low);
  return(valor);
}


double eval_expr(char *exprP)
{
  double val;
  complex comp;
  limpiar_cadena(exprP, expr);
  strcpy(exprP,expr);
  if(present_string(exprP, "sigma["))
  { 
    val=eval_sigma(exprP);
    return(val);
  }
  else
  if(present_string(exprP, "pi["))
  {
    val=eval_pi(exprP);
    return(val);
  }
  else
  if(present_string(exprP, "integral["))
  {
    val=eval_integral(exprP);
    return(val);
  }
  else
  if(present_string(exprP, "diferencial["))
  {
    val=eval_diff(exprP);
    return(val);
  }
  else
  if(present_string(exprP, "continua["))
  {
    val=eval_continua(exprP);
    return(val);
  }
  else
  if(present_string(exprP, "integrando["))
  {
    val=eval_integrando(exprP);
    return(val);
  }
  else
  {
    if(present_string(exprP, "com["))
    {
      reset_var(chk);
      pretraducir(exprP+4, nuevaC);
      traducir_a_postfijo(nuevaC, exprP);
      check_var(exprP, var, chk);
      comp=eval_funcComp(exprP,var);
    }
    else
    {
      reset_var(chk);
      pretraducir(exprP, nuevaC);
      traducir_a_postfijo(nuevaC, exprP);
      check_var(exprP, var, chk);
      val=eval_func(exprP, var);
    }
   }
  reset_var(chk);
  return(val);
}

void probarV(void)
{
	double val;
  char cadenaO[ELEMENTOS];
  clock_t startclock, endclock;

    do{
    printf("\n\"fin=\" para terminar\n");
    printf("\nintroducir cadena ");
    scanf("%[^=]", cadenaO);
    fflush(stdin);
    if(strnicmp(cadenaO, "fin", 3) == 0)
      break;
    startclock=clock();
    val=eval_expr(cadenaO);
    reset_var(chk);
    endclock=clock();
    res=val;
    printf("\nValor: %.14f", val);
    printf("\nel tiempo estimado de calculo fue de %.4lf segundos",(float)(endclock-startclock)/1000.0);
    fflush(stdin);
    }
    while(1);
    getchar();
    return;
}

void probarS(void)
{
    char cadenaO[ELEMENTOS], nuevaC[ELEMENTOS];
    do{
    printf("\n\"fin=\" para terminar\n");
    printf("\nintroducir cadena ");
    scanf("%[^=]", cadenaO);
    limpiar_cadena(cadenaO,nuevaC);
    strcpy(cadenaO,nuevaC);
    fflush(stdin);
    if(strnicmp(cadenaO, "fin", 3) == 0)
      break;
    system("cls");
    printf("\ncadena original=%s", cadenaO); 
    pretraducir(cadenaO, nuevaC);
    printf("\ncadena nueva=%s", nuevaC);  
    traducir_a_postfijo(nuevaC, cadenaO);
    printf("\ncadena en postfijo=%s", cadenaO);
    post_a_entre(cadenaO,nuevaC);
    printf("\nNueva cadena en entrefijo o original=%s", nuevaC);
    /**val=eval_expr(cadenaO);
    printf("\nel valor es= %lf", val);  */
    fflush(stdin);
    }
    while(1);
    getchar();
    return;
}

void retardo(long n)
{
  long i;
  for(i=0;i<=n;i++);
  for(i=0;i<=n;i++);
  for(i=0;i<=n;i++);
  return;
}

void scroll(void)
{
  char *cad="   este programa te permitira evaluar cualquier funcion            ";
  char *temp, *newcad;
  temp=(char*)malloc(sizeof(strlen(cad)));
  newcad=(char*)malloc(sizeof(strlen(cad)));
  strcpy(newcad, cad);
  while(1)
  {
    printf("%s", newcad);
    strcpy(temp, &newcad[1]); 
    strncat(temp, &newcad[0],1);
    strcpy(newcad, temp);
    retardo(500000);
    system("cls");
  }
}
/*  Presentacion();
  printf("\n\npresione tecla enter para comenzar");
  getchar();
  system("cls");*/
int main(void)
{
  Presentacion();
  probarV();
  
  return(0);     
}






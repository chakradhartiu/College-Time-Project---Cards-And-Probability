#include<iostream.h>
#include<dos.h>       //delay(),sleep(),sound(),nosound()
#include<conio.h>     //textcolor(),textbackcolor(),getch(),putch()
#include<ctype.h>     //isdigit(),isalnum()
#include<string.h>    //strcpy()
#include<stdio.h>     //gets(),puts()

char ans[6],a[14]="!&|123456789\0";;
char ch[5][9][18]=
{{"1. Heart  \x03","2. Diamond \x04","3. Club   \x05","4. Spade  \x06"," "," "," "," "," "},
 {"1. Red","2. Black"," "," "," "," "," "," "," "},
 {"1. Ace","2. King","3. Queen","4. Jack"," "," "," "," "," "},
 {"1. 2","2. 3","3. 4","4. 5","5. 6","6. 7","7. 8","8. 9","9. 10"},
 {"1. Face Cards","2. Alphabets","3. Digits","4. Non-Face Cards"," "," "," "," "," "}
};
int z[3][4][13],k,loc,cnnt=0,x,ap;

void loading();

void setc(int tc=15,int bc=0)
   { textcolor(tc); textbackground(bc); }

void cvt(char ch)
   { ap=int(ch)-48; }

void welcome()
   { setc(3);
     gotoxy(38,12); cout<<"WELCOME";   setc(RED+BLINK);
     textcolor(RED+BLINK);
     gotoxy(34,12); cout<<"CARDS AND PROBABILITY:-\n";
     cputs("\n\n\n\n\nPresented By:-");
     cputs("\n\n1. Chakradhar Tiu(Captain)");
     cputs("\n\n2. Sheetal Kudada");
     cputs("\n\n3. Shubham Raut");
     cout<<"\n\n\n\n\t\t\tPress any key to continue.......";
     getch();     setc();
   }

int prec(char ch)
   { switch(ch)
       { case '!':return 6;
	 case '&':return 4;
	 case '|':return 2;
	 default:return -1;
       }
   }

void draw1(int type)
   { switch(type)
	{ case 3:cout<<"HEART   \x03"; break;
	  case 4:cout<<"DIAMOND \x04"; break;
	  case 5:cout<<"CLUB    \x05"; break;
	  case 6:cout<<"SPADE   \x06"; break;
	}
   }

void loc1()
   { loc=0;
     for(int i=0;ans[i]!='\0';++i)
       { if(prec(ans[i])>=prec(ans[loc]))
	   loc=i;
       }
   }

void xp(int loc1)
   { int i=0;
     x=0;
     while(i<loc1)
	{ if(isalnum(ans[i]))
	     ++x;
	  ++i;
	}
   }

void short1(int srt)
   {  for(int i=0;i<4;++i)
	{ for(int j=0;j<13;++j)
	    {
	      if(srt==1)      {    z[x-1][i][j]*=z[x][i][j];        }
	      else if(srt==2) { if(z[x][i][j]==1)  z[x-1][i][j]=1;  }
	      else            { z[x][i][j]=1-z[x][i][j];            }
	    }
	}
   }

void not()
   { short1(0); }

void and()
   { short1(1); }

void or()
   { short1(2); }

void calculate()
   { int i,j;
     for(i=0;i<13;++i)
       { switch(k)
	   { case 0:z[x][ap-1][i]=1;     break;
	     case 1:z[x][ap][i]=1;
		    if(ap==1) z[x][ap-1][i]=1;
		    if(ap==2) z[x][ap+1][i]=1;
		    break;
	   }
	}
      for(i=0;i<4;++i)
	 { switch(k)
	     { case 2:if(ap==1)  z[x][i][0]=1;
		      else   z[x][i][14-ap]=1;
		      break;
	       case 3:z[x][i][ap]=1;    break;
	     }
	 }
      if(k==4)
	 {  for(i=0;i<4;++i)
	      {  for(j=0;j<13;++j)
		   {  if(((ap==1)||(ap==2))&&(j>9))
			z[x][i][j]=1;
		      if(((ap==3)||(ap==4))&&(j>0)&&(j<10))
			z[x][i][j]=1;
		   }
		 if((ap==2)||(ap==4))     z[x][i][0]=1;
	      }
	 }
   }

int valid()
   { int s,i,j,x1;
     if((k==0)||(k==2)||(k==4))  x1=7;
     else if(k==1)  x1=5;
     else if(k==3)  x1=strlen(a);
     for(i=0;ans[i]!='\0';++i)
	{ s=0;
	  for(j=0;j<x1;++j)
	     { if(ans[i]==a[j])  s=1;  }
	  if(s==0)
	  return 0;
	  if(ans[i]==ans[i+1])
	  return 0;
	  if(isdigit(ans[i])&&((ans[i+1]=='!')||(ans[i+2]=='&')||(ans[i+2]=='|')))
	  return 0;
	  if(ans[i]==('&'||'|'||'!')&&ans[i+1]==('&'||'|'))
	  return 0;
	}
     if(ans[0]==('|'||'&')||ans[strlen(ans)-1]==('|'||'&'||'!'))
     return 0;
     return 1;
   }

void prt(int x,int y,char a[],char b[])
   {  gotoxy(1,y);   delline();
      for(int i=(1-x);i<strlen(a);++i)
	 {  if(i<0)  cout<<" ";
	    else     cout<<a[i];
	 }
      clreol();
      if(x<1)
      {  gotoxy(x+80,y);  puts(b);   }
      clreol();
   }

void defaultf()
   { int i,j;
     for(i=0;i<13;++i)
       for(j=0;j<4;++j)
       {  z[0][j][i]=0;   z[1][j][i]=0;    z[2][j][i]=0;   }
   }

int defaultshow()
   { for(int i=0;i<4;++i)
       for(int j=0;j<13;++j)
	  if(z[0][i][j]==1)     return 0;
     return 1;
   }

class cards
   { char a[14];
     int type;
     int y;
     int tc;
     int bc;
     int select[13];
    public:
     void defaultf()
	{ strcpy(a,"A23456789tJQK");
	  for(int i=0;i<13;++i)   select[i]=0;
	}

     cards()  {   defaultf();   }
     ~cards()  {   }

     void set(int t,int y1)
	{ defaultf(); type=t;  y=y1;
	  if((type==3)||(type==4))
	     { tc=4;bc=14;}
	  else
	     { tc=0 ;bc=15; }
	}

     float selectno()
       { float n=0;
	 for(int i=0;i<13;++i)
	   {  n+=select[i];    }
	 defaultf();
	 return n;
       }

     void draw(int n=0)
	{ int i,j,k1;
	  setc(tc,bc);
	  gotoxy(38,y-2); draw1(type);
	  for(i=2;i<79;++i)
	    { if((i-1)%6==0)  ++i;
	      gotoxy(i,y);    putch(220);
	      gotoxy(i,y+4);  putch(223);
	      if(i%6==0)
		{ if((select[(i/6)-1]==1)||(defaultshow()&&(n!=5)))
		    { for(j=y;j<=y+4;++j)
			{ gotoxy(i,j);    putch(222);
			  gotoxy(i-4,j);  putch(221);
			}
		      gotoxy(i-2,y+2); setc(tc,bc);
		      if(a[(i/6)-1]=='t') cout<<"10";
		      else cout<<a[(i/6)-1];
		      gotoxy(i-3,y+1); putch(type);
		      gotoxy(i-1,y+3); putch(type);
		      delay(200);
		    }
		  else
		    { setc(2);
		      for(j=y;j<=y+4;++j)
		       for(k1=(i-4);k1<=i;++k1)
			  {   gotoxy(k1,j); putch(219);  }
		      setc(tc,bc);
		      delay(200);
		    }
		}
		 //close i%6 ()
	      }  //close i loop
	  delay(500);
	  }   //close draw ()
	  void  or(int z[13])
	     { for(int i=0;i<13;++i)   if(z[i]==1)  select[i]=1;   }
	  void and(int z[13])
	     { for(int i=0;i<13;++i)   select[i]*=z[i];  }
    } cds[4];    //close  class cards

void short2(int z)
   { cvt(ans[z]);   xp(z);    calculate();
     if(ans[z-1]=='!')   ans[z-1]='z';
     else ans[z]='z';
   }

void connect()
   { for(int i=0;i<4;++i)
       if(!cnnt)  cds[i].or(z[0][i]);
       else   cds[i].and(z[0][i]);
   }

void calc()
   { int i,j;
     while(ans[0]!='\0')
       { if(isdigit(ans[0])&&ans[1]=='\0')
	   { short2(0);connect();ans[0]='\0';break; }
	 if((ans[0]=='z')&&(ans[1]=='\0'))
	    {  connect();  ans[0]='\0';  break;  }
	 loc1();
	 if((ans[loc]=='&')||(ans[loc]=='|'))
	    {  if(isdigit(ans[loc+1]))
		 short2(loc+1);
	       if(isdigit(ans[loc-1]))
		 short2(loc-1);
	       xp(loc);
	       if(ans[loc]=='&')   and();
	       if(ans[loc]=='|')   or();
	       ans[loc-1]='z';
	       for(i=1;i<=2;++i)
		  { j=loc;
		    while(ans[j]!='\0')
		       {  ans[j]=ans[j+1];   ++j;     }
		  }
	    }
	 else  if(ans[loc]=='!')
	   {
	       short2(loc+1);  ans[loc]='z'; xp(loc);  not();   i=loc+1;
		 while(ans[i]!='\0')
		    { ans[i]=ans[i+1];   ++i;   }
	       if((ans[0]=='z')&&(ans[1]=='\0'))
		  {  connect();  ans[0]='\0';  break;  }
	   }
	 }//close  loop
   }

void draw(int n=0)
   { getch();       clrscr();
     float s=0;
     for(int i=0;i<4;++i)
	{ cds[i].draw(n);  s+=cds[i].selectno();   }
     setc(9);
     gotoxy(2,38);
     if(n==5)
       {  cout<<"PROBABILITY="<<s<<"/52="<<(s/52)<<"\n";   }
     setc();  defaultf();   getch();  clrscr();
   }

void choice()
   { char ch;     clrscr();
     cout<<"\n\nConnect by:-\n1.AND\n2.OR";
     L: cout<<"\nEnter your choice=>";
     cin>>ch;
     if(ch=='1')        cnnt=1;
     else if(ch=='2')   cnnt=0;
     else  {  cout<<"\nwrong choice!!!";   goto L;  }
     defaultf();
   }

void Mnprog()
   { int i,j,x2,x5,dir=0;    k=0;  char c;   cnnt=0;
	  if(defaultshow())     draw();
	  label: 
          clrscr();
	  _setcursortype(0);
	  cout<<"\n\t\t\t   Page : "<<k+1;
	  if(dir==0)
	     {
		cout<<"\n\n\t\t\tProbability Menu:-\n\n";
		i=0;
		while(i<9)
		   {  puts(ch[k][i]);
		      cout<<"\n";   ++i ;
		   }
	     }
	  else
	  for(i=x5;i!=(x5-(dir*83));i-=dir)
	     {
		prt(i,3,"\t\t\tProbability Menu:-\n","\t\t\tProbability Menu:-\n");
		clreol();
		for(j=0;j<9;++j)
		  { gotoxy(1,4);    clreol();
		    if(dir==(-1))   prt(i,(j+5),ch[k][j],ch[k-dir][j]);
		    if(dir==1)      prt(i,(j+5),ch[k-dir][j],ch[k][j]);
		  }
		delay(7);
	     }
	  _setcursortype(2);
	  cout<<"\n\n\n";
	  cout<<"\'+\' for next,"
	      <<"\'-\' for back,"
	      <<"\'s\' to start selection OR,"
	      <<"Press Esc to stop selection. \n";
	  c=getch();
	  if(c=='+')
	    {  if(k<4)  {  ++k; dir=1;     x5=1;    }
	       else dir=0;
	       goto label;
	    }
	  else if(c=='-')
	    {  if(k>0)  {  --k; dir=(-1);  x5=(-81); }
	       else dir=0;
	       goto label;
	    }
	  else if(c==27) {    goto end; }
	  else if((c=='s')||(c=='S'))
	    { j=0;
	      if((k==0)||(k==2)||(k==4))  x2=7;
	      else if(k==1)  x2=5;
	      else if(k==3)  x2=strlen(a);
	      cout<<"\n\n\n\n\nAvailable  characters:-\n(";
	      while(j<x2)
		 {   cout<<" ";
		     if((j==3)&&(k==3))    cout<<"\n";
		     cout<<a[j];
		     switch(j)
			{  case 0:cout<<"(NOT-Precedence^^^)";   break;
			   case 1:cout<<"(AND-Precedence^^)";    break;
			   case 2:cout<<"(OR-Precedence^)";      break;
			}
		     cout<<" ";   ++j;
		 }
	      cout<<")";
	      cout<<"\n\n\n\nYou may use these expressions:-";
	      cout<<"\n1. !(AUB)=!A ";putch(239);cout<<" !B";
	      cout<<"\n2. !(A";putch(239);cout<<"B)=!A U !B";
	      cout<<"\n\n\nEnter the expression(max. size 4)....\n";
	      gets(ans);
	    }
	  else
	    { cout<<"\nWrong choice  !!!";  dir=0;  getch(); goto label;  }
     if((!valid())&&(c!=27))
	{ cout<<"\nInvalid statement!!!\n"; dir=0;  getch();  goto label; }
     else
	{ calc();
	  cout<<"\n\nDo you want to add more expression....."
	      <<"\n(y/Y) to continue...";
	  c=getch();
	  if((c=='y')||(c=='Y'))
	   { choice();  dir=0; goto label;   }
	}    end:
	draw(5);  clrscr();  getch();
	cout<<"\nDo you want to visit again(y/Y).....";
	c=getch();
	if((c=='y')||(c=='Y'))   Mnprog();
   }
      // close mnprog()

void main()
   {  clrscr();      welcome();      loading();
      cds[0].set(3,4);          cds[2].set(5,22);
      cds[1].set(4,13);         cds[3].set(6,31);

      Mnprog();     clrscr();
      gotoxy(2,2);
      cout<<"Thanks for visiting.\n Visit again!!!";
      gotoxy(36,23);
      cout<<"Breaking......";
      sleep(4);
      clrscr();
   }
void loading()
  {
    clrscr();
    int x=31,y=15;
    gotoxy(35,3);
    setc(4);
    cout<<"LOADING..........";
    while(x<51)
    {  textcolor(YELLOW);
       gotoxy(x,y);     putch(219);
       gotoxy(x,y+3);   putch(219);
       ++x;
    }
    for(int i=0;i<=3;++i)
    {
    gotoxy(30,y+i);    putch(219);
    gotoxy(51,y+i);    putch(219);
    }
    x=31;y=16;
    setc(2);
    float t=0;
    while(x<51)
    {  for(i=0;i<=1;++i)
       {   gotoxy(x,y+i);     putch(219);   }
       t+=5;
       sound(1000);delay(150);nosound();delay(150);
       ++x;
       gotoxy(26,28);delline();cout<<int(t)<<"% completed..";
    }
    gotoxy(15,32);
    cout<<"Press any key to continue.......";
    getch();
  }
#include <stdio.h>
#include <ctype.h> 
#include <string.h>
#define MAIN	1
#define INT		2
#define CHAR	3
#define IF		4
#define ELSE	5
#define WHILE	6
#define	ID		10//letter(letter|digit)*
#define NUM		20//digitdigit*
#define EQUAL	21// =
#define PlUS	22// +
#define MINUS	23// -
#define STAR	24// *
#define	DIVOP	25// /
#define LP		26// (
#define RP		27// )
#define LC		28// {
#define RC		29// }
#define COMMA	30// ,
#define SEMI	31// ;
#define GT		32// >
#define LT		33// <
#define GE		34// >=
#define LE		35// <=
#define DD		36// ==
#define BUD		37// !=

char  key[6][5]={"main","int", "char","if","else","while"};
char token[10];

int lookup()
{
	int i ;
	int flag;
	for(i= 0;i<6;i++)
	{
		if(strcmp(token,key[i]) == 0)
		{
			printf("(%d,%s) 保留字\n",i+1, key[i]);
			flag = 1;
			break;
		}
		else
		{
			flag = 0;
		}
	}
	return flag;
}

void out(int i, char n[])
{
	printf("(%d,%s)\n",i,n);
} 

int report_error()
{
	printf("错误\n");
	return 0; 
}


void scanner_example(FILE*fp)
{
	char ch;
	int i = 0,c;
	ch = fgetc(fp);
	if(isalpha(ch))//判断字母 
	{
		token[0] = ch;
		ch = fgetc(fp);
		i = 1;
		while(isalnum(ch))//判断数字或者字母 
		{
			token[i] = ch;
			i++;
			ch = fgetc(fp);
		}
		token[i]='\0';
		fseek(fp, -1, 1);
		c = lookup(token);
		if(c==0) out(ID,token);
		//else out(c, " ");
	}
	else if(isdigit(ch))//判断数字 
	{
		token[0] = ch;
		ch = fgetc(fp);
		i = 1;
		while(isdigit(ch))
		{
			token[i] = ch;
			i++;
			ch = fgetc(fp);
		}
		token[i]='\0';
		fseek(fp, -1, 1);
		out(NUM, token);
	}
	else
	switch(ch)
	{
		case'<':ch = fgetc(fp);
					if(ch == '=')out(LE, "<=");
					else 
					{
						fseek(fp, -1, 1);
						out(LT, "<");
					}
				break;
					
		case'=':ch = fgetc(fp);
					if(ch == '=')out(DD, "==");
					else 
					{
						fseek(fp, -1, 1);
						out(EQUAL, "=");
					}
				break;
					
		case'>':ch = fgetc(fp);
					if(ch == '=')out(GE, ">="); 
					else 
					{
						fseek(fp, -1, 1);
						out(GT, ">");
					}
				break;
				
		case'!':ch = fgetc(fp);
					if(ch == '=')out(BUD, "!="); 
					else 
					{
						fseek(fp, -1, 1);
						report_error();
					}
				break;
		
		case'+':
//					ch = fgetc(fp);
//					fseek(fp, -1, 1);
					out(PlUS, "+") ;
					
				break;
				
		case'-':
//					ch = fgetc(fp);
//					fseek(fp, -1, 1);
					out(PlUS, "-") ;
				break;
				
		case'*':
//					ch = fgetc(fp);
//					fseek(fp, -1, 1);
					out(STAR, "*") ;
				break;
				
		case'/':
//					//ch = fgetc(fp);
//					fseek(fp, -1, 1);
					out(DIVOP, "/") ;
				break;
				
		case'(':
//					ch = fgetc(fp);
//					fseek(fp, -1, 1);
					out(LP, "(");	
				break;
				
		case')':
//					ch = fgetc(fp);
//					fseek(fp, -1, 1);
					out(RP, ")");
				break;
					
		case'{':
//					ch = fgetc(fp);
//					fseek(fp, -1, 1);
					out(LC,"{");
				break;
					
		case'}':
//					ch = fgetc(fp);
//					fseek(fp, -1, 1);
					out(RC,"}");
				break;
					
		case',':
//					ch = fgetc(fp);
//					fseek(fp, -1, 1);
					out(COMMA,",");
				break;
					
		case';':
//					ch = fgetc(fp);
//					fseek(fp, -1, 1);
					out(SEMI,";");
				break;
				
		case' ':
				break;
		
		case'\n':
				break;
				
		case'\t':
				break;
		
		case'$':
				report_error();
				break;
		case'&':
				report_error();
				break;
		case'%':
				report_error();
				break;
	}
}

int main()
{
	char w;
	FILE *fp;
    fp=fopen("tests.txt","r");
    if (fp == NULL)
    {
        printf("can't open file!\n");
        return 0;
    }
    while(!feof(fp))
    {
		scanner_example(fp);	
	}
    
    fclose(fp);
    return 0;  
}

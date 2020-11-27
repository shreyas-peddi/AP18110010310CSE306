/*
Implement lexical analyzer using C for recognizing the following tokens:
• A minimum of 10 keywords of your choice
• Identifiers with the regular expression : letter(letter | digit)*
• Integers with the regular expression: digit+
• Relational operators: <, >, <=, >=, ==, !=
• Storing identifiers in symbol table.
• Using files for input and output.**/

#include<stdio.h>
#include<ctype.h>
#include<string.h>
char keyword[24][30]={"int","while","break","for","do","if","float","char","switch","double","short","long","unsigned","sizeof","else","register","extern","static","auto","case","break","volatile","enum","typedef"};

int check_keyword(char s[]) 
{
	for(int i=0;i<24;++i)
		if(strcmp(s,keyword[i])==0)
			return 1;
	return 0;
}

void store_symbol_tab(char id[], char symbol_tab[][30])
{
	int i;
	for(i=0; strcmp(symbol_tab[i],"")&&i<20;++i)
		if(!strcmp(symbol_tab[i],id))
			return;
	if(i==20)
		{ 
		printf("\nOverflow!");
		return;
		}
	strcpy(symbol_tab[i],id);
}

int main()
{
	FILE *read,*write;
	char c,id[30], num[10];
	int state=0,i=0,j=0;
	read=fopen("read.txt","r");
	write=fopen("write.txt","w");
	
	char symb_tab[20][30];
	for(int i=0;i<20;++i)
		strcpy(symb_tab[i],"");	

	while((c=fgetc(read))!=EOF)
	{
		switch(state)
		{
			case 0: 
				if(isalpha(c)||c=='_')
				{
					state=1;
					id[i++]=c;
				}
				else if(isdigit(c))
				{
					state=3;
					num[j++]=c;
				}
				else if(c=='<' || c=='>')
					state=5;
				else if(c=='=' || c=='!')
					state=8;
				else if(c=='/')
					state=10;
				else if(c==' ' || c=='\t' || c=='\n' || c=='\r'); 
				else
					fprintf(write,"\n%c",c);
				break;
			case 1:
				if(isalnum(c)||c=='_')
					id[i++]=c;   
				else{
					id[i]='\0';
					if(check_keyword(id))
						fprintf(write," \n%s : keyword ",id);
					else{
						fprintf(write,"\n%s : identifier",id);
						
						store_symb_tab(id,symb_tab);
					}
					state=0;
					i=0;
					ungetc(c,read);
				}
				break;
			case 3:
				if(isdigit(c))
				    num[j++]=c; 
				else{
					num[j]='\0';
					fprintf(write," \n%s: number",num);
					state=0;
					j=0;
					ungetc(c,read);
				}
				break;
			case 5:
				if(c=='='){
					
					fseek(read,-2,SEEK_CUR); 
					c=fgetc(read); 
					if(c=='<')
						fprintf(write,"\n<=: relational operator LE");
					else
						fprintf(write,"\n<=: relational operator GE");
					c=fgetc(read); 
					state=0;
				}
				else{
					
					fseek(read,-2,SEEK_CUR); 
					c=fgetc(read); 
					if(c=='<')
						fprintf(write,"\n<: relational operator LT");
					else
						fprintf(write,"\n>: relational operator GT");
					
					state=0;
					
				}
				break;
			case 8:
				if(c=='='){
					
					fseek(read,-2,SEEK_CUR); 
					c=fgetc(read); 
					if(c=='=')
						fprintf(write,"\n==: relational operator EQ");
					else
						fprintf(write,"\n!=: relational operator NE");
					c=fgetc(read);
					state=0;
				}
				else{ 
					fprintf(write,"\n!");
					ungetc(c,read); 
					state=0; 
				}
				break;
			case 10:
				if(c=='*')
					state=11;
				else{
					fprintf(write,"\n/%c: invalid lexeme",c);
					state=0;
				}
				break;
			case 11: 
				if(c=='*')
					state=12;
				
				break;
			case 12:
				if(c=='*');
				else if(c=='/')
					state=0;
				else
					state=11;
				break;

		}
	}
	if(state==11)
		fprintf(write,"\ncomment did not close");
	fclose(read);
	fclose(write);
	
	/*for(int i=0; strcmp(symb_tab[i],"")&&i<20;++i)
    	 printf("\n%s",symb_tab[i]);*/

	return 0;
}

%{ 
#include<stdio.h> 
%} 
%token DIGIT 
%% 
S: E { printf("The result is =%d\n",$1);} 
; 
E: E'+'T { $$ = $1 + $3; } 
| T {$$ = $1;} 
; 
T: T'*'F {$$ = $1 * $3; } 
| F {$$ = $1;} 
; 
F: '('E')' {$$ = $2;} 
| DIGIT {$$ = $1;} 
; 
%% 
main() 
{ 
yyparse(); 
} 
yyerror(char *s) 
{ 
printf("%s",s); 
} 

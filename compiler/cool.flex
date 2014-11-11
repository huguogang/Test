/*
 *  The scanner definition for COOL.
 */

/*
 *  Stuff enclosed in %{ %} in the first section is copied verbatim to the
 *  output, so headers and global definitions are placed here to be visible
 * to the code in the file.  Don't remove anything that was here initially
 */
%{
#include <cool-parse.h>
#include <stringtab.h>
#include <utilities.h>

/* The compiler assumes these identifiers. */
#define yylval cool_yylval
#define yylex  cool_yylex

/* Max size of string constants */
#define MAX_STR_CONST 1025
#define YY_NO_UNPUT   /* keep g++ happy */

extern FILE *fin; /* we read from this file */

 /* define YY_INPUT so we read from the FILE fin:
  * This change makes it possible to use this scanner in
  * the Cool compiler.
  */
#undef YY_INPUT
#define YY_INPUT(buf,result,max_size) \
	if ( (result = fread( (char*)buf, sizeof(char), max_size, fin)) < 0) \
		YY_FATAL_ERROR( "read() in flex scanner failed");

char string_buf[MAX_STR_CONST]; /* to assemble string constants */
char *string_buf_ptr;

extern int curr_lineno;
extern int verbose_flag;

extern YYSTYPE cool_yylval;

 /*
  *  Add Your own definitions here
  */
void addLine();

int string_len;
void appendChar(char c);
int string_overflow_flag;
int string_resume_error; //error in string that allow lexing resume after cloing "

int commentLevel = 0;
%}

/*
 * Define names for regular expressions here.
 */

DARROW          =>
DIGIT           [0-9]

%x STRING
%x COMMENT
%%

 /*
  * Keywords are case-insensitive except for the values true and false,
  * which must begin with a lower-case letter.
  */
(?i:class)          {return CLASS;}
(?i:else)           {return ELSE;}
(?i:if)             {return IF;}
(?i:fi)             {return FI;}
(?i:in)             {return IN;}
(?i:inherits)       {return INHERITS;}
(?i:isvoid)         {return ISVOID;}
(?i:let)            {return LET;}
(?i:loop)           {return LOOP;}
(?i:pool)           {return POOL;}
(?i:then)           {return THEN;}
(?i:while)          {return WHILE;}
(?i:case)           {return CASE;}
(?i:esac)           {return ESAC;}
(?i:new)            {return NEW;}
(?i:of)             {return OF;}
(?i:not)            {return NOT;}
t(?i:rue)           {cool_yylval.boolean = true; return BOOL_CONST;}
f(?i:alse)          {cool_yylval.boolean = false; return BOOL_CONST;}

"--"[^\n]*           {/* skip one line comments */}
 /*
  *  Nested comments
  */
"(*"            {BEGIN(COMMENT); commentLevel = 1;}
<COMMENT>{
"(*"            {commentLevel++;}
"*)"            {commentLevel--;
                if(commentLevel == 0) {
                    BEGIN(INITIAL);
                }
                }
\n              {addLine();}
<<EOF>>         {
                BEGIN(INITIAL);
                cool_yylval.error_msg = "EOF in comment";
                return ERROR;}
.               {}                
}            
"*)"            {cool_yylval.error_msg = "Unmatched *)";
                return ERROR;}
 /*
  *  The multiple-character operators.
  */
{DARROW}		{ return (DARROW); }


{DIGIT}+        {cool_yylval.symbol = inttable.add_string(yytext);
                 return INT_CONST;}
[a-z][a-zA-Z0-9_]*      {cool_yylval.symbol = idtable.add_string(yytext);
                         return OBJECTID;}
[A-Z][a-zA-Z0-9_]*      {cool_yylval.symbol = idtable.add_string(yytext);
                         return TYPEID;}
 /*
  *  String constants (C syntax)
  *  Escape sequence \c is accepted for all characters c. Except for 
  *  \n \t \b \f, the result is c.
  *
  * \"(\\.|\\\n|[^\\"])*\"  {cool_yylval.symbol = idtable.add_string(yytext);
  *                       return STR_CONST;}
  */
\"              {BEGIN(STRING); 
                string_buf_ptr = string_buf;
                string_len = 0;
                string_overflow_flag = 0;
                string_resume_error = 0;
                }
<STRING>{
\n              {
                BEGIN(INITIAL);
                if(!string_overflow_flag && !string_resume_error) 
                {
                    cool_yylval.error_msg = "Unterminated string constant";
                    return ERROR;
                }
                }    
<<EOF>>         {
                BEGIN(INITIAL);
                cool_yylval.error_msg = "EOF in string constant";
                return ERROR;}
\0              {
                string_resume_error = 1;
                cool_yylval.error_msg = "String contains null character";
                return ERROR;
                }
\\\0            {
                string_resume_error = 1;
                cool_yylval.error_msg = "String contains escaped null character";
                return ERROR;
                }                                            
\"              {BEGIN(INITIAL);
                if(string_overflow_flag) 
                {
                    cool_yylval.error_msg = "String constant too long";
                    return ERROR;
                }
                if(!string_resume_error) 
                {
                    *string_buf_ptr = '\0';
                    cool_yylval.symbol = idtable.add_string(string_buf);
                    return STR_CONST;
                }
                }
\\\n            {addLine(); 
                /* append new line */
                appendChar('\n');
                }
\\t             {/* append tab */
                appendChar('\t');
                }
\\b             {/* append backspace */
                appendChar('\b');
                }
\\f             {/* append formfeed */
                appendChar('\f');
                }
\\n             {/* append newline */
                appendChar('\n');
                }
\\.             {/* append the char */
                appendChar(yytext[1]);
                }
[^\\\n\"\0]+      {/* append YYTEXT */
                char *ptr = yytext;
                while ( *ptr ) 
                {
                    appendChar(*ptr);
                    ptr++;
                }
                }
}

 /*
  * Operators
  */
"+"         {return '+';}
"-"         {return '-';}
"*"         {return '*';}
"/"         {return '/';}
"~"         {return '~';}
"<"         {return '<';}
"="         {return '=';}
"."         {return '.';}
"@"         {return '@';}
"{"         {return '{';}
"}"         {return '}';}
"("         {return '(';}
")"         {return ')';}
";"         {return ';';}
":"         {return ':';}
","         {return ',';}
"<-"        {return ASSIGN;}
"<="        {return LE;}


[ \f\r\t\v] {/*ignore white space*/}
\n          {addLine();}
.           {cool_yylval.error_msg = yytext; return ERROR;}
%%

void addLine() 
{
    curr_lineno++;
}
void appendChar(char c) 
{
    if(string_overflow_flag) 
    {
        return;
    }
    if(++string_len >= MAX_STR_CONST) 
    {
        string_overflow_flag = 1;
        return;
    }
    *string_buf_ptr++ = c;
}
#define LSH_TOK_DELIM " \t\r\n\a"
#define semiColon ";"

char process_name[4000005][50];
char *name; 
char hostname[100];
char originalPath[1024];
int position;

int takeInput(char* str);
char **split_cmd(char *line,char* delim);
int bgNf(int background,char **tokens);
void handler(int sig);
void cmdREMINDME(char **tokens);
void cmdCLOCK(char **tokens);
int cmdPINFO(char ** tokens) ;
void getpath(char originalPath[]);
void cmdCD(char **tokens,char originalPath[]);
void cmdPWD();
void cmdECHO(char** tokens);
void cmdLS(char **tokens);
void cmds(char **tokens);
void cmdSETENV(char **tokens);
void cmdUNSETENV(char **tokens);
void redirect(char **args);
void pipes(char **toks);
void cmdBG(char **tokens);
void cmdFG(char **tokens);
void cmdOVERKILL();
void cmdKJOB(char **toks);
void cmdJOBS();
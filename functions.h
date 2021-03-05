#ifndef __FUNCTIONS_H
#define __FUNCTIONS_H
void intialize();
void sub_intialize();
void prompt();
void separating_buff(char * buff, char *parts[]);
void separating_str(char * buff, char *pieces[]);
void execute_theline_buitin();
void execute_theline_other();
void cd_implt(char * pieces[]);
void echo_implt();
void ls_implt();
void pinfo_implt();
int is_builtin_cmd();
void store_history();
void hist_implt();

char *parts[80];
char *pieces[20];
int cnt_pieces;
int cnt_no_commands;

int background;
int bgprpidarr[1024];
char *bgprpidnamearr[1024];
int cnt_of_bg;
int index_of_hist;
int is_historyfull;

struct passwd *fas;
char base_dir[200];
char cwd_name[200];
char *cwd_asreq;
char hstnam[50];
char *buffer;
char *buffer_dup;



#endif
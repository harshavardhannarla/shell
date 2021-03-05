#include "functions.h"
#include "headers.h"


int convert_to_int(char * str)
{    int t=0,i=0,s=1;
     if(str[i]=='-')
     { s=-1;i++;}

     for(;i < strlen(str);i++)
   {   t = t*10 + (str[i]-'0');
   }
return t*s;

}

int is_builtin_cmd()
{  if(strcmp(pieces[0],"cd")==0 || strcmp(pieces[0],"echo")==0 || strcmp(pieces[0],"ls")==0 || strcmp(pieces[0],"pinfo")==0 ||strcmp(pieces[0],"history")==0)
    return 1;
    else
    return 0;
}




void intialize()
{    
    gethostname(hstnam,50);
    fas= getpwuid(getuid());
    getcwd(base_dir,sizeof(base_dir));
    cnt_of_bg = 0; 
    index_of_hist =0;
}

void sub_intialize()
{   getcwd(cwd_name,sizeof(cwd_name));
    if(strncmp(cwd_name,base_dir,strlen(base_dir))==0)
     cwd_asreq = &cwd_name[strlen(base_dir)];
    else
     cwd_asreq = cwd_name;
   
}

void prompt() 
{    
  printf("<%s@%s:~%s>",fas->pw_name,hstnam,cwd_asreq);

}

void separating_str(char * buff, char *pieces[])
{  cnt_pieces=0;
   char * token = strtok(buff," \t\n"); 

   while( token!=NULL )
   {
       pieces[cnt_pieces] = strdup(token);
       cnt_pieces++;
       token = strtok(NULL," \t\n");
   
   }
    pieces[cnt_pieces]=NULL;
}

void separating_buff(char * buff, char *parts[])
{    cnt_no_commands = 0;
   
   char * token = strtok(buff,";\n");

   while( token!=NULL )
   {
       parts[cnt_no_commands] = strdup(token);
       cnt_no_commands++;
       token = strtok(NULL,";\n");
   
   }
   parts[cnt_no_commands]=NULL;   

}
void execute_theline_other()
{       int k =0; 
        k=execvp(pieces[0],pieces);
        if(k==-1)
        printf("%s: command not found\n",pieces[0]);
       // perror("error:");
        exit(0); 
       

}



void execute_theline_buitin()
{     if(strcmp(pieces[0],"cd")==0)
        cd_implt(pieces);
       else if(strcmp(pieces[0],"echo")==0)
           echo_implt();
       else if(strcmp(pieces[0],"ls")==0)
          ls_implt();
       else if(strcmp(pieces[0],"pinfo")==0)
          pinfo_implt();
       else if(strcmp(pieces[0],"history")==0)
          hist_implt();

}


void echo_implt()
{   for(int i=1;i<cnt_pieces;i++)
    printf("%s ",pieces[i]);
    printf("\n");
    
}

void pwd_implt(char *pieces)
{   printf("%s",cwd_name);

}

void cd_implt(char * pieces[])
{    if(cnt_pieces>1)
    {  if(strcmp(pieces[1],"~") == 0)
       chdir(base_dir);
       else if(strcmp(pieces[1],".")==0)
        {}
       else
       { if(chdir(pieces[1])==-1)
           perror("Error");
       }
    }

    else
      {   chdir(base_dir); 
          
      }
      
  
}



void pinfo_implt()
{   int pid;
    

     if(cnt_pieces > 1)
      {   pid = convert_to_int(pieces[1]);
          
      }
          
     else
      { pid=getpid();}
   
   char filename_stat[200];
  sprintf(filename_stat,"/proc/%d/stat",pid);

  //  printf("%s",filename_stat);
   FILE *f = fopen(filename_stat,"r");
    if( f == NULL )
    perror("Error:");
   
   char state[2];
   long unsigned int vm_sz;
   int t = fscanf(f,"%*d%*s%s%*d%*d%*d%*d%*d%*u%*u%*u%*u%*u%*u%*u%*d%*d%*d%*d%*d%*d%*u%lu",state,&vm_sz);
  
   if(t<=0)
   printf("notworking\n");
   fclose(f);

   char filename_exe[200];
   sprintf(filename_exe,"/proc/%d/exe",pid);
   char *exe_path= malloc(500);
   int k= readlink(filename_exe,exe_path,500);
    if(k ==-1)
   perror("Error:");
   
   exe_path[k]='\0';
  
   printf("pid -- %d\nProcess Status -- %s\nmemory -- %lu\nExecutable Path -- %s\n",pid,state,vm_sz,exe_path);



}
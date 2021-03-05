#include "functions.h"
#include "headers.h"








void handler()
{    int corpse;
     int status;
     char *pr_name; 
   while(true)
    { corpse = waitpid((pid_t)-1, &status, WNOHANG);
     if(corpse ==0)
        return;
     
     else if(corpse == -1)
         return;
     
     else if(corpse > 0)
         { int i;
           for(i=0;i<cnt_of_bg;i++)
           if(bgprpidarr[i] == corpse)
            break;
            if (WIFEXITED(status)) 
                fprintf(stderr,"\n%s with pid %d exited \n", bgprpidnamearr[i],corpse);
            else if (WIFSIGNALED(status)) 
                fprintf(stderr,"\n%s with pid %d killed by signal %d\n",bgprpidnamearr[i],corpse, WTERMSIG(status));
             else if (WIFSTOPPED(status)) 
                fprintf(stderr,"\n%s with pid %d stopped by signal %d\n", bgprpidnamearr[i],corpse,WSTOPSIG(status));
             else if (WIFCONTINUED(status)) 
                fprintf(stderr,"\n%s with pid %d continued\n", bgprpidnamearr[i],corpse);
            
           
           
           
           
         //  printf("\n%s with pid %d exited normally\n",bgprpidnamearr[i],corpse);

         }
    } 
   

}




int main()
{  
    size_t buff_sz = 1000;
    buffer= (char *)malloc(buff_sz*sizeof(char));
    buffer_dup=(char *)malloc(buff_sz*sizeof(char));
    intialize();

    
    while (1)
    {  
        signal(SIGCHLD,handler);
        sub_intialize();
        prompt();
       
        
        getline(&buffer,&buff_sz,stdin);
        store_history();
        strcpy(buffer_dup,buffer);

      separating_buff(buffer_dup,parts);

      for(int i = 0;i<cnt_no_commands;i++)
      { 
        separating_str(parts[i],pieces);
 
       if(strcmp(pieces[cnt_pieces-1],"&")==0)
       { pieces[cnt_pieces-1] = NULL;
         cnt_pieces--;
         background =1;
       }
      else
      background = 0;
     
      
      if(background && is_builtin_cmd())
       background = 0;
       
      pid_t pid;
      
     if(strcmp(pieces[0],"exit")==0)
     return 0;
     

      if(background)
      {  pid=fork();
        
        if(pid==0)
         {
           setpgid(0,0);
           execute_theline_other();
         }
       
       printf("started %s with pid %d\n",pieces[0],pid);
       bgprpidarr[cnt_of_bg] = pid;
       bgprpidnamearr[cnt_of_bg] = malloc(100);
       
       strcpy(bgprpidnamearr[cnt_of_bg],pieces[0]);
       cnt_of_bg++;  
      }
     
      else
      { if(is_builtin_cmd())
         execute_theline_buitin();
        else 
        { if(fork()!=0)
          wait(NULL);
      
         else
           execute_theline_other();
         
        }
      }

      }
    }
}

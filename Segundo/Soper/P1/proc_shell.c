#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define SIZE 100
#define NARG 30

typedef struct {
	    char string[SIZE];
		    char *array[NARG];
}Est;


void *chop(void * arg){
	    Est * est = arg;
		    int i=1;
			    est->array[0] = strtok(est->string," ");
				    /*printf("%s\n", est->array[0]);*/
				    while(((est->array[i]) = strtok(NULL," "))!=NULL)
						    {
								        /*
										 *         printf("%s\n", est->array[i]);
										 *                 */
								        i++;
										    }
					    
					    est->array[i] = NULL;
}

int main() {
	    int status,error,i=0;
		    pid_t pid;
			    Est est;
				    pthread_t h1;
					    printf("Inserte línea de comando:");
						    while(fgets(est.string,SIZE,stdin)!=NULL){
								        i=0;
										        while(est.string[i]!='\n'){
													            i++;
																        }
												        est.string[i]='\0';

														        error = pthread_create(&h1, NULL,chop,&est);
																        if (error!=0){
																			            fprintf(stderr, "pthread_create: %s\n", strerror(error));
																						        }

																		        error = pthread_join(h1,NULL);
																				        if (error!=0){
																							            fprintf(stderr, "pthread_join: %s\n", strerror(error));
																										        }

																						        
																						        pid = fork();
																								        if(pid<0){
																											            perror("fork");
																														            exit(EXIT_FAILURE);
																																	        }
																										        else if (pid == 0) {

																													            int i=0;
																																            while(est.array[i]!=NULL)
																																				            {
																																								                printf("%s",est.array[i]);
																																												                i++;
																																																            }

																																			            if(execvp(est.array[0],est.array)){
																																							                perror("execvp");
																																											                exit(EXIT_FAILURE);
																																															            }
																																						        }
																												        else if (pid > 0) {
																															            wait(&status);
																																		            if(WIFEXITED(status)){
																																						                fprintf(stderr,"\nExited with value %d\n", WEXITSTATUS(status));
																																										            }
																																					            else if(WIFSIGNALED(status)){
																																									                fprintf(stderr, "\nTerminated by signal %d\n", WTERMSIG(status));
																																													            }
																																								           
																																								        }
																														        
																														        est.string[0]='\0';
																																        printf("\033[0;33mInserte línea de comando\033[0;31m$\033[0m");

																																		    }
							    printf("\nExited\n");
								     return 0;
}


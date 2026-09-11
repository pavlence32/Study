#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
void report_self(void) {
    printf("Процесс: ID = %d, ID родителя = %d\n", getpid(), getppid());
}

void report_spawn(pid_t child_pid) {
    printf("Процесс с ID %d породил процесс с ID %d\n", getpid(), child_pid);
}

void report_exit(void) {
    printf("Процесс с ID %d и ID родителя %d завершает работу\n", getpid(), getppid());
}

int main(void) {
    pid_t pid;
    report_self();
    pid = fork();                       
    if (pid == 0) {
        report_self();
        pid = fork();                   
        if (pid == 0) {
            report_self();

            pid = fork();               
            if (pid == 0) {
                report_self();          
                report_exit();
                exit(0);
            }
            report_spawn(pid);

            pid = fork();               
            if (pid == 0) {
                report_self();
                execlp("ls", "ls", "-l", NULL);  
                perror("execlp");                
                exit(1);
            }
            report_spawn(pid);

            pid = fork();               
            if (pid == 0) {
                report_self();          
                report_exit();
                exit(0);
            }
            report_spawn(pid);

            wait(NULL);                 
            wait(NULL);
            wait(NULL);

            report_exit();             
            exit(0);
        }
        report_spawn(pid);              

        wait(NULL);                     
        report_exit();                  
        exit(0);
    }
    report_spawn(pid);                  

    pid = fork();                       
    if (pid == 0) {
        report_self();                  
        report_exit();
        exit(0);
    }
    report_spawn(pid);                  

    wait(NULL);                       
    wait(NULL);                        

    report_exit();                      
    return 0;
}
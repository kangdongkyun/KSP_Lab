#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <dirent.h>
#include <fnmatch.h>
#include <pwd.h>

#include <sys/stat.h>
#include <sys/types.h>

#define proc_path "/proc/"


typedef struct process_info {
    char cmd[16];
    char state;
    uid_t uid;
} pi;

pi* parse_process_status(pid_t pid) {
    char proc_name[20] = {0,};
    pi* p = (pi *)malloc(sizeof(pi));
    
    // need to parse "Name, State, Uid, Gid"
    sprintf(proc_name, "/proc/%d/status", pid);

    FILE* proc = fopen(proc_name, "r");
    if (!proc) return 0;
    else {
        char buf[256] = {0,};
        fscanf(proc, "Name:\t%s\n", p->cmd);
        fgets(buf, 256, proc); // dummy
        fscanf(proc, "State:  %c\n", &p->state);
        for(int i = 0; i < 6; ++i) fgets(buf, 256, proc); // dummy
        fscanf(proc, "Uid:\t%d\n", &p->uid);
    }
    fclose(proc);   
    return p;
}

int filter_proc(const struct dirent64 *dir) {
    return !fnmatch("[1-9]*", dir->d_name, 0);
}

int get_all_proc(void) {
    struct dirent64 **proclist;

    int n = scandir64(proc_path, &proclist, filter_proc, NULL);
    if (n < 0) return -1;
    else {
        printf("UID     \t\tPID\t\tPGID\t\tState\t\tCMD\n");

        for (register int i = 0; i < n; ++i) {
            pid_t pid = strtol(proclist[i]->d_name, 0, 10);
            pid_t pgid = getpgid(pid);

            pi* p = parse_process_status(pid);
            printf("%-16s\t%-6d\t\t%-6d\t\t%c\t\t%-32s\n", getpwuid(p->uid)->pw_name, pid, pgid, p->state, p->cmd);

            free(proclist[i]);
            free(p);
        }
    }
    return 0;
}

int main(int argc, char* argv[]) {
    if (argc != 1) {
        printf("%s \n", argv[0]);
        return 0;
    }

    pid_t pid = getpid();
    pid_t ppid = getppid();
    printf("[+] Current PID : %d PPID : %d\n", pid, ppid);

    get_all_proc();

    return 1;
}
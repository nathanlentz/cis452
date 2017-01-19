/*********************************
* CIS 452 W17: Lab 1 - Assignment
* @author: Nathan Lentz
* 01.12.17
**********************************/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <pwd.h>

#define ENV_SIZE 17

int main()
{
    printf("Beginning user analysis . . .\n");
    char *user = getlogin();

    // Allocate memory for password file
    struct passwd *pwd = calloc(1, sizeof(struct passwd));
    char buf[1024];

    if(getpwnam_r(user, pwd, buf, sizeof(buf), &pwd)){
        perror("\ngetpwnam_r");
    }

    char hostname[1024];
    hostname[1023] = '\0';
    gethostname(hostname, 1023);

    // Print found data
    printf("\nuser: %s\n", user);
    printf("uid: %d\n", pwd->pw_uid);
    printf("gid: %d\n", pwd->pw_gid);
    printf("host: %s\n", hostname);

    // Get entries from /etc/passwd
    int i;
    struct passwd *p;
    for(i = 0; i < 5; i++){
        p = getpwuid(i);
        printf("entry %d: %s\n", i, p->pw_name);
    }

    char *env;
    char *foundenv;
    env = malloc(ENV_SIZE);
    printf("\nEnvironment variable desired? ");
    scanf("%s", env);
    foundenv = getenv(env);
    if(foundenv){
        printf("\nValue is: %s\n\n", foundenv);
    }
    else {
        printf("Could not find environment variable with that name.\n");
    }

    // RELEASE
    free(env);
    free(pwd);

    return 0;
}



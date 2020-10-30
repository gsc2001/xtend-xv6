#include "types.h"
#include "stat.h"
#include "user.h"

int main(int argc, char **argv) {
    if(argc <= 1)
    {
        printf(2,"time: No command to time\n");
        exit();
    }
    int forkReturn = fork();

    if(forkReturn < 0)
    {
        printf(2, "time: Unable to run command\n");
        exit();
    }
    else if(forkReturn == 0)
    {
        printf(1, "Started timing %s\n", argv[1]);
        if(exec(argv[1], argv + 1) < 0)
        {
            printf(2, "time: Unable to run command\n");
            exit();
        }
    }
    else {
        int wtime, rtime;
        int ret = waitx(&wtime, &rtime);

        printf(1, "time: %s returned, waitx return: %d, Waiting Time:%d, Running time: %d\n\n",argv[1],ret, wtime, rtime);
        exit();
    }
}

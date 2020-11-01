
#include "types.h"
#include "user.h"

int arr[5], k;
int main(int argc, char *argv[])
{
    for (int i = 0; i < 5; i++)
        arr[i] = -1;
    k = 0;
    int number_of_processes = atoi(argv[1]);
    printf(1, "Creating %d processes\n", number_of_processes);
    int j;
    for (j = 0; j < number_of_processes; j++)
    {
        int pid = fork();
        if (pid < 0)
        {
            printf(1, "Fork failed\n");
            continue;
        }
        if (pid == 0)
        {
            int length = 1e8;
            if (j % 2 == 0)
            {
                length = 1e5;
            }
            int _n = 5;
            volatile int i;
            for (volatile int k = 0; k < _n; k++)
            {
                // if (k <= j)
                // {
                //     sleep(200); //io time
                // }
                // else
                // {

                for (i = 0; i < length; i++)
                {
                    ; //cpu time
                }
                if (j % 2 == 0)
                {
                    sleep(200);
                }
                // }
            }

            // printf(1, "Process: %d Finished\n", j);
            exit();
        }
        else
        {
            // printf(1, "Process %d -> %d\n", j, pid);
            // int a = set_priority(100 - (20 + j), pid); // will only matter for PBS, comment it out if not implemented yet (better priorty for more IO intensive jobs)
            // printf(1, "Process %d -> %d\n", j, a);
        }
    }
    for (j = 0; j < number_of_processes + 5; j++)
    {
        wait();
    }
    exit();
}

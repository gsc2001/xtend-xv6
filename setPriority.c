#include "types.h"
#include "stat.h"
#include "user.h"

int main(int argc, char **argv)
{
    if (argc != 3)
    {
        printf(2, "Wrong format for setPriority; Usage setPriority new_priority pid\n");
        exit();
    }

    printf(2, "PID: %d PRIOR: %d\n", atoi(argv[1]), atoi(argv[2]));
    int _ret = set_priority(atoi(argv[1]), atoi(argv[2]));
    if (_ret == -1)
    {
        printf(2, "Invalid priority of pid\n");
    }
    exit();
}
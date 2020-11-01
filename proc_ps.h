struct proc_ps
{
    int pid;
    int priority;
    int r_time;
    int w_time;
    int state;
    int n_run;
    int cur_q;
    int q_ticks[5];
};
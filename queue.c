
#include "types.h"
#include "defs.h"
#include "memlayout.h"
#include "mmu.h"
#include "param.h"
#include "proc.h"
#include "spinlock.h"
#include "traps.h"
#include "x86.h"

proc_node *q_alloc()
{
    for (int i = 0; i < NPROC; i++)
    {
        if (store[i]->use == 0)
        {
            store[i]->use = 1;
            return &store[i];
        }
    }
    return -1;
}

void q_free(proc_node *p)
{
    p->use = 0;
}

proc_node *push(proc_node *head, proc_node *p)
{
    proc_node *new = q_alloc();
    new->p = p;
    new->next = 0;

    if (head == 0)
    {
        return new;
    }

    proc_node *i = head;
    while (i->next != 0)
    {
        i = i->next;
    }
    i->next = new;

    return head;
}

proc_node *pop(proc_node *head)
{
    if (head == 0)
        return 0;

    proc_node *t = head->next;
    q_free(head);
    return t;
}

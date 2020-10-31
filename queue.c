
#include "types.h"
#include "defs.h"
#include "memlayout.h"
#include "mmu.h"
#include "param.h"
#include "proc.h"
#include "spinlock.h"
#include "traps.h"
#include "x86.h"

struct proc_node *q_alloc()
{
    for (int i = 0; i < NPROC; i++)
    {
        if (store[i].use == 0)
        {
            // cprintf("IN ALLOCATION\n");
            store[i].use = 1;
            return &store[i];
        }
    }
    return 0;
}

void q_free(struct proc_node *p)
{
    // cprintf("FREEING %d\n", p->p->pid);
    p->use = 0;
}

struct proc_node *push(struct proc_node *head, struct proc *p)
{
    struct proc_node *new = q_alloc();
    new->p = p;
    new->next = 0;

    if (head == 0)
    {
        return new;
    }

    struct proc_node *i = head;
    while (i->next != 0)
    {
        i = i->next;
    }
    i->next = new;

    return head;
}

struct proc_node *pop(struct proc_node *head)
{
    if (head == 0)
        return 0;

    struct proc_node *t = head->next;
    q_free(head);
    return t;
}

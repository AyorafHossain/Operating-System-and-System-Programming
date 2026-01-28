#include <stdio.h>


int SIZE, buffer[100],in = 0, out = 0 ,mutex = 1,F=0,E;


int wait(int s)
{
    while(s<=0);
    s = s - 1;
    return s;
}


int signal(int s)
{
    s = s + 1;
    return s;
}


void produce(int item)
{
    //Check Overflow
    if (E == 0)
    {
         printf("Buffer Full!\n");

    }

    else
    {
        E = wait(E);
        mutex = wait(mutex);

        buffer[in] = item;
        in = (in + 1) % SIZE;
        printf("Produced: %d\n", item);

        mutex = signal(mutex);
        F = signal(F);
    }
}

void consume()
{
    if (F == 0)
    {
        printf("Buffer Empty!\n");
    }

    else
    {
        F = wait(F);
        mutex = wait(mutex);

        int item = buffer[out];
        out = (out + 1) % SIZE;
        printf("Consumed: %d\n", item);

        mutex = signal(mutex);
        E = signal(E);
    }
}

int main()
{
    int choice, item;

    printf("Enter buffer size: ");
    scanf("%d", &SIZE);

    E = SIZE;

    while (1)
    {
        printf("\n1. Produce\n2. Consume\n3. Exit\nEnter choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            printf("Enter item to produce: ");
            scanf("%d", &item);
            produce(item);
            break;
        case 2:
            consume();
            break;
        case 3:
            return 0;
        default:
            printf("Invalid choice!\n");
        }
    }
}


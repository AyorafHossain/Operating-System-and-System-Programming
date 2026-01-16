#include <stdio.h>

int main()
{
    int i, j = 0, page_amount, page[50], frame[10],frame_amount, k, avail, miss = 0, hit = 0;

    printf("Enter Amount of pages: ");
    scanf("%d", &page_amount);

    printf("Enter page reference string:\n");
    for (i = 0; i < page_amount; i++)
    {
        scanf("%d", &page[i]);
    }

    printf("Enter amount of frames: ");
    scanf("%d", &frame_amount);

    /* Initialize frames */
    for (i = 0; i < frame_amount; i++)
    {
        frame[i] = -1;
    }

    printf("\n------------------------------------------\n");
    printf("Page\tFrame Status\n");
    printf("------------------------------------------\n");

    for (i = 0; i < page_amount; i++)
    {
        printf("%d\t", page[i]);
        avail = 0;

        /* Check page hit */
        for (k = 0; k < frame_amount; k++)
        {
            if (frame[k] == page[i])
            {
                avail = 1;
                hit++;
                break;
            }
        }

        /* Page fault */
        if (avail == 0)
        {
            frame[j] = page[i];
            j = (j + 1) % frame_amount;
            miss++;
        }

        /* Print frame contents */
        for (k = 0; k < frame_amount; k++)
        {
            if (frame[k] != -1)
                printf("%d ", frame[k]);
            else
                printf("- ");
        }
        printf("\n");
    }

    printf("------------------------------------------\n");
    printf("Total Page Faults = %d\n", miss);
    printf("Total Page Hits = %d\n", hit);

    /* Hit and Miss Ratio */
    printf("Page Fault Percentage = %.2f%%\n", ((float)miss / page_amount) * 100);
    printf("Page Hit Percentage = %.2f%%\n", ((float)hit / page_amount) * 100);
    return 0;
}

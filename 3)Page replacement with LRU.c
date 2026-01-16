#include <stdio.h>

int main()
{
    int i, j, k, page_amount, page[50], frame[10];
    int frame_amount, avail, miss = 0, hit = 0;
    int pos, least;

    printf("Enter amount of pages: ");
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

        /* Check Page Hit */
        for (j = 0; j < frame_amount; j++)
        {
            if (frame[j] == page[i])
            {
                avail = 1;
                hit++;
                break;
            }
        }

        /* Page Fault */
        if (avail == 0)
        {
            /* Check empty frame */
            for (j = 0; j < frame_amount; j++)
            {
                if (frame[j] == -1)
                {
                    frame[j] = page[i];
                    miss++;
                    goto print;
                }
            }

            /* Find LRU Page to Replace */
            least = 10000;
            pos = -1;

            for (j = 0; j < frame_amount; j++)
            {
                for (k = i - 1; k >= 0; k--)
                {
                    if (frame[j] == page[k])
                        break;
                }

                if (k < least)
                {
                    least = k;
                    pos = j;
                }
            }

            frame[pos] = page[i];
            miss++;
        }

    print:
        /* Print frame status */
        for (j = 0; j < frame_amount; j++)
        {
            if (frame[j] != -1)
                printf("%d ", frame[j]);
            else
                printf("- ");
        }
        printf("\n");
    }

    printf("------------------------------------------\n");
    printf("Total Page Faults = %d\n", miss);
    printf("Total Page Hits = %d\n", hit);

    /* Percentage calculation */
    printf("Page Fault Percentage = %.2f%%\n", ((float)miss / page_amount) * 100);
    printf("Page Hit Percentage = %.2f%%\n", ((float)hit / page_amount) * 100);

    return 0;
}

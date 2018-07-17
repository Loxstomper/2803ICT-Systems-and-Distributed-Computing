#include <stdio.h>
#include <stdlib.h>

void read(int length, char** input, int* nums)
{
    for (int i = 1; i < length; i ++)
    {
        nums[i - 1] = atoi(input[i]);
    }
}

int sum(int length, int* nums)
{
    int count = 0;

    for (int i = 0; i < length; i ++)
    {
        count += nums[i];
    }

    return count;
}

int compare (const void * a, const void *b)
{
    return (*(int*)b - *(int*)a);
}

int main(int argc, char ** argv)
{
    if (argc < 2)
    {
        printf("./qsort n, n, n, n...\n");
        return -1;
    }

    int * nums = malloc(sizeof(int) * argc - 1);

    read(argc, argv, nums);

    qsort(nums, argc - 1, sizeof(int), compare);

    for (int i = 0; i < argc - 1; i ++)
    {
        printf("%d ", nums[i]);
    }

    printf("= %d\n", sum(argc - 1, nums));

    free(nums);


    return 0;
}

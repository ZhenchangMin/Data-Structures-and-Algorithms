#include <stdio.h>
#include <stdlib.h>
#include <string.h>

inline int hexIndex(char c)
{
    return (c <= '9') ? c - '0' : 10 + (c - 'A');
}

int main()
{
    int n, k;
    scanf("%d%d", &n, &k);

    char *data = (char *)malloc((size_t)n * (k + 1));
    char **arr = (char **)malloc((n + 1) * sizeof(char *));
    for (int i = 1; i <= n; i++)
    {
        arr[i] = data + (size_t)(i - 1) * (k + 1);
        scanf("%s", arr[i]);
    }

    // radix sort part
    char **tmp = (char **)malloc((n + 1) * sizeof(char *));
    int cnt[16];

    for (int pos = k - 1; pos >= 0; pos--)
    {// inside the radix sort is bucket sort.
        memset(cnt, 0, sizeof(cnt));

        for (int i = 1; i <= n; i++)
            cnt[hexIndex(arr[i][pos])]++;

        for (int i = 1; i < 16; i++)
            cnt[i] += cnt[i - 1];// cleverly we turn the counts into indices. like if we wonna sort 54321, the cnt should be 12345

        for (int i = n; i >= 1; i--)
        {
            int idx = hexIndex(arr[i][pos]);
            tmp[cnt[idx]] = arr[i];// pos is the current digit we are sorting, and by using cnt_index we get to the place of tmp.
            cnt[idx]--;
        }
        // for example we sort 543321, cnt [1, 2, 3, 4, 5] is 12456, and then tmp[1] is 1, tmp[2] is 2, tmp[3] is 3, tmp[4] is 3, tmp[5] is 4, tmp[6] is 5

        char **swap = arr;
        arr = tmp;
        tmp = swap;
    }

    // prefix sum of 'F' counts, use prefix to save time
    int *prefix = (int *)malloc((n + 1) * sizeof(int));
    prefix[0] = 0;
    for (int i = 1; i <= n; i++)
    {
        int cntF = 0;
        for (int j = 0; j < k; j++)
            if (arr[i][j] == 'F')
                cntF++;
        prefix[i] = prefix[i - 1] + cntF;
    }

    int q;
    scanf("%d", &q);
    while (q--)
    {
        int l, r;
        scanf("%d%d", &l, &r);
        printf("%d\n", prefix[r] - prefix[l - 1]);
    }

}

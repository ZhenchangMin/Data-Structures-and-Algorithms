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

    char **tmp = (char **)malloc((n + 1) * sizeof(char *));
    int cnt[16];

    for (int pos = k - 1; pos >= 0; pos--)
    {
        memset(cnt, 0, sizeof(cnt));

        for (int i = 1; i <= n; i++)
            cnt[hexIndex(arr[i][pos])]++;

        for (int i = 1; i < 16; i++)
            cnt[i] += cnt[i - 1];

        for (int i = n; i >= 1; i--)
        {
            int idx = hexIndex(arr[i][pos]);
            tmp[cnt[idx]] = arr[i];
            cnt[idx]--;
        }

        char **swap = arr;
        arr = tmp;
        tmp = swap;
    }

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

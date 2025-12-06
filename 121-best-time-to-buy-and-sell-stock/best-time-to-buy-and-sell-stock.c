#define max(a, b) ((a) > (b) ? (a) : (b))

int maxProfit(int* prices, int n) {
    int* max_prices = (int*)calloc(n, sizeof(int));
    max_prices[n-1] = prices[n-1];
    for (int i = n-2; i >= 0; i--)
        max_prices[i] = max(prices[i], max_prices[i+1]);

    int max_profit = 0;
    for (int i = 0; i < n; i++)
        max_profit = max(max_profit, max_prices[i] - prices[i]);
    
    return max_profit;
}
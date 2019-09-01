int dietPlanPerformance(int*calories, int caloriesSz, int k, int lower, int upper) {
    int n = caloriesSz;
    long long sums[n + 1]; memset(sums,0,sizeof(sums));
    for (int i = 0; i < n; i++)
        sums[i + 1] = sums[i] + calories[i];
    long long points = 0;
    for (int i = 0; i + k <= n; i++) {
        long long sum = sums[i + k] - sums[i];
        if (sum < lower)
            points--;
        if (sum > upper)
            points++;
    }
    return points;
}

int*corpFlightBookings(int**bookings, int bookingsSz, int*bookings0sz, int n, int*rsz){
    int change[n+1]; memset(change, 0, sizeof(change));
    for(int z=0;z<bookingsSz;z++){int*booking = bookings[z];
        booking[0]--;
        booking[1]--;
        change[booking[0]]     += booking[2];
        change[booking[1] + 1] -= booking[2];
    }
    int*seats = calloc(n, sizeof(int));
    for(int i = 0; i < n; i++)
        seats[i] = (i == 0 ? 0 : seats[i - 1]) + change[i];
   *rsz=n;
    return seats;
}

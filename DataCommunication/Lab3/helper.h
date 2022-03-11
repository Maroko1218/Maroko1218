struct distance_table {
    int costs[4][4];
};

void shotgunlayer2(int src, int arr[4][4], int *shortestPath);
struct rtpkt makepacket(int src, int dst, int arr[4][4], int *shortestPath);
struct distance_table {
    int costs[4][4];
};

void shotgunlayer2(int src, int *arr);
int* mincost(struct distance_table node);
struct rtpkt makepacket(int src, int dst, int *arr);
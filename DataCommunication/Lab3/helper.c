#include "helper.h"
#include "prog3.h"

struct rtpkt makepacket(int src, int dst, int *arr) {
    struct rtpkt pkt;
    pkt.sourceid = src;
    pkt.destid = dst;
    for (int i = 0; i < 4; i++) {
        pkt.mincost[i] = arr[i];
    }
    return pkt;
}

int* mincost(struct distance_table node) {
    static int arr[4] = {999, 999, 999, 999};
    for (int i = 0; i < 4; i++) {
        arr[i] = node.costs[0][i];
    }
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (node.costs[i][j] < arr[j]) {
                arr[j] = node.costs[i][j];
            }
        }
    }
    return arr;
}

void shotgunlayer2(int src, int *arr) {
    for (int i = 0; i < 4; i++) {
        tolayer2(makepacket(src, i, arr));
    }
}

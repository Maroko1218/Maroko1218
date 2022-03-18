#include "helper.h"
#include "prog3.h"

int mincost(int src, int dst, int exclude, int arr[4][4]) {
    int val = 1000, values[4] = {999, 999, 999, 999};
    for (int i = 0; i < 4; i++) {
        if (i == exclude) { continue; }
        values[i] = arr[dst][i];
    }
    int temp;
    for (int i = 0; i < 4; i++) {
        if (val > values[i]) {
            val = values[i];
            temp = i;
        }
    }
    return temp;
}

struct rtpkt makepacket(int src, int dst, int arr[4][4], int *shortestPath) {
    struct rtpkt pkt;
    pkt.sourceid = src;
    pkt.destid = dst;
    for (int i = 0; i < 4; i++) {
        pkt.mincost[i] = arr[i][shortestPath[i]];
        if (shortestPath[i] == dst) {
            pkt.mincost[i] = arr[i][mincost(src, i, dst, arr)];    
        }
    }
    return pkt;
}

void shotgunlayer2(int src, int arr[4][4], int *shortestPath) { //Sends a packet to all possible nodes
    for (int i = 0; i < 4; i++) {
        if (i != src && arr[i][i] != 999) {
            tolayer2(makepacket(src, i, arr, shortestPath));
        }        
    }
}
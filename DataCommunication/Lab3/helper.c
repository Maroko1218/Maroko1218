#include "helper.h"
#include "prog3.h"

struct rtpkt makepacket(int src, int dst, int arr[4][4], int *shortestPath) {
    struct rtpkt pkt;
    pkt.sourceid = src;
    pkt.destid = dst;
    for (int i = 0; i < 4; i++) {
        pkt.mincost[i] = arr[i][shortestPath[i]];
    }
    return pkt;
}

void shotgunlayer2(int src, int arr[4][4], int *shortestPath) { //Sends a packet to all possible nodes
    for (int i = 0; i < 4; i++) {
        if (i != src && arr[i][i] != 999)
        {
            tolayer2(makepacket(src, i, arr, shortestPath));
        }        
    }
}
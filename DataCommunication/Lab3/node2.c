#include "prog3.h"
#include "helper.h"


struct distance_table dt2;

void printdt2(struct distance_table *dtptr) {
    printf("                via     \n");
    printf("   D2 |    0     1    3 \n");
    printf("  ----|-----------------\n");
    printf("     0|  %3d   %3d   %3d\n", dtptr->costs[0][0],
           dtptr->costs[0][1], dtptr->costs[0][3]);
    printf("dest 1|  %3d   %3d   %3d\n", dtptr->costs[1][0],
           dtptr->costs[1][1], dtptr->costs[1][3]);
    printf("     3|  %3d   %3d   %3d\n", dtptr->costs[3][0],
           dtptr->costs[3][1], dtptr->costs[3][3]);
}

/* students to write the following two routines, and maybe some others */

static int nodeToShortestPath[4];

void rtinit2() {
    for (int i = 0; i < 4; i++) {
        nodeToShortestPath[i] = i;
        for (int j = 0; j < 4; j++) {
            dt2.costs[i][j] = 999;
        }
    }
       
    dt2.costs[0][0] = 3;
    dt2.costs[1][1] = 1;
    dt2.costs[2][2] = 0;
    dt2.costs[3][3] = 2;       
/*
999 999 3 999
999 999 1 999
999 999 0 999
999 999 2 999
*/
    shotgunlayer2(2, dt2.costs, nodeToShortestPath);
}


void rtupdate2(struct rtpkt *rcvdpkt) {
    struct distance_table *debug = &dt2;
    int changed = 0; //boolean/flag
    for (int i = 0; i < 4; i++) {
        if (i == rcvdpkt->destid) { continue; } //Skip self node
        int old = dt2.costs[i][nodeToShortestPath[i]]; // Temporarily store old value
        int new = dt2.costs[rcvdpkt->sourceid][rcvdpkt->sourceid] + rcvdpkt->mincost[i]; // Potentially change value
        dt2.costs[i][rcvdpkt->sourceid] = new; 
        if(new < old){
            nodeToShortestPath[i] = rcvdpkt->sourceid;
            changed++;
        } 
        if (dt2.costs[i][rcvdpkt->sourceid] > 999) { dt2.costs[i][rcvdpkt->sourceid] = 999; } // if the cost was infinite reset back to 999
    }
    if (changed) {
        shotgunlayer2(rcvdpkt->destid, dt2.costs, nodeToShortestPath);
    }
    printdt2(&dt2);
}

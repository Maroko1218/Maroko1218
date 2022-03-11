#include "prog3.h"
#include "helper.h"


struct distance_table dt3;

void printdt3(struct distance_table *dtptr) {
    printf("             via     \n");
    printf("   D3 |    0     2 \n");
    printf("  ----|-----------\n");
    printf("     0|  %3d   %3d\n", dtptr->costs[0][0], dtptr->costs[0][2]);
    printf("dest 1|  %3d   %3d\n", dtptr->costs[1][0], dtptr->costs[1][2]);
    printf("     2|  %3d   %3d\n", dtptr->costs[2][0], dtptr->costs[2][2]);
}

/* students to write the following two routines, and maybe some others */

static int nodeToShortestPath[4];

void rtinit3() {
    for (int i = 0; i < 4; i++) {
        nodeToShortestPath[i] = i;
        for (int j = 0; j < 4; j++) {
            dt3.costs[i][j] = 999;
        }
    }
       
    dt3.costs[0][0] = 7;
    //dt3.costs[1][1] = 999;
    dt3.costs[2][2] = 2;
    dt3.costs[3][3] = 0;  

         
/*
999 999 999 7
999 999 999 999
999 999 999 2
999 999 999 0
*/
    shotgunlayer2(3, dt3.costs, nodeToShortestPath);
}


void rtupdate3(struct rtpkt *rcvdpkt) {
    struct distance_table *debug = &dt3;
    int changed = 0; //boolean/flag
    for (int i = 0; i < 4; i++) {
        if (i == rcvdpkt->destid) { continue; } //Skip self node
        int old = dt3.costs[i][nodeToShortestPath[i]]; // Temporarily store old value
        int new = dt3.costs[rcvdpkt->sourceid][rcvdpkt->sourceid] + rcvdpkt->mincost[i]; // Potentially change value
        dt3.costs[i][rcvdpkt->sourceid] = new; 
        if(new < old){
            nodeToShortestPath[i] = rcvdpkt->sourceid;
            changed++;
        } 
        if (dt3.costs[i][rcvdpkt->sourceid] > 999) { dt3.costs[i][rcvdpkt->sourceid] = 999; } // if the cost was infinite reset back to 999
    }
    if (changed) {
        shotgunlayer2(rcvdpkt->destid, dt3.costs, nodeToShortestPath);
    }
    printdt3(&dt3);
}



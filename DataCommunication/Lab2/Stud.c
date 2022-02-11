/********* STUDENTS WRITE THE NEXT SEVEN ROUTINES *********/

#include "Stud.h"
#include <string.h>

int ASeqnum;
int Aacknum;


/********* HELPER FUCTIONS START HERE *********/
struct pkt make_pkt(struct msg message) {
    struct pkt temp = {ASeqnum, Aacknum, 0};
    strcpy(temp.payload, message.data);
    return temp;
}
/********* HELPER FUCTIONS END HERE *********/



/* called from layer 5, passed the data to be sent to other side */
void A_output(struct msg message) {
    struct pkt sndpkt = make_pkt(message);
    tolayer3(A, sndpkt);
}

/* need be completed only for extra credit */
void B_output(struct msg message) {

}

/* called from layer 3, when a packet arrives for layer 4 */
void A_input(struct pkt packet) {

}

/* called when A's timer goes off */
void A_timerinterrupt() {

}  

/* the following routine will be called once (only) before any other */
/* entity A routines are called. You can use it to do any initialization */
void A_init() {
    ASeqnum = 0;
    Aacknum = 0;
}

/* Note that with simplex transfer from a-to-B, there is no B_output() */

/* called from layer 3, when a packet arrives for layer 4 at B*/
void B_input(struct pkt packet) {
    printf("%s\n", packet.payload);
}

/* called when B's timer goes off */
void B_timerinterrupt() {

}

/* the following rouytine will be called once (only) before any other */
/* entity B routines are called. You can use it to do any initialization */
void B_init() {

}

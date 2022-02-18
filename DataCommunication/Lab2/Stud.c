/********* STUDENTS WRITE THE NEXT SEVEN ROUTINES *********/

#include "Stud.h"
#include <string.h>
#include <math.h>

//A
int Aseqnum;
int Aacknum;
struct pkt Asendpacket;

//B
int Backnum;
int Bseqnum;

int PASSEDPACKETS; //Debug
/********* HELPER FUCTIONS START HERE *********/
int make_checksum(struct pkt packet) {
    int sum = 0;
    for (int i = 0; i < 20; i++) {
        sum += (2 * (i+1)) * (int)packet.payload[i];
    }
    return sum + packet.seqnum + packet.acknum;
}

struct pkt make_pkt(struct msg message, int acknum, int seqnum) {
    struct pkt temp = {seqnum, acknum, 0};
    strcpy(temp.payload, message.data);
    temp.checksum = make_checksum(temp);
    return temp;
}

struct msg make_msg(struct pkt packet) {
    struct msg temp = {""};
    strcpy(temp.data, packet.payload);
    return temp;
}

int is_packet_corrupt(struct pkt packet, int seqnum){
    if(packet.checksum != make_checksum(packet)){
        return 1;
    } 
    return 0; 
}

int is_ACK(struct pkt packet, int acknum) {
    if (packet.acknum == acknum) {
        return 1;
    }
    return 0;
}

/********* HELPER FUCTIONS END HERE *********/



/* called from layer 5, passed the data to be sent to other side */
void A_output(struct msg message) {
    Asendpacket = make_pkt(message, Aacknum, Aseqnum);
    Aseqnum++;
    Aacknum = (Aacknum + 1) % 2;
    starttimer(A, 25);
    tolayer3(A, Asendpacket);
}

/* need be completed only for extra credit */
void B_output(struct msg message) {
    //Not to be implemented according to the lab spec.
}

/* called from layer 3, when a packet arrives for layer 4 */
void A_input(struct pkt packet) {
    if (is_packet_corrupt(packet, Aseqnum-1) || !is_ACK(packet, ((Aacknum % 2 == 0) ? 1 : 0))) {
        return;
    }
    stoptimer(A);
}

/* called when A's timer goes off */
void A_timerinterrupt() {
    Aseqnum--;
    Aacknum = ((Aacknum % 2 == 0) ? 1 : 0);
    struct msg temp = make_msg(Asendpacket);
    A_output(temp);
}

/* the following routine will be called once (only) before any other */
/* entity A routines are called. You can use it to do any initialization */
void A_init() {
    Aseqnum = 0;
    Aacknum = 0;
}

/* Note that with simplex transfer from a-to-B, there is no B_output() */

/* called from layer 3, when a packet arrives for layer 4 at B*/
void B_input(struct pkt packet) {    
    if (is_packet_corrupt(packet, Bseqnum)) {  //If packet corrupt return;
        return;  //makes timout trigger for A resending the same packet.
    }
    if (packet.seqnum < Bseqnum) { //ACKnum is incorrect
        struct msg temp = {"ACK"};
        tolayer3(B, make_pkt(temp, ((Backnum % 2 == 0) ? 1 : 0), Bseqnum-1));
        return;
    } else { //If packet not corrupt and ACKnum is correct
        tolayer5(B, packet.payload);
        PASSEDPACKETS++;
        printf("Passed packets: %d\n", PASSEDPACKETS);
        struct msg temp = {"ACK"};
        tolayer3(B, make_pkt(temp, Backnum, Bseqnum));
        Bseqnum++;
        Backnum = (Backnum + 1) % 2;
        // send packet to stop timer
    }
}

/* called when B's timer goes off */
void B_timerinterrupt() {
    //Not to be implemented according to the lab spec.
}

/* the following rouytine will be called once (only) before any other */
/* entity B routines are called. You can use it to do any initialization */
void B_init() {
    Backnum = 0;
    Bseqnum = 0;
    PASSEDPACKETS = 0; //Debug
}

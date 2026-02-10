#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>

#define WS 4
#define TF 10

typedef struct {
    int frame_id;
    bool sent;
    bool ack;
} Frame;

Frame buffer[WS];

void send_frame(Frame *frame);
bool receive_ack(Frame *frame);

int main() {
    int base = 0;
    int acknowledged = 0;

    printf("Sliding Window Protocol Simulation\n");
    printf("Total frames: %d\n\n", TF);

    while (acknowledged < TF) {

        // Fill window
        for (int i = 0; i < WS; i++) {
            if (base + i < TF && !buffer[i].sent) {
                buffer[i].frame_id = base + i;
                buffer[i].sent = false;
                buffer[i].ack = false;
            }
        }

        // Send frames
        for (int i = 0; i < WS; i++) {
            if (!buffer[i].sent && buffer[i].frame_id < TF) {
                printf("Sending frame %d\n", buffer[i].frame_id);
                send_frame(&buffer[i]);
                buffer[i].sent = true;
            }
        }

        // Receive acknowledgements
        for (int i = 0; i < WS; i++) {
            if (buffer[i].sent && !buffer[i].ack) {
                if (receive_ack(&buffer[i])) {
                    printf("Acknowledged frame %d\n", buffer[i].frame_id);
                    buffer[i].ack = true;
                    acknowledged++;
                } else {
                    printf("Frame %d lost, retransmitting from frame %d\n",
                           buffer[i].frame_id, base);

                    for (int j = 0; j < WS; j++) {
                        buffer[j].sent = false;
                        buffer[j].ack = false;
                    }
                    break;
                }
            }
        }

        // Slide window
        while (buffer[0].ack) {
            for (int i = 1; i < WS; i++) {
                buffer[i - 1] = buffer[i];
            }
            buffer[WS - 1].sent = false;
            buffer[WS - 1].ack = false;
            base++;
        }

        printf("\n");
    }

    printf("All frames sent and acknowledged successfully\n");
    return 0;
}

void send_frame(Frame *frame) {
    // Simulation only
}

bool receive_ack(Frame *frame) {
    return rand() % 10 >= 1;  // 90% success
}

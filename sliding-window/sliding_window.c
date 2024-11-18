#include <stdio.h>

#define MAX_FRAMES 100

int main()
{
    int window_size, frames;
    int frame_array[MAX_FRAMES];

    // Input window size
    printf("Enter window size: ");
    scanf("%d", &window_size);

    // Input number of frames
    printf("Enter number of frames to transmit: ");
    scanf("%d", &frames);

    // Input the frames
    printf("Enter %d frames: ", frames);
    for (int i = 0; i < frames; i++)
    {
        scanf("%d", &frame_array[i]);
    }

    printf("In sliding window protocol frames are sent in following way (assuming no corruption of frames).\n");
    printf("After sending %d frames at each stage sender waits for acknowledgement sent by the receiver\n\n", window_size);

    // Process frames in windows
    for (int i = 0; i < frames; i += window_size)
    {
        // Print current window frames
        for (int j = 0; j < window_size && i + j < frames; j++)
        {
            printf("%d    ", frame_array[i + j]);
        }
        printf("=> Acknowledgement of above frames sent is received by sender\n\n");
    }

    return 0;
}

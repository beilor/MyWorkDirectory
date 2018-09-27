#include <cstdio>
#include <linux/input.h>
#include <fcntl.h>
#include <cstring>
#include <unistd.h>
#include <errno.h>

int main(void)
{
    int fdMouse = open("/dev/input/event4", O_RDONLY);
    if (fdMouse <= 0) {
        printf("open device error\n");
        printf("Message : %s\n", strerror(errno));
        return 0;
    }

    struct input_event eventMouse;
    memset(&eventMouse, '0', sizeof(eventMouse));
    while (1) {
        unsigned int readSize = read(fdMouse, &eventMouse, sizeof(eventMouse));
        if (readSize != sizeof(eventMouse)) {
            printf("read device error\n");
            return 0;
        }
        if (eventMouse.type == EV_REL) {
            if (eventMouse.code == REL_WHEEL) {
                printf("mouse wheel is slid,value is: %d\n", eventMouse.value);
            }
            if (REL_X == eventMouse.code) {
                printf("the mouse in X axes by %d\n", eventMouse.value);
            }
            if (REL_Y == eventMouse.code) {
                printf("the mouse in Y axes by %d\n", eventMouse.value);
            }
        }
        else if (EV_KEY == eventMouse.type) {
                if (BTN_LEFT == eventMouse.code) {
                    if (1 == eventMouse.value) {
                        printf("left mouse key is down\n");
                    }
                    else {
                    printf("left mouse key is release\n");
                    }
                }
                if (BTN_RIGHT == eventMouse.code) {
                    if (1 == eventMouse.value) {
                        printf("right mouse key is down\n");
                    }
                    else {
                        printf("right mouse key is release\n");
                    }
                }
                if (BTN_MIDDLE == eventMouse.code) {
                    if (1 == eventMouse.value) {
                        printf("middle mouse key is down\n");
                    }
                    else {
                        printf("middle mouse key is release\n");
                    }
                }
        }
        else if (EV_SYN == eventMouse.type) {
            if (0 == eventMouse.code) {
                if (0 == eventMouse.value) {
                    printf("sync\n");
                }
            }
            else {
                printf("other know sync,the code is: %d, the value is: %d\n", eventMouse.code, eventMouse.value);
            }
        }
        else {
        printf("tpye is: %d, code is: %d, value is: %d\n",eventMouse.type, eventMouse.code, eventMouse.value);
        }
    }
}
#include <stdio.h>

int main(int argc, char **argv) {
    if(argc == 1) {
        printf("This is simple range generator. Run with 1, 2 or 3 parameters\n");
        return 0;
    }

    int start = 0, end = 0, step = 1;

    switch (argc) {
    case 1:
        printf("This is simple range generator. Run with 1, 2 or 3 parameters\n");
        return 0;
    case 2:
        sscanf(argv[1], "%d", &end);
        break;
    case 3:
        sscanf(argv[1], "%d", &start);
        sscanf(argv[2], "%d", &end);
        break;
    case 4:
        sscanf(argv[1], "%d", &start);
        sscanf(argv[2], "%d", &end);
        sscanf(argv[3], "%d", &step);
        break;
    default:
        break;
    }

    int i = start - step;
    
    while(i + step < end) {
        i += step;

        printf("%d\n", i);
        printf("--------\n");
    }

    return 0;
}
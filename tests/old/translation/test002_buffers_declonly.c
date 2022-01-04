#include <stdio.h>

extern inline int cynth_imod (int i, int n);

enum {
    cynth_uu_buff_size = 4
};
struct {
    float data [cynth_uu_buff_size];
    int pos;
} cynth_u_buff = {
    .data = {0},
    .pos  = 0
};

enum {
    cynth_uu_main_size = 32
};
struct {
    float data [cynth_uu_main_size];
    int pos;
} cynth_u_main = {
    .data = {0},
    .pos  = 0
};

extern inline float cynth_u_f (int u_x);

extern inline float cynth_uu_0 (int u_t);

extern inline float cynth_uu_1 (void);

int main (void) {

    int stop = 0;
    int iter = 0;
    int max  = 1000;

    int time = 0;

    while (!stop && iter <= max) {

        // Write:
        cynth_u_buff.data[(cynth_u_buff.pos + 1) % cynth_uu_buff_size] = cynth_uu_0(time);
        cynth_u_main.data[(cynth_u_main.pos + 1) % cynth_uu_main_size] = cynth_uu_1();

        // Step forward:
        cynth_u_buff.pos = (cynth_u_buff.pos + 1) % cynth_uu_buff_size;
        cynth_u_main.pos = (cynth_u_main.pos + 1) % cynth_uu_main_size;

        ++time;
        ++iter;

    }

    // Debug:
    printf("Buffer `buff` stopped at %i.\n", cynth_u_buff.pos);
    for (int i = 0; i < cynth_uu_buff_size; ++i) {
        printf("%f\n", cynth_u_buff.data[i]);
    }
    printf("Output buffer `main` stopped at %i.\n", cynth_u_main.pos);
    for (int i = 0; i < cynth_uu_main_size; ++i) {
        printf("%f\n", cynth_u_main.data[i]);
    }

    return 0;

}

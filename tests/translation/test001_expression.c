#include <stdio.h>

float cynth_fmod (float, float); // TODO: Implementation.

int main (void) {

    float uu_0 = cynth_fmod (
        ((float) (
            ((float) (
                ((int) (
                    1
                )) +
                ((int) (
                    2
                ))
            )) *
            ((float) (
                3.0
            ))
        )),
        ((float) (
            ((int) (
                2
            ))
        ))
    );

    printf("%f", uu_0);

}

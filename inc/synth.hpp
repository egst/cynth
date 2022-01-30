#pragma once

/**
 *  This header declares the public interface of the generated synth programs.
 */

extern "C" {

    void cth_init ();
    int  cth_run  (int time);

    // TODO: The output types should be taken from config.
    float * cth_output_buffer (char const * name);
    bool  * cth_input_bool    (char const * name);
    int   * cth_input_int     (char const * name);
    float * cth_input_float   (char const * name);

}

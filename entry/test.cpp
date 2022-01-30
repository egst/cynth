#include <concepts>

#include "asiosys.h"
#include "asio.h"

static_assert(std::same_as<ASIOError, long>);
//static_assert(std::same_as<ASIOSampleRate, double>);

int main () {

    ASIOSampleRate sr;
    ASIOGetSampleRate(nullptr);
    ASIOSetSampleRate(sr);

}

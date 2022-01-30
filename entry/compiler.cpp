#include <iostream>
#include <tuple>

// Note: Support for the C++20 <numbers> library is missing from many compilers,
// so I'll just use the macros for now.
//#include <numbers>
#define _USE_MATH_DEFINES
#include <cmath>

#include "esl/string.hpp"
//#include "esl/lift.hpp"
//#include "esl/sugar.hpp"

#include "context/all.hpp"
#include "interface/all.hpp"
#include "sem/all.hpp"
#include "syn/all.hpp"
#include "config.hpp"
#include "parser.hpp"

// TMP
#include "debug.hpp"

int main () {

    constexpr bool debug = false;

    using namespace cynth;
    //using namespace esl::sugar;
    //namespace target = esl::target;

    syn::node::Block root;

    // TODO: Use a dedicated struct as the parser argument.
    bool parseSuccess = false;
    yy::parser parse{std::pair<cynth::syn::node::Block &, bool &>{root, parseSuccess}};
    parse();

    if (!parseSuccess) return 1;

    if constexpr (debug) {
        auto recreated = esl::pretty(interface::display(root));
        std::cout << "recreated input:\n" << recreated << "\n\n";
    }

    context::Global    globalCtx;
    context::Function  functionCtx;
    context::Branching branchingCtx;
    context::Main ctx = {globalCtx, functionCtx, branchingCtx};

    // Built-in types:
    ctx.lookup.insertType("Bool",   {sem::type::Bool{}});
    ctx.lookup.insertType("Int",    {sem::type::Int{}});
    ctx.lookup.insertType("Float",  {sem::type::Float{}});
    ctx.lookup.insertType("String", {sem::type::String{}});

    // Built-in constants:
    ctx.lookup.insertValue(
        "srate",
        // TODO: I should probably stick with sampleRate in Hz (not kHz) everywhere to avoid confusion.
        {sem::Variable{sem::CompleteValue{sem::value::Float{static_cast<sem::Floating>(sampleRate * 1000)}}}}
    );
    ctx.lookup.insertValue(
        "pi",
        {sem::Variable{sem::CompleteValue{sem::value::Float{static_cast<sem::Floating>(M_PI)}}}}
    );
    ctx.lookup.insertValue(
        "e",
        {sem::Variable{sem::CompleteValue{sem::value::Float{static_cast<sem::Floating>(M_E)}}}}
    );
    auto noteValues = {
        sem::CompleteValue{sem::value::Float{32.7}},
        sem::CompleteValue{sem::value::Float{32.65}},
        sem::CompleteValue{sem::value::Float{36.71}},
        sem::CompleteValue{sem::value::Float{38.89}},
        sem::CompleteValue{sem::value::Float{41.20}},
        sem::CompleteValue{sem::value::Float{43.65}},
        sem::CompleteValue{sem::value::Float{46.25}},
        sem::CompleteValue{sem::value::Float{49.0}},
        sem::CompleteValue{sem::value::Float{51.91}},
        sem::CompleteValue{sem::value::Float{55.0}},
        sem::CompleteValue{sem::value::Float{58.27}},
        sem::CompleteValue{sem::value::Float{61.74}}
    };
    auto noteAlloc = sem::ArrayAllocation{esl::make_component_vector(noteValues)};
    ctx.lookup.insertValue(
        "notes",
        {sem::Variable{sem::CompleteValue{sem::value::Array{
            .allocation = &noteAlloc,
            .valueType  = sem::type::Array{sem::CompleteType{sem::type::Float{true}}, 12, true}
        }}}}
    );
    //constexpr std::array<float,        13> frequencies = {32.7, 32.65, 36.71, 38.89, 41.20, 43.65, 46.25, 49.0, 51.91, 55.0, 58.27, 61.74, 65.41};

    // Built-in operations:
    ctx.global.insertFunction(sem::runtime::definition::floor());
    ctx.global.insertFunction(sem::runtime::definition::idiv());
    ctx.global.insertFunction(sem::runtime::definition::imod());
    ctx.global.insertFunction(sem::runtime::definition::fmod());

    // Internal library dependencies:
    ctx.global.insertInclude(c::inclusion("<math.h>"));
    ctx.global.insertInclude(c::inclusion("<stdbool.h>"));
    ctx.global.insertInclude(c::inclusion("<stddef.h>"));
    ctx.global.insertInclude(c::inclusion("<string.h>"));
    // Debug: (TODO: Only use these in debug mode.)
    ctx.global.insertInclude(c::inclusion("<stdio.h>"));
    ctx.global.insertInclude(c::inclusion("<signal.h>"));
    ctx.global.insertInclude(c::inclusion("<time.h>"));
    if constexpr (platform == Platform::windows)
        ctx.global.insertInclude(c::inclusion("<windows.h>"));
    else
        ctx.global.insertInclude(c::inclusion("<unistd.h>"));

    // Internal type definitions:
    ctx.global.insertType(c::statement(c::emptyTypeDefinition()));

    auto result = root.processProgram(ctx);

    if (!result) {
        std::cerr << "compilation error:" << result.error().message << '\n';
        return 1;
    }

    auto processed = *result;

    auto generated = ctx.assemble();

    if constexpr (debug)
        std::cout << "generated program:\n";

    std::cout << generated << '\n';

    return 0;

}

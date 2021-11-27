#pragma once

/**
 *  This is the only file "exporting" macros.
 *  All other files undef any locally defined macros.
 *  This file only provides macros, no actual C++ declarations.
 *  Headers for the underlying C++ declarations must be included manually.
 */

#define ESL_INSPECT(val) esl::inspector<decltype(val)>{}
#define ESL_INSPECT_TYPE(type) esl::inspector<type>{}

#pragma once

#if defined(ON_WINDOWS)
#if defined(GLOVE_EXPORTS)
#define GLOVE_API_EXPORT __declspec(dllexport)
#else
#define GLOVE_API_EXPORT __declspec(dllimport)
#endif // defined(GLOVE_EXPORTS)
#else
#define GLOVE_API_EXPORT
#endif
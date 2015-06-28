#pragma once

#if defined(ON_WINDOWS)
#if defined(BD_EXPORTS)
#define BD_API_EXPORT __declspec(dllexport)
#else
#define BD_API_EXPORT __declspec(dllimport)
#endif // defined(BD_EXPORTS)
#else
#define BD_API_EXPORT
#endif
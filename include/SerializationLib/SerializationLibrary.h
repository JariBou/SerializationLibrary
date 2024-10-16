#pragma once

#ifdef SERIAL_COMPILE
#define SERIAL_API __declspec( dllexport )
#else
#define SERIAL_API __declspec( dllimport )
#endif

#pragma once

#include <cassert>
#include <cstdint>
#include <cstdlib>
#include <fmt/core.h>
// #include <spdlog/spdlog.h>

using s8 = int8_t;
using s16 = int16_t;
using s32 = int32_t;
using s64 = int64_t;
using s128 = __int128;

using u8 = uint8_t;
using u16 = uint16_t;
using u32 = uint32_t;
using u64 = uint64_t;
using u128 = unsigned __int128;

using uchar = unsigned char;   // NOLINT(google-runtime-int)
using ushort = unsigned short; // NOLINT(google-runtime-int)
using uint = unsigned int;     // NOLINT(google-runtime-int)

static_assert(sizeof(float) == 4);
using r32 = float;
static_assert(sizeof(double) == 8);
using r64 = double;
static_assert(sizeof(long double) == 16);
using r128 = long double;

/*!
    \file Timestamp.cpp
    \brief Implementation of the Timestamp class.
 
    Copyright (c) 2004-2006, Applied Informatics Software Engineering GmbH.
    and Contributors.
    
    Permission is hereby granted, free of charge, to any person or organization
    obtaining a copy of the software and accompanying documentation covered by
    this license (the "Software") to use, reproduce, display, distribute,
    execute, and transmit the Software, and to prepare derivative works of the
    Software, and to permit third-parties to whom the Software is furnished to
    do so, all subject to the following:
    
    The copyright notices in the Software and this entire statement, including
    the above license grant, this restriction and the following disclaimer,
    must be included in all copies of the Software, in whole or in part, and
    all derivative works of the Software, unless such copies or derivative
    works are solely in the form of machine-executable object code generated by
    a source language processor.
    
    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT
    SHALL THE COPYRIGHT HOLDERS OR ANYONE DISTRIBUTING THE SOFTWARE BE LIABLE
    FOR ANY DAMAGES OR OTHER LIABILITY, WHETHER IN CONTRACT, TORT OR OTHERWISE,
    ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
    DEALINGS IN THE SOFTWARE.
*/
#if HAVE_CONFIG_H
#  include <config.h>
#endif // HAVE_CONFIG_H

#include "Timestamp.h"
#include <algorithm>
#include <iostream>
#if defined(_WIN32)
#include <windows.h>
#else
#include <unistd.h>
#include <sys/time.h>
#include <sys/times.h>
#endif


namespace Platform
{

Timestamp::Timestamp()
{
    update();
}


Timestamp::Timestamp(TimeVal tv)
{
    _ts = tv;
}


Timestamp::Timestamp(const Timestamp& other)
{
    _ts = other._ts;
}


Timestamp::~Timestamp()
{
    // empty
}


Timestamp&
Timestamp::operator = (const Timestamp& other)
{
    _ts = other._ts;
    return *this;
}


Timestamp&
Timestamp::operator = (TimeVal tv)
{
    _ts = tv;
    return *this;
}


void
Timestamp::swap(Timestamp& timestamp)
{
    std::swap(_ts, timestamp._ts);
}


Timestamp
Timestamp::fromEpochTime(time_t t)
{
    return Timestamp(TimeVal(t)*resolution());
}


Timestamp
Timestamp::fromUtcTime(UtcTimeVal val)
{
    val -= (TimeDiff(0x01b21dd2) << 32) + 0x13814000;
    val /= 10;
    return Timestamp(val);
}


void
Timestamp::update()
{
#if defined(_WIN32)

    FILETIME ft;
    GetSystemTimeAsFileTime(&ft);
     // UNIX epoch (1970-01-01 00:00:00) expressed in Windows NT FILETIME
    ULARGE_INTEGER epoch;
    epoch.LowPart  = 0xD53E8000;
    epoch.HighPart = 0x019DB1DE;

    ULARGE_INTEGER ts;
    ts.LowPart  = ft.dwLowDateTime;
    ts.HighPart = ft.dwHighDateTime;
    ts.QuadPart -= epoch.QuadPart;
    _ts = ts.QuadPart/10;

#else

    struct timeval tv;
    if (gettimeofday(&tv, NULL))
    {
        std::cout << "Error updating Timestamp. Cannot get time of day." << std::endl;
        exit(1);
    }
    _ts = TimeVal(tv.tv_sec)*resolution() + tv.tv_usec;

#endif
}


#if defined(_WIN32)


Timestamp
Timestamp::fromFileTimeNP(UInt32 fileTimeLow, UInt32 fileTimeHigh)
{
    ULARGE_INTEGER epoch; // UNIX epoch (1970-01-01 00:00:00) expressed in Windows NT FILETIME
    epoch.LowPart  = 0xD53E8000;
    epoch.HighPart = 0x019DB1DE;

    ULARGE_INTEGER ts;
    ts.LowPart  = fileTimeLow;
    ts.HighPart = fileTimeHigh;
    ts.QuadPart -= epoch.QuadPart;

    return Timestamp(ts.QuadPart/10);
}


void
Timestamp::toFileTimeNP(UInt32& fileTimeLow, UInt32& fileTimeHigh) const
{
    ULARGE_INTEGER epoch; // UNIX epoch (1970-01-01 00:00:00) expressed in Windows NT FILETIME
    epoch.LowPart  = 0xD53E8000;
    epoch.HighPart = 0x019DB1DE;

    ULARGE_INTEGER ts;
    ts.QuadPart  = _ts*10;
    ts.QuadPart += epoch.QuadPart;
    fileTimeLow  = ts.LowPart;
    fileTimeHigh = ts.HighPart;
}

#endif

} // namespace Platform
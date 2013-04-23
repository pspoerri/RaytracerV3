/*!
    \file Stopwatch.h
    \brief Definition of the Stopwatch class.
 
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
#ifndef PLATFORM_STOPWATCH_H_INCLUDED
#define PLATFORM_STOPWATCH_H_INCLUDED

#include "Timestamp.h"

namespace Platform
{

//! A simple facility to measure time intervals with microsecond resolution.
class Stopwatch
{
public:
    Stopwatch();
    ~Stopwatch();

    //! Starts (or resumes) the stopwatch.
    void start() {_start.update(); _cpuStart = clock(); _running = true;}

    //! Stops or pauses the stopwatch.
    void stop();

    //! Resets the stopwatch.
    void reset();

    //! Resets and starts the stopwatch.
    void restart();

    //! Returns the elapsed time in microseconds since the stopwatch started.
    Timestamp::TimeDiff elapsed() const;

    //! Returns the amount of CPU miscroseconds used since the stopwatch started.
    Timestamp::TimeDiff cpu() const;

    //! Returns the number of seconds elapsed since the stopwatch started.
    double elapsedSeconds() const {return elapsed()/double(resolution());}

    //! Returns the amount of CPU seconds used since the stopwatch started.
    double cpuSeconds() const {return cpu()/double(resolution());}

    //! Returns the resolution of the stopwatch.
    static Timestamp::TimeVal resolution() {return Timestamp::resolution();}

private:
    Stopwatch(const Stopwatch&);            // Not implementated
    Stopwatch& operator=(const Stopwatch&); // Not implementated

    Timestamp           _start;
    Timestamp::TimeDiff _elapsed;
    clock_t             _cpuStart;
    Timestamp::TimeDiff _cpuTotal;
    bool                _running;
};

} // namespace Platform

#endif // PLATFORM_STOPWATCH_H_INCLUDED

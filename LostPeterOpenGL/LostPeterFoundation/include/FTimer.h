/****************************************************************************
* LostPeterFoundation - Copyright (C) 2022 by LostPeter
* 
* Author:   LostPeter
* Time:     2023-06-03
* Github:   https://github.com/LostPeter/LostPeterOpenGL
* Document: https://www.zhihu.com/people/lostpeter/posts
*
* This code is licensed under the MIT license (MIT) (http://opensource.org/licenses/MIT)
****************************************************************************/

#ifndef _F_TIMER_H_
#define _F_TIMER_H_

#include "FPreDefine.h"

namespace LostPeterFoundation
{
    class foundationExport FTimer
    {
    public:
        FTimer();
        ~FTimer();

    public:
    protected:
        TimePoint m_tpStart;
        TimePoint m_tpLast;

    public:
        F_FORCEINLINE const TimePoint& GetTimePointStart() const { return m_tpStart; }
        F_FORCEINLINE const TimePoint& GetTimePointLast() const { return m_tpLast; }

    public:
        void Reset();
        
        TimePoint Now();
        float SecondsBetween(TimePoint& a, TimePoint& b);

        float GetTimeSinceStart();
        float GetTimeDelta();

        void Tick();
    };

}; //LostPeterFoundation

#endif
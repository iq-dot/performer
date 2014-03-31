#ifndef PSTDDEVIATION_H
#define PSTDDEVIATION_H

#include <performer/analysis/pfunctor.h>

/**
*This PerformerFunctor is for calculating standard deviations
*NOTE: This PerformerFunctor relies on the frameworks Paverage PerformerFunctor to have been already executed, generally the analyzer component should
*be responsible for taking care of this
*/
class PstdDeviation : public PerformerFunctor
{
    public:
        PstdDeviation(result_category *rc);
        virtual ~PstdDeviation();

        void operator()(const SpeedInfo&);
        void operator()(const MemInfo&);

    private:
        double spd_nsize;
        double mem_nsize;

        double sumWallTime;
        double sumCpuTime;
        double sumUsrTime;
        double sumSysTime;

        double sumVsSize;
        double sumRsSize;
        double sumRefMem;
        double sumSwapMem;

        double sumCleanMem;
        double sumDirtyMem;

        double sumPrivateMem;
        double sumPrivateCleanMem;
        double sumPrivateDirtyMem;

        double sumSharedMem;
        double sumSharedCleanMem;
        double sumSharedDirtyMem;

        double sumStackSize;
        double sumStackRss;
        double sumStackRef;
        double sumStackClean;
        double sumStackDirty;

        double sumHeapSize;
        double sumHeapRss;
        double sumHeapRef;
        double sumHeapClean;
        double sumHeapDirty;

        double sumVmData;
        double sumVmExe;
        double sumVmLib;
        double sumVmPTE;

        double sumPagefaults;
};

#endif // PSTDDEVIATION_H

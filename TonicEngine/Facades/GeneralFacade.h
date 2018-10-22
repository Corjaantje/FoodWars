#ifndef PROJECT_SWA_GENERALFACADE_H
#define PROJECT_SWA_GENERALFACADE_H

#include "IFacade.h"

class GeneralFacade : public IFacade {
public:
    GeneralFacade();
    ~GeneralFacade();
    void sleep(int millis) const;
};

#endif //PROJECT_SWA_GENERALFACADE_H

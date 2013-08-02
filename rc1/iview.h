#ifndef IVIEW_H
#define IVIEW_H

#include "storage.h"
#include "conf/layoutmodel.h"

class IView
{
public:
    virtual ~IView() {}
    virtual Storage *getStorage()=0;
    virtual LayoutModel *getLayout()=0;
};

#endif // IVIEW_H

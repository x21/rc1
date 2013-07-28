#include <QDebug>
#include "layoutmodel.h"

LayoutModel::LayoutModel()
{
    nrows=2;

    nseg = new int[nrows];
    nseg[0] = 5;
    nseg[1] = 7;

    rowheight = new int[nrows];
    rowheightpx = new int[nrows];
    rowheight[0] = 4;
    rowheight[1] = 4;
    rowheightmax=8;

    segwidth = new int[12];
    segwidthpx = new int[12];
    setAll(12,segwidth,1);

    segwidthmax=new int[2];
    segwidthmax[0]= 5;
    segwidthmax[1]= 7;

    note = new int[12];
    note[0]=50;
    note[1]=51;
    note[2]=52;
    note[3]=53;
    note[4]=54;
    note[5]=55;
    note[6]=56;
    note[7]=57;
    note[8]=58;
    note[9]=59;
    note[10]=60;
    note[11]=61;

    ctlx=new int[12];
    setAll(12,ctlx,0);

    ctly=new int[12];
    setAll(12,ctly,0);

    calcGeo(200,200);
}

void LayoutModel::calcGeo(int w, int h)
{
    qDebug() << "Cacl geo " << w << " " << h;
    width=w;
    height=h;
    int i=0;
    int rowheightsum=0;
    for(int y=0;y<nrows;y++) {
        rowheightpx[y]=height*rowheight[y]/rowheightmax;
        rowheightsum+=rowheightpx[y];
        // additional pixels may occur due to rounding differences
        // -> add additional pixels to last row
        if(y==nrows-1 && rowheightsum<height) {
            rowheightpx[y]+=rowheightsum-height;
        }
        int segwidthsum=0;
        for(int x=0;x<nseg[y];x++) {
            segwidthpx[i]=width*segwidth[i]/segwidthmax[y];
            segwidthsum+=segwidthpx[i];
            // -> add additional pixels to last segment
            if(x==nseg[y]-1 && segwidthsum<width) {
                segwidthpx[i]+=segwidthsum-width;
            }
            i++;
        }
    }
}

int LayoutModel::getHeight() const
{
    return height;
}

int LayoutModel::getWidth() const
{
    return width;
}

int LayoutModel::getNrows() const
{
    return nrows;
}

int LayoutModel::getRowheightpx(int i) const
{
    return rowheightpx[i];
}

int LayoutModel::getNseg(int i) const
{
    return nseg[i];
}

void LayoutModel::setAll(int n, int *d, int v)
{
    for(int i=0;i<n;i++) {
        d[i]=v;
    }
}

int LayoutModel::getSegwidth(int i) const
{
    return segwidth[i];
}

int LayoutModel::getCtly(int i) const
{
    return ctly[i];
}

int LayoutModel::getCtlx(int i) const
{
    return ctlx[i];
}

int LayoutModel::getNote(int i) const
{
    return note[i];
}


int LayoutModel::getSegwidthpx(int i) const
{
    return segwidthpx[i];
}


int LayoutModel::getSegwidthmax(int i) const
{
    return segwidthmax[i];
}

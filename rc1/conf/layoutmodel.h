#ifndef LAYOUTMODEL_H
#define LAYOUTMODEL_H

class LayoutModel
{
public:
    LayoutModel();
    void calcGeo(int w, int h);

    int getWidth() const;
    int getHeight() const;

    int getNrows() const;

    int getRowheightpx(int i) const;
    int getNseg(int i) const;
    int getSegwidth(int i) const;
    int getSegwidthmax(int i) const;
    int getSegwidthpx(int i) const;
    int getNote(int i) const;
    int getCtlx(int i) const;
    int getCtly(int i) const;


private:
    int nrows;
    int *rowheight;
    int rowheightmax;
    int *rowheightpx;
    int *nseg;
    int *segwidth;
    int *segwidthmax;
    int *segwidthpx;
    int *note;
    int *ctlx;
    int *ctly;
    int width = 200;
    int height = 200;

    void setAll(int n, int * d, int v);

};

#endif // LAYOUTMODEL_H

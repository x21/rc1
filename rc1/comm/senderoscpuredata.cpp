#include "senderoscpuredata.h"
#include "comm/libofqf/qoscclient.h"

SenderOscPuredata::SenderOscPuredata(RC1 *rc1)
{
    oscout=new QOscClient(QHostAddress("255.255.255.255"),3333);
    oscout->setAddress(QHostAddress("255.255.255.255"),3333);
    notestate=new quint8[127];
    for(int i=0;i<127;i++) {
        notestate[i]=0;
    }
    prog=0;
    onNoteCnt=0;
    this->rc1=rc1;
}

void SenderOscPuredata::note(int c, int voiceId, int f, int vel)
{
    if(vel>0) {
        if(notestate[f]==0) {
            notestate[f]=vel;
            QVariantList v;
            v.append(f);
            v.append(vel);
            v.append(c);
            sendOsc("/note",v);
            onNoteCnt++;
            rc1->getEvstat()->incOscnoteoncount();
        } else {
            rc1->getEvstat()->incAlreadyoncount();
        }
    } else {
        notestate[f]=0;
        QVariantList v;
        v.append(f);
        v.append(0);
        v.append(c);
        sendOsc("/note",v);
        onNoteCnt--;
        rc1->getEvstat()->incOscnoteoffcount();
//  paranoia option, make sure it is really all off
//        if(onNoteCnt==0) sendOsc("/alloff",1);
    }
}

void SenderOscPuredata::pc(int c, int v1)
{
    QVariantList v;
    v.append(c);
    v.append(v1);
    sendOsc("/pc",v);
}

void SenderOscPuredata::cc(int c, int voiceId, int cc, double v1)
{
    // translate value to midi
    int v1mid=(double)127*v1;
    // translate cc numbers
    QVariantList v;
    v.append(cc);
    v.append(v1mid);
    v.append(c);
    sendOsc("/cc",v);
}

void SenderOscPuredata::sendOsc(QString path, QVariant list)
{
//    qDebug() << " sendOsc to " << path << " values " << list;
    oscout->sendData(path,list);
    rc1->getEvstat()->incOsccount();
}

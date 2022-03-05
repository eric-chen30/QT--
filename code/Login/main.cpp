#include <QtWidgets/QApplication>
#include "info.h"
#include "mainwindow.h"
#include "toregister.h"
#include "carregister.h"
#include "appointment.h"
#include "accepted.h"
#include "oncar.h"
#include "appinfo.h"
#include "instantcall.h"
#include "pay.h"
#include "evaluation.h"

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);


    info w;

    MainWindow dlg;

    toRegister rlg;

    carRegister rlg2;

    appointment appo;

    instantcall inst;

    accepted acce;

    oncar onc;

    appinfo appi;

    pay pay0;

    evaluation eval;

    QObject::connect(&dlg,SIGNAL(registersignal()),&rlg,SLOT(acceptedregister()));
    QObject::connect(&dlg,SIGNAL(loginsignal()),&w,SLOT(acceptLogin()));
    QObject::connect(&rlg,SIGNAL(registeredsignal()),&dlg,SLOT(acceptedlogin()));
    QObject::connect(&w,SIGNAL(registeredcarsignal()),&rlg2,SLOT(acceptrecargister()));
    QObject::connect(&rlg2,SIGNAL(registeredsignal2()),&w,SLOT(show()));
    QObject::connect(&w,SIGNAL(appointCall()),&appo,SLOT(acceptappointCall()));
    QObject::connect(&w,SIGNAL(instantCall()),&inst,SLOT(acceptInstantCall()));
    QObject::connect(&appo,SIGNAL(receiveSignal()),&acce,SLOT(acceptReceiveSignal()));
    QObject::connect(&appo,SIGNAL(waitingCar()),&appi,SLOT(acceptWaitingCar()));
    QObject::connect(&inst,SIGNAL(receiveSignal2()),&acce,SLOT(acceptReceiveSignal2()));
    QObject::connect(&inst,SIGNAL(waitingCar2()),&appi,SLOT(acceptWaitingCar2()));
    QObject::connect(&acce,SIGNAL(getOnCar()),&onc,SLOT(acceptgetOnCar()));
    QObject::connect(&acce,SIGNAL(currentPlace()),&onc,SLOT(acceptCurrentPlace()));
    QObject::connect(&onc,SIGNAL(closeAppinfo()),&appi,SLOT(close()));
    QObject::connect(&acce,SIGNAL(paySingal()),&onc,SLOT(close()));
    QObject::connect(&acce,SIGNAL(paySingal()),&pay0,SLOT(acceptPaySingal()));
    QObject::connect(&pay0,SIGNAL(evaluationSignal()),&eval,SLOT(acceptEvaluationSignal()));

    dlg.show();
    return a.exec();


}


#include <iostream>
#include <iomanip>
#include<covid/node.h>
#include <covid/connectionSI.h>
#include <covid/connectionLinear.h>


using namespace std;
using namespace covid;

int main() {
    std::cout << "Simulator Covid started" << std::endl;
    const int N = 10; // numero giorni di previsione del modello


    double I0 = 0.00092e-2, D0=0.00030e-2, A0=0.00016e-2, R0=0.00014e-2,
            T0=0.00001e-2, H0=0.00009e-2, E0=0.00000;
    double S0 = 1.0 - I0 - D0 - A0 - R0 - T0 - H0 - E0;

    double alpha = 0.570, beta = 0.011, delta = 0.011, gamma = 0.456,
    epsilon = 0.171, theta = 0.371, zeta = 0.125, eta = 0.125,
    mu = 0.012, nu = 0.027, tau = 0.003, lambda = 0.034, rho = 0.034,
    kappa = 0.017, xi = 0.017, sigma = 0.017;

    //creo gli 8 nodi del modello SIDARTHE

    node S("S", S0);
    node I("I", I0);
    node D("D", D0);
    node A("A", A0);
    node R("R", R0);
    node T("T", T0);
    node H("H", H0);
    node E("E", E0);

    //LISTA DI NODES (PUNTATORI)
    vector<node*> nodes;
    nodes.push_back(&S);
    nodes.push_back(&I);
    nodes.push_back(&D);
    nodes.push_back(&A);
    nodes.push_back(&R);
    nodes.push_back(&T);
    nodes.push_back(&H);
    nodes.push_back(&E);

    //solo per la connessione SI (parametri per calcolo flusso)
    vector<nodeParam> nodeParams;
    nodeParams.push_back(nodeParam(&I, alpha));
    nodeParams.push_back(nodeParam(&D, beta));
    nodeParams.push_back(nodeParam(&A, gamma));
    nodeParams.push_back(nodeParam(&R, delta));

    //controller PD(parametri costruttore controllerPD);
    //controller PD = new controllerPD(paramCostruttore);

    connectionSI SI(&S, &I, nodeParams, "SI"); // connessione + complessa
    connectionLinear ID(&I, &D, "ID", epsilon);

    vector<connection*> connectionList;
    connectionList.push_back(new connectionLinear( &I, &A, "IA", zeta));
    connectionList.push_back(new connectionLinear(&I, &H, "IH", lambda));
    connectionList.push_back(new connectionLinear(&D, &R, "DR", eta));
    connectionList.push_back(new connectionLinear(&D, &H, "DH", rho));
    connectionList.push_back(new connectionLinear(&A, &R, "AR", theta));
    connectionList.push_back(new connectionLinear(&A, &H, "AH", kappa));
    connectionList.push_back(new connectionLinear(&A, &T, "AT", mu));
    connectionList.push_back(new connectionLinear(&R, &T, "RT", nu));
    connectionList.push_back(new connectionLinear(&R, &H, "RH", xi));
    connectionList.push_back(new connectionLinear(&T, &H,"TH", sigma));
    connectionList.push_back(new connectionLinear(&T, &E, "TE", tau));
    connectionList.push_back(&SI);
    connectionList.push_back(&ID);


    const double dt = 1/10;
    for (int days = 0; days < N; ++days)
    {
        if(days == 4) // dopo il giorno numero 4
        {
            bool found = SI.updateCoeffSI("I", 0.422);
            found = found && SI.updateCoeffSI("D", 0.0057);
            found = found && SI.updateCoeffSI("A", 0.285);
            found = found && SI.updateCoeffSI("R", 0.0057);
            if(!found)
                std::cout << "Errore nella creazione dei nodi ne manca uno o piu' dei 4 necessari per connectionSI (I-D-A-R) ";
        }
        else if(days == 12) // dopo il giorno numero 12
        {
            if(!ID.updateCoeffLC(0.143))
                cout << "Errore nell'update dei parametri di connectionLinearID ";
        }

        //flusso non rimarrà costante per un intero giorno ma varierà e quindi dovremo calcolarlo più volto in un giorno
        for(int k = 0; k < 1.0/dt; ++k)
        {
            for (int i = 0; i < connectionList.size(); ++i)
                connectionList[i]->computeFlow(dt); // calcolo i flussi per tutti i nodi ad un
                                                    // dato intervallo temporale

            for (int i = 0; i < connectionList.size(); ++i) {
                connection *connectionI = connectionList[i];
                connectionI->getNodeSource()->transferTo(connectionI->getNodeDestination(), connectionI->getFlow());
            }
        }

        cout << setprecision(2) << std::fixed;
        for(int j = 0; j < nodes.size(); ++j) // stampa dei valori dello stato del nodo dopo days giorni
            cout << nodes[j]->getName() << " : " << nodes[j]->getValue() << " ";

        cout << endl;
    }


    std::cout << "Simulator Covid finished" << std::endl;
    return 0;
}

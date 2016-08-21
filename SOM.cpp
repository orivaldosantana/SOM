/* 
 * File:   SOM.cpp
 * Author: oriva
 * 
 * Created on 06 de Fevereiro de 2015, 15:21
 */
#include "SOM.h"
#include "utils.h"
#include <list>
#include <cmath>

SOM::SOM(int _sn) {
    sizeNetwork = _sn;
    learningRate = 0.2;
    minLearningRate = 0.01;
    alpha = learningRate; 
    maxIteration = 15000;
    maxEpoch = 200; 
    debug = true;
    currentIt = 0;
    epoch = 0;
    sigma = 1.5; 
    //maxIteration = 100000; 
    
    //initializeNodes(3); 
}

SOM::~SOM() {
    
}

// encontrar o vencedor 

void SOM::findWinner(Sample *s, int& iWin, int& jWin){ 
    iWin = 0;
    jWin = 0; 
    double bestD = nodes[0][0].distance(*s); 
    for (int i=0; i < sizeNetwork; i++){
        for (int j=0; j < sizeNetwork; j++ ){
            if (nodes[i][j].isEnabled()) {
                double d = nodes[i][j].distance(*s); 
                if (d < bestD){
                    bestD = d;
                    iWin = i;
                    jWin = j;
                }
            }
        }
    }
 
}

double SOM::distancePos(int aX, int aY, int bX, int bY){
    return sqrt( pow(aX - bX,2) + pow(aY - bY,2) ); 
}

//TODO esta função pode ser otimizada: o passo de pegar e compara em um laço apenas  
double SOM::compareRange(int x, int y, int iStart, int iEnd, std::vector<double>& info){
    std::vector<double> infoN; 
    nodes[x][y].getFeaturesRange(iStart,iEnd,infoN); 
    return distanceVector(info,infoN); 
}

double SOM::distanceVector(std::vector<double>& infoA, std::vector<double>& infoB){
    if (infoB.size() < infoA.size())
        return -1; 
    double sum = 0;
    for (int i=0; i < infoA.size(); i++){
        sum = sum + pow (infoA[i] - infoB[i],2);
    }
    return sqrt(sum); 
}


int SOM::validatePos(int pos){
    if (pos >= sizeNetwork)
        pos = sizeNetwork -1; 
    if (pos < 0)
        pos = 0; 
    return pos; 
}

int SOM::updateWeight(Sample *s, int iWin, int jWin) {



    /*
     *  // função de vizinhança = exp(abs(pwin - pneighbor)/sig*sig) )
     * tamanho máximo da vizinhaça = tamanho da rede dividido por 3
     */
    int jAnt = validatePos(jWin - sizeNetwork / 3);
    int jPost = validatePos(jWin + sizeNetwork / 3);
    int iAnt = validatePos(iWin - sizeNetwork / 3);
    int iPost = validatePos(iWin + sizeNetwork / 3);
    
//nodes[iWin][jWin].print();    
    double neighboorFunction;
    //double sigma = 1.3;    
    for (int i = iAnt; i <= iPost; i++) {
        for (int j = jAnt; j <= jPost; j++ ){
            // calcula a distância na grade entre o vencedor e um vizinho (i,j)            
            neighboorFunction = alpha * exp(-(distancePos(i,j,iWin,jWin) / (sigma * sigma))); 
            nodes[i][j].updateFeatures(neighboorFunction,s);
        }
    }
    nodes[iWin][jWin].setEnabled(false); 
//nodes[iWin][jWin].print();  
 

}

void SOM::printNodes() {
    
    std::stringstream ssFileName;
    
    ssFileName << "output/color_" << currentIt << ".txt"; 
    
    std::string sFileName = ssFileName.str(); 
    
    ofstream nodesFile;
    nodesFile.open (sFileName.c_str());
  
    for (int i = 0; i < sizeNetwork; i++) {
        for (int j = 0; j < sizeNetwork; j++) {
            cout << " [" <<  nodes[i][j].toString() << "] ";
            nodesFile << nodes[i][j].toString(); 
        }
        cout <<endl; 
        nodesFile << endl; 
    }
    nodesFile.close();

}

void SOM::setDataSet(DataSet* dataSet) {
    this->dataSet = dataSet;
}

void SOM::setSizeNetwork(int sizeNetwork) {
    this->sizeNetwork = sizeNetwork;
}

int SOM::getSizeNetwork() const {
    return sizeNetwork;
}

 
 
void SOM::execute(){
    if (!dataSet->isEmpty()) {
        epoch = 0;
        currentIt = 0;
        while ((epoch < maxEpoch) ){
            executeOneIt();                 
        }
    } else
        std::cout << " Data set is empty! " << std::endl;
    std::cout << "Epoch: " << epoch << std::endl; 
}
 

void SOM::executeOneIt() {
    
    // escolhe aleatoriamente um padrão de entrda para a rede 
    bool firstSample = dataSet->getRandomSample(currentSample);
    if (firstSample) {
        epoch++; 
        //enable all nodes of the network
        enableNodes(); 
        // update all rates 
        // update learning rate 
        alpha = learningRate * (double(maxEpoch - epoch) / double(maxEpoch));
        if (alpha < minLearningRate)
            alpha = minLearningRate;
                //update the gain G (sigma)
        sigma = (1 - 0.01) * sigma;
    }
    
    std::cout << "Sample: ";
    currentSample->print(); 
    std::cout << endl; 

    // encontra o vencedor    
    int iWinner, jWinner;
    findWinner(currentSample,iWinner,jWinner); 
 
    // atualiza os pesos
    updateWeight(currentSample,iWinner,jWinner); 
    
    if ((currentIt % 100000 == 0) && (debug))
        printNodes();
    currentIt++; 
    cout << "CurrentIt: " << currentIt << endl; 

}


void SOM::getNodeFeatures(int i, int j, std::vector<double>& info) {
    if ((i > sizeNetwork)||(j > sizeNetwork))
        return;
    //nodes[i][j].print(); 
    nodes[i][j].getFeatures(info); 
}
/**
 * Inicialization of SOM nodes 
 * @param sizeNodes amount of node features  
 * @param positivesValues allow only positive values for the node initial features 
 */
void SOM::initializeNodes(int sizeNodes, bool positivesValues, double intensity, double maxIntensity ){
    //srand(3); 
    double a;
    std::vector<double>  info; 
    // inicialização dos nodos da rede
    
    for (int i = 0; i < sizeNetwork; i++) {        
        for (int j = 0; j < sizeNetwork; j++) {
            info.clear(); 
            for (int l =0; l < sizeNodes; l++) {
                if (positivesValues)
                    a = (rand() % int(intensity))/maxIntensity ;            
                else
                    a = (rand() % int(intensity))/maxIntensity - (intensity/maxIntensity)/2.0;            
                info.push_back(a);
            }
            nodes[i][j].setLabel(Utils::int2string(i)+"-"+Utils::int2string(j));            
            nodes[i][j].setFeatures(info);             
        }
    }
}

void SOM::enableNodes(){
    for (int i = 0; i < sizeNetwork; i++) {        
        for (int j = 0; j < sizeNetwork; j++) {
            nodes[i][j].setEnabled(true); 
        }
    }
}

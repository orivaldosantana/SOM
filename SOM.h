/* 
 * File:   SOM.h
 * Author: oriva
 *
 * Created on 15 de Março de 2014, 12:21
 */

#ifndef SOM_H
#define	SOM_H
 
#include "Node.h"
#include "DataSet.h"

 
class SOM {
public:
    SOM();

    ~SOM();
 
    void findWinner(Sample *s, int &i, int &j); 
 
    void executeOneIt();
    void execute(); 
 
    double distancePos(int aX, int aY, int bX, int bY);
    double distanceVector(std::vector<double>  &infoA, std::vector<double>  &infoB);
    double compareRange(int x, int y, int iStart, int iEnd,  std::vector<double>  &info); 
    void enableNodes();
    int  updateWeight(Sample *s, int iWin, int jWin);
    void getNodeFeatures(int i, int j, std::vector<double>  &info); 
  
 
    void print();
    void setDataSet(DataSet* dataSet);
    void setSizeNetwork(int sizeNetwork);
    int getSizeNetwork() const;
    void initializeNodes(int sizeNodes = 2, bool positivesValues = false ); 
    
private:
    
    int validatePos(int pos); 
    // armazena os nodos da rede
    Node nodes[100][100];
 
    int sizeNetwork;
    int currentIt;
    Sample* currentSample; 
    double learningRate;
    double minLearningRate;
    double alpha; ///< Taxa de aprendizagem atual 
    double sigma; ///< Determinar a largura da função de vizinhaça 
    
    int maxIteration;
 
    DataSet *dataSet; 
    int epoch; 
    int maxEpoch; 
    

    bool debug;
};

#endif	/* SOM_H */


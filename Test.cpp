/* 
 * File:   Test.cpp
 * Author: oriva
 * 
 * Created on 20 de Agosto de 2016, 11:37
 */

#include "Test.h"


Test::Test() {
}

Test::Test(const Test& orig) {
}

void Test::colorDataSet() {
    std::string fileData = "data/cores_3d.txt";
    
    SOM som(10);
    DataSet *data = new DataSet(fileData);
    data->show();
    
    som.setDataSet(data);

    
    float maxColorInitialValue = 0.02; 
    som.initializeNodes(3,true, maxColorInitialValue); 
    
    int iterations = 150;

    
    // Execute many iterations 
    int i = 0;
    som.printNodes();
    while (i < iterations) {
        som.executeOneIt();
        i++;
        som.printNodes(); 
    }
    std::cout << "Iteractions executed: " << iterations << std::endl;
 
    delete data; 
}

void Test::armInLine() {
    std::string fileData = "data/braco_em_linha.txt";
    SOM som(12);
    DataSet *data = new DataSet(fileData);
    data->show();
    
    som.setDataSet(data);

 
    float maxFeatureInitialValue = 0.01; 
    som.initializeNodes(4,true, maxFeatureInitialValue); 
    
    int iterations = 50;

    
    // Execute many iterations 
    int i = 0;
    som.printNodes();
    while (i < iterations) {
        som.executeOneIt();
        i++;
        som.printNodes(); 
    }
    std::cout << "Iteractions executed: " << iterations << std::endl;
 
    delete data; 
  
}

Test::~Test() {
}


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
    
    SOM som(3);
    DataSet *data = new DataSet(fileData);
    data->show();
    
    som.setDataSet(data);

    int maxColorIntensity = 255;
    int maxCollorInitialValue = 20; 
    som.initializeNodes(3,true, maxCollorInitialValue, maxColorIntensity); 
    
    int iterations = 2;

    
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


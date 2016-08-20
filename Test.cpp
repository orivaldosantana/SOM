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
    
    DataSet *data = new DataSet(fileData);
    data->show();
    
    som.setDataSet(data);
    som.initializeNodes(7,true); 
    
    int iterations = 10;

    
    // Execute many iterations 
    int i = 0;
    while (i < iterations) {
        som.executeOneIt();
        i++;
    }
    std::cout << "Iteractions executed: " << iterations << std::endl;
 
    delete data; 
}

Test::~Test() {
}


/* 
 * File:   Test.cpp
 * Author: oriva
 * 
 * Created on 20 de Agosto de 2016, 11:37
 */

#include "Test.h"
#include "TestArduino.h"


TestArduino::TestArduino() {
}

TestArduino::TestArduino(const TestArduino& orig) {
}

void TestArduino::allDirections(){
    std::string fileData = "data/ura4_arduino.txt";
    
    SOM som(6);
    DataSet *data = new DataSet();
    data->loadDataFromClassesFile(fileData); 
    data->show();
    
    som.setDataSet(data);
    
    float maxColorInitialValue = 0.01; 
    som.initializeNodes(3,true, maxColorInitialValue); 
    
    int iterations = 550;
    
    // Execute many iterations 
    int i = 0;
    som.printNodes();
    som.printNodes(true);
    while (i < iterations) {
        som.printMitrixFormat();
        som.executeOneIt();
        i++;
        //som.printNodes(true);
       
    }
    std::cout << "Iteractions executed: " << iterations << std::endl;
    
    som.labelingPhase(); 
    som.showLabels(); 
    som.showWinnerDistances();
    som.labelingPhaseII();
    som.showLabels(); 
    som.showWinnerDistances();
    
    //som.saveToTxtFile("/tmp/som_a");
    som.printMitrixFormat();
    som.printLabelsMitrixFormat(); 
}

void TestArduino::turnLeft(){
    std::string fileData = "data/ura_arduino.txt";
    
    SOM som(6);
    DataSet *data = new DataSet();
    data->loadDataFromClassesFile(fileData); 
    data->show();
    
    som.setDataSet(data);

    
    float maxColorInitialValue = 0.01; 
    som.initializeNodes(3,true, maxColorInitialValue); 
    
    int iterations = 250;

    
    // Execute many iterations 
    int i = 0;
    som.printNodes();
    som.printNodes(true);
    while (i < iterations) {
        som.printMitrixFormat();
        som.executeOneIt();
        i++;
        //som.printNodes(true);
       
    }
    std::cout << "Iteractions executed: " << iterations << std::endl;
    
    som.labelingPhase(); 
    som.showLabels(); 
    som.showWinnerDistances();
    som.labelingPhaseII();
    som.showLabels(); 
    som.showWinnerDistances();
    
    //som.saveToTxtFile("/tmp/som_a");
    som.printMitrixFormat();
    som.printLabelsMitrixFormat(); 
}

 
TestArduino::~TestArduino() {
}


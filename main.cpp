/* 
 * File:   main.cpp
 * Author: oriva
 *
 * Created on 20 de Agosto de 2016, 10:56
 */

#include <cstdlib>
#include <iostream>
#include "Test.h"
#include "TestArduino.h"

using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {
    cout << " Testando rede SOM!" << endl;
    
    //Test test; 
    
    //test.colorDataSet(); 
    //test.armInLine();
    
    TestArduino test; 
    test.turnLeft(); 
    
    return 0;
}


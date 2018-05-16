/* 
 * File:   Test.h
 * Author: oriva
 *
 * Created on 20 de Agosto de 2016, 11:37
 */

#ifndef TESTARDUINO_H
#define	TESTARDUINO_H

#include "SOM.h"
#include "DataSet.h"
#include <fstream>

class TestArduino {
public:
    TestArduino();
    TestArduino(const TestArduino& orig);
    virtual ~TestArduino();
    
    void turnLeft();
    void allDirections(); 
 
private:
    
    

};

#endif	/* TEST_H */


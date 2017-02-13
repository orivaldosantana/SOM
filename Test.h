/* 
 * File:   Test.h
 * Author: oriva
 *
 * Created on 20 de Agosto de 2016, 11:37
 */

#ifndef TEST_H
#define	TEST_H

#include "SOM.h"
#include "DataSet.h"
#include <fstream>

class Test {
public:
    Test();
    Test(const Test& orig);
    virtual ~Test();
    
    void colorDataSet();
    void armInLine();  
private:
    
    

};

#endif	/* TEST_H */


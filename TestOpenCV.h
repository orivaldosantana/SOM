/* 
 * File:   Test.h
 * Author: oriva
 *
 * Created on 20 de Agosto de 2016, 11:37
 */

#ifndef TESTOPENCV_H
#define	TESTOPENCV_H

#include "SOM.h"
#include "DataSet.h"
#include <fstream>

#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
#include <stdio.h>
using namespace cv;
using namespace std;


class TestOpenCV {
public:
    TestOpenCV();
    TestOpenCV(const TestOpenCV& orig);
    virtual ~TestOpenCV();
    
    int openWebcam(); 
    void loadImageToMatrix(); 
 
private:
    
    

};

#endif	/* TESTOPENCV_H */


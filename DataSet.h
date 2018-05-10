/* 
 * File:   DataSet.h
 * Author: oriva
 *
 * Created on 10 de Outubro de 2014, 15:32
 */

#ifndef DATASET_H
#define	DATASET_H

#include "Sample.h"
#include <cstdlib> 
#include <limits> 
#include <iostream>
#include <fstream>
#include <algorithm>

class DataSet {
public:
    DataSet         ( );
    DataSet         (std::string fn);
    DataSet         (const DataSet& orig);
    virtual ~DataSet( );

    void            generateRandomIndex         ( );
    //void            getRandomSample             (Sample &s);
    bool            getRandomSample             (Sample* &s); 
    Sample*         getRandomSample             ( ); 
    Sample*         getSample                   (unsigned int i);
    int             getSize                     ( ); 
    bool            isEmpty                     ( );
    void            loadDataFromFile            (std::string fileName);
    void            loadDataFromClassesFile     (std::string fileName);
    void            normalizeData               ( );
    void            putNoise                    (float                 sigma, 
                                                 unsigned int    repetitions);
    void            saveToFile                  (std::string        fileName, 
                                                 bool       randomize = true, 
                                                 bool      normalize = false);
    void            saveToFileOctaveFormat      (std::string        fileName,
                                                 unsigned int       rows = 0);
    void            savePartToFile              (std::string        fileName);
    void            show                        ( );
    void            randomizeIndex              ( );
    //void            resetRandomSampleIndex      ( );
    
    static int srandInc;  ///< Utilizada para incrementar o semente que aleatoriza o vetor de incices 
    
private:
    int dataSetSize; 
    std::string fileName;
    std::vector<std::string> lables;  
    bool empty;
    std::vector<Sample*> matrix;
    std::vector<unsigned int> index;
    int sampleI; 
    int sampleSize;

};

#endif	/* DATASET_H */


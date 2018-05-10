/* 
 * File:   DataSet.cpp
 * Author: oriva
 * 
 * Created on 10 de Outubro de 2014, 15:32
 */

#include "DataSet.h"

 int DataSet::srandInc = 0; 

DataSet::DataSet() {
    sampleI = 0;
    sampleSize = 0;
    dataSetSize = 0;

}

DataSet::DataSet(std::string fn){
    sampleI = 0; 
    loadDataFromFile(fn); 
}

DataSet::DataSet(const DataSet& orig) {
    
}

void DataSet::generateRandomIndex() {
    
    //std::cout << endl << "----------------" << DataSet::srandInc <<"----------" << endl << time(NULL) + DataSet::srandInc << endl; 
    srand(unsigned ( time(NULL) + DataSet::srandInc ));
    index.clear();
    unsigned int tss = index.size();
    for (unsigned int i = 0; i < matrix.size(); i++)
        index.push_back(i);
    randomizeIndex();

}

/**
 * Obtem um amostra aleatória 
 * @param s uma amostra
 * @return verdadeiro se a amostra é a primeira, falso para as outras
 */
 bool DataSet::getRandomSample(Sample* &s) {
    s = getRandomSample();
    if (sampleI == 0)
        return true; 
    return false; 
}

Sample* DataSet::getRandomSample() {
    sampleI++;
    if (((uint) sampleI) >= matrix.size())
        sampleI = 0;
    return (matrix[index[sampleI]]);
}

Sample* DataSet::getSample(unsigned int i) {
    if (i >= matrix.size())
        i = 0;
    return matrix[i];
}

int DataSet::getSize(){
    matrix.size(); 
}

bool DataSet::isEmpty(){
    return empty; 
}

//TODO: adicionar uma excessão na leitura de arquivo 
void DataSet::loadDataFromFile(std::string fileName) {
    matrix.clear(); 
    std::ifstream file;
    std::vector<double> lineMatrix;
    file.open(fileName.c_str());
    if (!file.good()) {
        std::cout << " File, " << fileName << ", not found! " << std::endl;
        return;
    }
    float columns, lines, data;
    file >> lines >> columns;
    for (int i = 0; i < lines; i++) {
        if (file.good()) {
            for (int j = 0; j < columns; j++) {
                file >> data;
                lineMatrix.push_back(data);
            }
           // Sample s(lineMatrix);

            matrix.push_back(new Sample(lineMatrix));
            lineMatrix.clear(); 
        }
    }
    empty = false;
    sampleSize = columns;
    //matrix.pop_back();
    dataSetSize = matrix.size();
    //originalDatabaseSize = matrix.size();
    generateRandomIndex(); 
}

void DataSet::loadDataFromClassesFile(std::string fileName) {
    matrix.clear(); 
    std::ifstream file;
    std::string label; 
    std::vector<double> lineMatrix;
    file.open(fileName.c_str());
    if (!file.good()) {
        std::cout << " File, " << fileName << ", not found! " << std::endl;
        return;
    }
    float columns, lines, data;
    file >> lines >> columns;
    for (int i = 0; i < lines; i++) {
        if (file.good()) {
            for (int j = 0; j < columns-1; j++) {
                file >> data;
                lineMatrix.push_back(data);
            }
            // Sample s(lineMatrix);
            file >> label; 
            matrix.push_back(new Sample(lineMatrix, label));
            lineMatrix.clear();     
        }
    }
    empty = false;
    sampleSize = columns;
    //matrix.pop_back();
    dataSetSize = matrix.size();
    //originalDatabaseSize = matrix.size();
    generateRandomIndex(); 
}

void DataSet::normalizeData() {
    std::vector<double> lineMatrix;
    double positiveInfinityValue = std::numeric_limits<double>::max();
    double negativeInfinityValue = std::numeric_limits<double>::min();
    Sample* s;
    std::vector<double> maxValues(sampleSize, negativeInfinityValue);
    std::vector<double> minValues(sampleSize, positiveInfinityValue);
    // obtem os maiores e menores valores
    for (uint i = 0; i < matrix.size(); i++) {
        s = matrix.at(i);
        s->getFeatures(lineMatrix);
        for (int j = 0; j < sampleSize; j++) {
            float value = lineMatrix.at(j);
            if (value > maxValues.at(j)) {
                maxValues.at(j) = value;
            }
            if (value < minValues.at(j)) {
                minValues.at(j) = value;
            }
        }
    }
    std::cout << " - - - min: ";
    for (int j = 0; j < sampleSize; j++) {
        std::cout << minValues.at(j) << " ";
    }
    std::cout << std::endl;
    std::cout  << " - - - max: ";
    for (int j = 0; j < sampleSize; j++) {
        std::cout << maxValues.at(j) << " ";
    }
    std::cout << std::endl;
    for (uint i = 0; i < matrix.size(); i++) {
        s = matrix.at(i);
        s->getFeatures(lineMatrix);
        // normaliza 
        for (int j = 0; j < sampleSize; j++) {
            double newValue = (lineMatrix.at(j) - minValues[j]) / (maxValues[j] - minValues[j]);
            lineMatrix.at(j) = newValue;
            s->setFeatures(lineMatrix); 
        }
    }
}

void DataSet::putNoise(float sigma, unsigned int repetitions) {

    std::vector<Sample*> matrixTemp;
    uint amountOriginalData = matrix.size();
    for (uint i = 0; i < repetitions * matrix.size(); i++) {
        uint pos = i % amountOriginalData;
        Sample* originalSample = matrix.at(pos);
        std::vector<double> info;
        originalSample->getFeatures(info);
        Sample* noiseSample= new Sample(info);
        noiseSample->putNormalNoise(sigma);
        matrixTemp.push_back(noiseSample);
    }
    matrix = matrixTemp;
    dataSetSize = matrixTemp.size();
}

void DataSet::randomizeIndex() {
    std::random_shuffle(index.begin(), index.end());
}



void DataSet::saveToFile(std::string fileName, bool randomize, bool normalize) {
    std::vector<double> lineMatrix;
    Sample* s;
    if (empty)
        return;
    std::ofstream file(fileName.c_str());
    if (normalize) {
        normalizeData();
    }
    file << matrix.size() << " " << sampleSize << std::endl;
    // escrita dos dados em arquivo
    for (int i = 0; i < matrix.size(); i++) {
        if (sampleSize != 0) {
            if (randomize) {
                s = getRandomSample();
            } else {
                s = getSample(i);
            }
            s->getFeatures(lineMatrix);
            for (int j = 0; j < sampleSize; j++) {
                file << lineMatrix[j] << " ";
            }
        }
        file << std::endl;
    }
    file.close();
}



void DataSet::saveToFileOctaveFormat(std::string fileName, unsigned int rows) {
    std::vector<double> lineMatrix;
    Sample* s;
    std::ofstream file(fileName.c_str());
    if (rows == 0)
        rows = matrix.size();

    file << "# name: data " << std::endl;
    file << "# type: matrix " << std::endl;
    file << "# rows: " << rows << std::endl;
    file << "# columns: " << sampleSize << std::endl;
    uint i = 0;
    uint r = 0;
    while (r < rows) {

        if (i == matrix.size())
            i = 0;
        s = getSample(i);
        std::cout << s->toString() << std::endl;
        s->getFeatures(lineMatrix);
        //     file << (i % originalDatabaseSize ) + 1 << " " ;
        for (int j = 0; j < sampleSize; j++) {
            file <<  lineMatrix[j] << " ";
        }
        file << std::endl;
        i++;
        r++;
    }
    file.close();
}


void DataSet::show() {
    if (empty)
        return;
    // leitura da estrutura de dados que contem o arquivo
    Sample s(0); 
    std::cout << " Size of matrix:" << matrix.size() << std::endl;
    for (uint i = 0; i < matrix.size(); i++) {
        std::cout << "Sample "<< i << ": ";
        std::cout <<  matrix.at(i)->toString() << std::endl; 
    }
    std::cout << std::endl;
}

DataSet::~DataSet() {
}


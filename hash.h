#ifndef HASH_H
#define HASH_H

#include <iostream>
#include <cmath>
#include <random>
#include <chrono>

typedef std::size_t HASH_INDEX_T;

struct MyStringHash {
    HASH_INDEX_T rValues[5] { 983132572, 1468777056, 552714139, 984953261, 261934300 };
    MyStringHash(bool debug = true)
    {
        if(false == debug){
            generateRValues();
        }
    }
    // hash function entry point (i.e. this is h(k))
    HASH_INDEX_T operator()(const std::string& k) const
    {
        // Add your code here
        std::vector<unsigned long long> wordC(5,0);// Breaks strings into up to 5 base 36 chunks

        int chunkInd=0;
        int strLength= static_cast<int>(k.size());
        //Process from end of string in chunks of 6
        for(int i=strLength-1;i>=0 && chunkInd<5; ++chunkInd){
          unsigned long long chunkVal=0;
          unsigned long long baseM=1;

          for(int j=0;j<6 && i>=0;++j,--i){
            char normChar=std::tolower(k[i]);// normalize to lowercase
            HASH_INDEX_T base36V=letterDigitToNumber(normChar);//Convert to base 36 digit
            chunkVal+=base36V*baseM;
            baseM*=36;
          }
          wordC[4-chunkInd]=chunkVal;// fill chunks from right to left
        }
        //Weighted sum using rValues
        unsigned long long hashSum=0;
        for(int i=0;i<5;i++){
          hashSum+=rValues[i]*wordC[i];
        }

        return hashSum;
    }

    // A likely helper function is to convert a-z,0-9 to an integral value 0-35
    HASH_INDEX_T letterDigitToNumber(char letter) const
    {
        // Add code here or delete this helper function if you do not want it
        if(letter>='0' && letter<='9'){
          return 26+(letter-'0');
        }
        else if(letter>='A' && letter<='Z'){
          return letter-'A';

        }
        else if(letter>='a' && letter<='z'){
          return letter-'a';
        }
        return 0;

    }

    // Code to generate the random R values
    void generateRValues()
    {
        // obtain a seed from the system clock:
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        std::mt19937 generator (seed);  // mt19937 is a standard random number generator

        // Simply call generator() [it has an operator()] to get another random number
        for(int i{ 0 }; i < 5; ++i)
        {
            rValues[i] = generator();
        }
    }
};

#endif

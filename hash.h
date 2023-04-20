#ifndef HASH_H
#define HASH_H

#include <iostream>
#include <cmath>
#include <random>
#include <chrono>


typedef std::size_t HASH_INDEX_T;
// unsigned long long baseConversion(std::string s);
// std::string reverseString(std::string inputString);

struct MyStringHash {
    HASH_INDEX_T rValues[5] { 983132572, 1468777056, 552714139, 984953261, 261934300 };
    MyStringHash(bool debug = true)
    {
        if(false == debug){
            generateRValues();
        }
    }
    // The Approach
    // The basic approach will be to treat groups of letters/digits as base-36 and convert to an integer value (i.e. the decimal equivalent).
    // First translate each letter into a value between 0 and 35, where a=0, b=1, c=2, …, z=25 and digit '0'=26, … '9'=35. Be sure to convert an upper case letter to lower case before performing this mapping. Next you will translate a (sub)string of 6 letters a1 a2 a3 a4 a5 a6 into an (unsigned long long) 64-bit integer w[i] (essentially converting from base-36 to decimal), via the following mathematical formula:
    // w[i]=365∗a1+364∗a2+363∗a3+362∗a4+36∗a5+a6
    // Place zeros in the leading positions if your (sub)string is shorter than 6 letters. So an example string like "104" would set a1, a2, and a3 all to zero (since we only have a length 3 string) and yield  
    // 362∗27+36∗26+30
    //  (since '1' : 27, '0' : 26, and '4' : 30) You should use the base conversion approach taught in class to avoid repeated calls to pow(). Note that indexing is a bit tricky here so think carefully. The digit at the “end” of the string is assigned the power 36^0, and the 2nd to last letter is worth 36^1, etc.
    // If an input word is longer than 6 letters, then you should first do the above process for the last 6 letters in the word, then repeat the process for each previous group of 6 letters. Recall, you will never receive a word longer than 28 characters. The last group may not have 6 letters in which case you would treat it as a substring of less than 6 characters as described above. Since we have at most 28 characters this process should result in a sequence of no more than 5 integers: w[0] w[1] w[2] w[3] w[4], where w[4] was produced by the last 6 letters of the word.
    // Store these values in an array (of unsigned long long). Place zeros in the leading positions of w[i] if the string does not contain enough characters to make use of those values. So for a string of 12 letters, w[0], w[1], and w[2] would all be 0 and only w[3] and w[4] would be (potentially) non-zero.
    // We will now hash the string. Use the following formula to produce and return the final hash result using the formula below (where the r values are explained below).
    // h(k)=(r[0]∗w[0]+r[1]∗w[1]+r[2]∗w[2]+r[3]∗w[3]+r[4]∗w[4])
    // hash function entry point (i.e. this is h(k))
    HASH_INDEX_T operator()(const std::string& k) const
    {
        // Add your code here
        
        //reverse the string
        
        std::string k_ = k;
        k_ = reverseString(k_);
        
        std::vector<unsigned long long> w;
        size_t j = 0;

        for(size_t i = 0; i <= 28; i += 6)//iterate the string by 6. Max cap is 28 chars
        {
            double w_value = 0;
            std::string temp = "";
            for(j = i; j < i + 6; ++j)
            {
                if(j >= k_.size()){ // when iterate to the end of the string ,break
                    break;
                }
                temp+=k_[j];      
            }
            //conver the 6 chars to a base 36 number
            w_value = baseConversion(temp);
            w.push_back(w_value);
        }
        //h(k)=(r[0]∗w[0]+r[1]∗w[1]+r[2]∗w[2]+r[3]∗w[3]+r[4]∗w[4])
        HASH_INDEX_T result = 0;
        for(int i = 0; i < 5; ++i)
        {
            HASH_INDEX_T temp = rValues[i] * w[4-i];
            result += temp;
        }
        return result;

    }


    // A likely helper function is to convert a-z,0-9 to an integral value 0-35
    HASH_INDEX_T letterDigitToNumber(char letter) const
    {
        // Add code here or delete this helper function if you do not want it
        //if letters, convert to 0-25, if digits, convert to 26-35
        
        if(letter >= 'A' && letter <= 'Z')
        {
            letter = letter + 32;
        }
        if(letter >= 'a' && letter <= 'z')
        {
            return letter - 'a';
        }
        else if(letter >= '0' && letter <= '9')
        {
            return letter - '0' + 26;
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

    unsigned long long baseConversion(const std::string s)const
    {
        unsigned long long result = 0;
        for(size_t i = 0; i < s.size(); ++i)
        {
            result += letterDigitToNumber(s[i]) * pow(36, i);
        }
        return result;
    }

    std::string reverseString(const std::string inputString) const
    {
        std::string reversedString = "";
        int length = inputString.length();

        for (int i = length - 1; i >= 0; i--) {
            reversedString += inputString[i];
        }

        return reversedString;
    }

};




#endif

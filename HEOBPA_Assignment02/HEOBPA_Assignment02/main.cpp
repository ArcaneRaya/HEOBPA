//
//  main.cpp
//  HEOBPA_Assignment02
//
//  Created by Ruben Bergshoeff on 11/26/17.
//  Copyright © 2017 Ruben Bergshoeff. All rights reserved.
//

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <math.h>

template <typename Tvec, typename Tpred>
std::vector<std::vector<Tvec>> partitionOn (std::vector<Tvec> &stringVector, Tpred pred) {
    typename std::vector<Tvec>::iterator bound;
    bound = std::partition(stringVector.begin(), stringVector.end(), pred);
    
    typename std::vector<Tvec> v1;
    for (auto it = stringVector.begin(); it != bound; ++it) {
        v1.push_back(*it);
    }
    typename std::vector<Tvec> v2;
    for (auto it = bound; it != stringVector.end(); ++it) {
        v2.push_back(*it);
    }
    
    return std::vector<std::vector<Tvec>> {v1,v2};
}

std::string makeUppercase (std::string &s) {
    for(char& c : s) {
        if(c >= 'a' && c <= 'z')
        {
            c += 'A' - 'a';
        }
    }
    return s;
}

void removeDoubles (std::vector<std::string> &stringVector) {
    std::vector<std::string> tempStringVector = stringVector;
    std::sort(tempStringVector.begin(), tempStringVector.end());
    tempStringVector.erase(std::unique(tempStringVector.begin(), tempStringVector.end()), tempStringVector.end());
    std::vector<std::string>::iterator newEnd;
    newEnd = std::remove_if(stringVector.begin(), stringVector.end(), [&] (std::string s) -> bool {
                                if (std::find(tempStringVector.begin(), tempStringVector.end(), s) != tempStringVector.end()){
                                    tempStringVector.erase(std::find(tempStringVector.begin(), tempStringVector.end(), s));
                                    return false;
                                } else {
                                    return true;
                                }
                            });
    stringVector.erase(newEnd, stringVector.end());
}

void evenOrUneven (std::vector<double> &intVector) {
    if ( std::all_of(intVector.begin(), intVector.end(), [](double i){return (fmod(i, 2));}) ) {
        std::cout << "All the elements are odd numbers.";
    } else if ( std::all_of(intVector.begin(), intVector.end(), [](double i){return !(fmod(i, 2));}) ) {
        std::cout << "All the elements are even numbers.";
    } else {
        std::cout << "There are both even and odd numbers.";
    }
    std::cout << std::endl;
}

template<typename T>
void displayVector (std::vector<T> &someVector) {
    for (auto it = someVector.begin(); it != someVector.end(); ++it) {
        std::cout<< *it << ' ' ;
    }
    std::cout << std::endl;
}

//struct NotDuplicate {
//    bool operator()(const T& element) {
//        return s_.insert(element).second; // true if s_.insert(element);
//    }
//private:
//    total;
//};

int main(int argc, const char * argv[]) {
    std::vector<std::string> colours{"red", "green", "white", "blue", "orange", "green", "orange", "black", "purple"};
    std::cout << "STRINGS" << std::endl;
    // gebruik functies uit <algorithm> en <functional> om (steeds vanuit een ORIGINELE copie van deze vector)
    // 1) de vector in 2 nieuwe vectoren te splitsen, 1 met alles wat alfabetisch voor 'purple' komt, 1 met alles er na
    std::cout << "# 1)" << std::endl;
    auto coloursCopy1 = colours;
    auto returns = partitionOn(coloursCopy1, [] (std::string s) -> bool { return s < "purple"; } );
    std::cout << "1 - ";
    displayVector(returns[0]);
    std::cout << "2 - ";
    displayVector(returns[1]);
    std::cout << std::endl;
    
    // 2) alle elementen UPPERCASE te maken.
    std::cout << "# 2)" << std::endl;
    auto coloursCopy2 = colours;
    std::transform(coloursCopy2.begin(), coloursCopy2.end(), coloursCopy2.begin(), makeUppercase);
    displayVector(coloursCopy2);
    std::cout << std::endl;
    
    // 3) alle dubbele te verwijderen
    std::cout << "# 3)" << std::endl;
    auto coloursCopy3 = colours;
    removeDoubles(coloursCopy3);
    displayVector(coloursCopy3);
    std::cout << std::endl;
    std::cout << std::endl;
    
    
    std::vector<double> numbers{10, 324422, 6, -23, 234.5, 654.1, 3.1242, -9.23, 635};
    std::cout << "DOUBLES" << std::endl;
    // gebruik functies uit <algorithm> en <functional> om (steeds vanuit een ORIGINELE copie van deze vector)
    // 1) alle negatieve elementen te verwijderen
    std::cout << "# 1)" << std::endl;
    auto numbersCopy1 = numbers;
    auto newEnd = std::remove_if(numbersCopy1.begin(), numbersCopy1.end(), [] (int i) -> bool { return 0 > i; });
    numbersCopy1.erase(newEnd, numbersCopy1.end());
    displayVector(numbersCopy1);
    std::cout << std::endl;
    
    // 2) voor alle elementen te bepalen of ze even of oneven zijn
    std::cout << "# 2)" << std::endl;
    auto numbersCopy2 = numbers;
    evenOrUneven(numbersCopy2);
    std::cout << std::endl;
    auto returns2 = partitionOn(numbersCopy2, [] (double i) -> bool { return (fmod(i, 2)) == 0; } );
    std::cout << "1 - ";
    displayVector(returns2[0]);
    evenOrUneven(returns2[0]);
    std::cout << std::endl;
    std::cout << "2 - ";
    displayVector(returns2[1]);
    evenOrUneven(returns2[1]);
    std::cout << std::endl;
    
    // 3) de som, het gemiddelde, en het product van alle getallen te berekenen
    std::cout << "# 3)" << std::endl;
    auto numbersCopy3 = numbers;
    double sum;
    std::for_each(numbersCopy3.begin(), numbersCopy3.end(), [&] (double n) {
        sum += n;
    });
    std::cout << "SUM: " << sum << std::endl;
    std::cout << "AVERAGE: " << sum / numbersCopy3.size() << std::endl;
    
    double product = 1;
    std::for_each(numbersCopy3.begin(), numbersCopy3.end(), [&] (double n) {
        product *= n;
    });
    std::cout << "PRODUCT: " << product << std::endl;
    
    
    return 0;
}

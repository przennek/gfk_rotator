/* 
 * File:   AbstractTest.h
 * Author: przemek
 *
 * Created on 24 stycznia 2016, 00:10
 */

#ifndef ABSTRACTTEST_H
#define ABSTRACTTEST_H

#include <string>
#include <exception>

using namespace std;

class AbstractTest {
public:
    void assertTrue(bool p1) {
        if(!p1) std::cout << get_test_name() << " failed.\n";
        std::cout << get_test_name() << " passed.\n";
    }
       
    void assertFalse(bool p1) {
        if(p1) std::cout << get_test_name() << " failed.\n";
        std::cout << get_test_name() << " passed.\n";
    }
    
    virtual void runTest();
    
    virtual string get_test_name() {
        return "AbstractTest";
    };
};

#endif /* ABSTRACTTEST_H */


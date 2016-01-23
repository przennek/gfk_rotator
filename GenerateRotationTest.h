/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   GenerateRotationTest.h
 * Author: przemek
 *
 * Created on 24 stycznia 2016, 00:11
 */

#ifndef GENERATEROTATIONTEST_H
#define GENERATEROTATIONTEST_H

#include "AbstractTest.h"

class GenerateRotationTest: public AbstractTest {
public:    
    void runTest() {
        assertTrue(true);
    }
    
    static GenerateRotationTest *instance;
};

GenerateRotationTest* GenerateRotationTest::instance = new GenerateRotationTest();
#endif /* GENERATEROTATIONTEST_H */


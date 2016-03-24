#pragma once
#ifndef TIME_TEST_H
#define TIME_TEST_H

class TimeTest{
    public:
        TimeTest();
        
        double czasKomiwojazerZupelny(int rozmiar = 0, int ilePowtorzen = 100);
        double czasKomiwojazerBoundBranch(int rozmiar = 0, int ilePowtorzen = 100);
};
#endif

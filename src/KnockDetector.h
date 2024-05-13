#include "KnockAlgorithm.h"

#ifndef KnockDetector_h
#define KnockDetector_h

#if defined(ESP8266) || defined(ESP32)
#include <functional>
#define CALLBACK std::function<void(float knockIntensity, int pulseLength)> callback
#else
#define CALLBACK void (*callback)(float knockIntensity, int pulseLength)
#endif


#include <Arduino.h>

#include "KnockPulse.h"

class KnockDetector {
    
    public:
        KnockDetector(int lowThreshold, int noiseThreshold, CALLBACK);
        void loop(int reading);

        KnockDetector& setCallback(CALLBACK);
        
    private:
        CALLBACK;
        int _reading;
        int _state;
        bool _isAwaitingKnockTransient;
        long _currentKnockBurstTime;
        long _lastKnockBurstTime;
        long _silenceStartTime;
        long _silenceEndTime;
        int _lowThreshold;
        int _noiseThreshold;
        bool _mustReadValue = false;
        const long _silenceTimeout = 20 * 1000; // 50 ms for waiting for new values to append to signal

        KnockPulse _knockPulse;
};

#endif

#ifndef KnockPulse_h
#define KnockPulse_h

class KnockPulse {
    public:
        KnockPulse();
        KnockPulse(int value, long time);
        double getKnockIntensity();
        long getKnockLength();
        
        int mTransientValue = 0;
        long mPulseStartTime = 0;
        long mPulseEndTime = 0;
        int mValuesCount = 0;
        int mValuesSum = 0;
};

#endif

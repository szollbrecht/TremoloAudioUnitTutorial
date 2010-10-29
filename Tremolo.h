#include "AUEffectBase.h"
#include "TremoloVersion.h"

#if AU_DEBUG_DISPATCHER
  #include "AUDebugDispatcher.h"
#endif


#ifndef __Tremolo_h__
#define __Tremolo_h__


#pragma mark ____Tremolo Parameters

// parameters
static CFStringRef kParamName_Tremolo_Freq      = CFSTR("Frequency");
static const float kDefaultValue_Tremolo_Freq   = 2.0;
static const float kMinimumValue_Tremolo_Freq   = 0.5;
static const float kMaximumValue_Tremolo_Freq   = 20.0;

static CFStringRef kParamName_Tremolo_Depth     = CFSTR("Depth");
static const float kDefaultValue_Tremolo_Depth  = 50.0;
static const float kMinimumValue_Tremolo_Depth  = 0.0;
static const float kMaximumValue_Tremolo_Depth  = 100.0;

static CFStringRef kParamName_Tremolo_Waveform  = CFSTR("Waveform");
static const int kSineWave_Tremolo_Waveform     = 1;
static const int kSquareWave_Tremolo_Waveform   = 2;
static const int kDefaultValue_Tremolo_Waveform = kSineWave_Tremolo_Waveform;

// menu item names for the waveform parameter
static CFStringRef kMenuItem_Tremolo_Sine = CFSTR("Sine");
statuc CFStringRef kMenuItem_Tremolo_Square = CFSTR("Square");

// parameter identifiers
enum {
  kParameter_Frequency = 0;
  kParameter_Depth     = 1;
  kParameter_Waveform  = 2;
  kNumberOfParameters  = 3;
};

#pragma mark ____Tremolo
class Tremolo : public AUEffectBase
{
public:
  Tremolo(AudioUnit component);
#if AU_DEBUG_DISPATCHER
  virtual ~Tremolo () { delete mDebugDispatcher; }
#endif
  
  virtual AUKernelBase *    NewKernel() { return new TremoloKernel(this); }
  
  virtual  OSStatus      GetParameterValueStrings(AudioUnitScope      inScope,
                             AudioUnitParameterID    inParameterID,
                             CFArrayRef *      outStrings);
    
  virtual  OSStatus      GetParameterInfo(AudioUnitScope      inScope,
                         AudioUnitParameterID  inParameterID,
                         AudioUnitParameterInfo  &outParameterInfo);
    
  virtual OSStatus      GetPropertyInfo(AudioUnitPropertyID    inID,
                        AudioUnitScope      inScope,
                        AudioUnitElement    inElement,
                        UInt32 &      outDataSize,
                        Boolean  &      outWritable );
  
  virtual OSStatus      GetProperty(AudioUnitPropertyID inID,
                      AudioUnitScope     inScope,
                      AudioUnitElement     inElement,
                      void *      outData);
  
   virtual  bool        SupportsTail () { return false; }
  
  /*! @method Version */
  virtual OSStatus    Version() { return kTremoloVersion; }
  
    
  
protected:
    class TremoloKernel : public AUKernelBase    // most of the real work happens here
  {
public:
    TremoloKernel(AUEffectBase *inAudioUnit )
    : AUKernelBase(inAudioUnit)
  {
  }
    
    // *Required* overides for the process method for this effect
    // processes one channel of interleaved samples
        virtual void     Process(  const Float32   *inSourceP,
                    Float32       *inDestP,
                    UInt32       inFramesToProcess,
                    UInt32      inNumChannels,
                    bool      &ioSilence);
    
        virtual void    Reset();
    
    //private: //state variables...
  };
};

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


#endif
//
//  ofxAVFVideoPlayer.h
//  AVFoundationTest
//
//  Created by Sam Kronick on 5/31/13.
//
//

#pragma once

#include "ofMain.h"

#ifdef __OBJC__
#import "ofxAVFVideoRenderer.h"
#endif

/*
 [ofBaseVideoPlayer]
 virtual void                play() = 0;
 virtual void                stop() = 0;
 virtual float                 getWidth() const = 0;
 virtual float                 getHeight() const = 0;
 virtual bool                isPaused() const = 0;
 virtual bool                isLoaded() const = 0;
 virtual bool                isPlaying() const = 0;
 
 [ofBaseVideo]
 virtual bool isFrameNew() const =0;
 virtual void close()=0;
 virtual bool isInitialized() const=0;
 virtual bool setPixelFormat(ofPixelFormat pixelFormat) = 0;
 virtual ofPixelFormat getPixelFormat() const = 0;

 [ofBaseHasPixels]
 virtual ofPixels_<T> & getPixels()=0;
 virtual const ofPixels_<T> & getPixels() const=0;
 */

class ofxAVFVideoPlayer  : public ofBaseVideoPlayer {
    
public:
    
    ofxAVFVideoPlayer();
    ~ofxAVFVideoPlayer();
    
    bool                load(string path) override;
    bool                isInitialized() const override { return isLoaded(); }
    
    void                closeMovie();
    void                close() override;
    
    void                idleMovie();
    void                update() override;
    void                play() override;
    void                stop() override;
    
    float               getAmplitude(int channel = 0);
    float               getAmplitudeAt(float pos, int channel = 0);
    float *             getAllAmplitudes();
    int                 getNumAmplitudes();
    
    bool                isFrameNew() const override; //returns true if the frame has changed in this update cycle
    
    // Returns openFrameworks compatible RGBA pixels.
    // Be aware of your current render mode.
    
    unsigned char *     getData();
    ofPixelsRef         getPixelsRef();
    ofPixels&           getPixels() override;
    const ofPixels&     getPixels() const override;
    
    // Returns openFrameworks compatible ofTexture pointer.
    // if decodeMode == OF_QTKIT_DECODE_PIXELS_ONLY,
    // the returned pointer will be NULL.
    ofTexture *         getTexture();
    ofTexture&          getTextureReference();
    
    bool                isLoading();
    bool                isLoaded() const override;
    bool                shouldLoadAudio();
    void                setShouldLoadAudio(bool doLoadAudio);
    bool                isAudioLoaded();
    bool                errorLoading();
    
    bool                isPlaying() const override;
    bool                getIsMovieDone();
    
    float               getPosition();
    float               getCurrentTime();
    float               getPositionInSeconds();
    int                 getCurrentFrame();
    float               getDuration();
    int                 getTotalNumFrames();
    bool                isPaused() const override;
    float               getSpeed();
    ofLoopType          getLoopState();
    float               getVolume();
    
    void                setPosition(float pct) override;
    void                setTime(float seconds);
    void                setPositionInSeconds(float seconds);
    void                setFrame(int frame) override; // frame 0 = first frame...
    void                setBalance(float balance);
    void                setPaused(bool bPaused) override;
    void                setSpeed(float speed) override;
    void                setLoopState(ofLoopType state) override;
    void                setVolume(float volume) override;
    
    // ofxAVFVideoPlayer only supports OF_PIXELS_RGB and OF_PIXELS_RGBA.
    bool                setPixelFormat(ofPixelFormat pixelFormat) override;
    ofPixelFormat       getPixelFormat() const override;
    
    void                draw(float x, float y, float w, float h);
    void                draw(float x, float y);
    
    float               getWidth() const override;
    float               getHeight() const override;
    
    void                firstFrame() override;
    void                nextFrame() override;
    void                previousFrame() override;
    
    void                setInternalPixelBufferAsYuv422(bool b);
    bool                isInternalPixelBufferAsYuv422() const;
    
protected:
    bool bInternalPixelBufferAsYuv422;
    
    ofLoopType currentLoopState;
    
    bool bTheFutureIsNow;
    
    bool bPaused;
    bool bShouldPlay;
    bool bShouldLoadAudio;
    
    float scrubToTime;
    bool bNewFrame;
    bool bHavePixelsChanged;
    
    float duration;
    float speed;
    
    string moviePath;
    
    bool bInitialized;
    void exit(ofEventArgs& args);
    
    void updateTexture();
    void reallocatePixels();
    
    ofFbo fbo;
    ofTexture tex;
    ofPixels pixels;
    ofPixelFormat pixelFormat;
    
    // This #ifdef is so you can include this .h file in .cpp files
    // and avoid ugly casts in the .m file
#ifdef __OBJC__
    AVFVideoRenderer* moviePlayer;
#else
    void * moviePlayer;
#endif
    
};

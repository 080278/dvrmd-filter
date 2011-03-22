#pragma once

#include <cv.h>
#include "vapi_types.h"
#include "visionapi.h"

namespace HHV {

VISIONAPI class Engine {
protected:
	unsigned long _fno;
public:
  Engine();
  virtual ~Engine();
  // Required engine frame rate
  virtual void Process(IplImage *img, __int64 frametime,  const std::vector<Event> &events_in ) =0;
  virtual int GetVideoEvents(std::vector<VideoEvent> &video_events_out) = 0;
  virtual int GetEvents(std::vector<Event> &events_out) = 0;
  virtual int  GetDisplayData(__int64 &frametime, FrameMetaDataList &metList) { return 0; };
  virtual const IplImage *GetProcessedImage() =0;
};

VISIONAPI Engine *GetProcessingEngineInstance(std::string engine_name, const Attributes& parameters);

};

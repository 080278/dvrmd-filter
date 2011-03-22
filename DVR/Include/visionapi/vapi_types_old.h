#pragma once

#include <vector>
#include <string>
#include <cv.h>

using std::string;
using std::vector;

namespace HHV {


typedef std::map<std::string, std::string> Attributes;

struct ObjectMeta {
	std::string	         id;		// unique object identifier
	std::string           label; // object text label
	std::string           type; // object class 
	bool			 bAlerted;	// object alert tag
	CvRect			 box;
	CvScalar	     color; // color used to draw object tracking / bounding box
};

struct VideoEvent {
	enum VideoEventLevel { VE_NONE=0, VE_ALERT=1, VE_EVENT=2, VE_STATUS =3, VE_DEBUG= 4 };
    __int64 time_stamp;
    VideoEventLevel event_level;
	std::string event_name;
    Attributes attributes;
	vector<ObjectMeta>	obj_meta;
};

struct Event {
	__int64 time_stamp;
	std::string src_id;
	std::string topic;
    Attributes attributes;
};

// display meta data
struct RGBColor {
  int r,g,b; //0-255
};

typedef std::vector <CvPoint> Points;  // a list of line segments

struct Attribute {
	std::string name;
	std::string value;
};

struct TextMeta {
  int x, y;
  RGBColor color;
  int size; // size in height
  std::string text;
};

struct DrawingStyle {
  RGBColor color;
  int thickness;
  bool bFill;
  RGBColor fill_color;
  int alpha;  // 0 to 100, the actual color = alpha*color+(1-alpha)*background_color
  bool bFlash;
} ;

struct PolyLine {
   RGBColor color;
   int thickness;
   int end_style; // 0 no style; 1: arrow solid, 2: arrow line
   int arrow_length;
   int arrow_width;
   Points lines;
 };


struct PolygonM {
   DrawingStyle style;
   Points points;
};

struct ObjectType {  
   DrawingStyle style;
 // object: -1: no display, 0: line_segment, 1: rectangle, 2: ellipse
   int type; 
   int x0, y0, x1,y1;
   int x2,y2, x3, y3;  // for use with ellipse only, 4 points bounds the ellipse
};

struct ObjectLoc {
   int x,y,w,h;
};

struct DisplayObjectMeta {
	std::string id;
	ObjectType obj;  // 
	PolyLine track;  // track of the objecct
};

typedef std::vector <DisplayObjectMeta> DisplayObjectMetaList; // display object info
typedef std::vector <PolyLine> PolyLines;

typedef std::vector <TextMeta> Texts;     // a list of texts
typedef std::vector <PolygonM> Polygons;     // a list of polygons
typedef std::vector <ObjectType> GUIObjects;     // a list of basic objects


struct FrameDisplayData {
  int image_width;
  int image_height;
  DisplayObjectMetaList disp_obj_list;

  PolyLines line_list;
  Texts text_list;
  Polygons polygon_list;
  GUIObjects gui_object_list;
  
  void clear()
  {
    disp_obj_list.clear();
    line_list.clear();
    text_list.clear();
    polygon_list.clear();
    gui_object_list.clear();
  }
};

struct FrameMetaData {
   FrameDisplayData displayData;    // For display
   Attributes attributes;       // additional attributes

   void clear()
   {
     displayData.clear();
     attributes.clear();
   }
};

typedef std::vector <FrameMetaData > FrameMetaDataList;     
};

#define ATTRIBUTE_REGION "regions"


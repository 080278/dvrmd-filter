#pragma once

#include <vector>
#include <string>
#include <map>
#include <cv.h>
#include <fstream>

using std::string;
using std::vector;

namespace HHV {

	struct RGBColor;
	typedef std::map<std::string, std::string> Attributes;
	typedef std::vector <CvPoint> Points;  // a list of line segments

	class MetaDataHelper
	{
	public:
		
	public:
		//For memory block
		template<class TByte, int ByteCount>
		static byte* ReadBytes(byte* pBase, TByte& value)
		{
			byte bs[ByteCount];
			memcpy(bs, pBase, ByteCount);
			value = *((TByte*)bs);
			return pBase+ByteCount;
		}

		static byte* ReadString(byte* pBase, std::string& value)
		{
			int nLen = 0;
			byte* pNext = ReadBytes<int, 4>(pBase, nLen);
			if (nLen > 0)
			{
				char* pStr = new char[nLen+1];
				memcpy(pStr, pNext, nLen);
				pStr[nLen] = 0;
				value = pStr;
				delete [] pStr;
				pNext = pNext + nLen;
			}
			return pNext;
		}

		template<class TByte, int ByteCount>
		static byte* WriteBytes(byte* pBase, TByte value)
		{
			byte bs[ByteCount];
			*((TByte*)bs) = value;
			memcpy(pBase, bs, ByteCount);
			return pBase+ByteCount;
		}

		static byte* WriteString(byte* pBase, std::string& value)
		{
			byte* pNext = WriteBytes<int, 4>(pBase, value.length());
			memcpy(pNext, value.c_str(), value.length());
			return pNext+value.length();
		}
		static int MemSize(std::string& str)
		{
			return sizeof(int) + str.length();
		}
	public:
		//For file
		static void Read(std::ifstream& is, std::string& value)
		{
			int nLen = 0;
			is >> nLen;
			if (nLen > 0)
			{
				char* pBuf = new char[nLen];
				is.read(pBuf, nLen);
				value = pBuf;
				delete[] pBuf;
			}
		}
		static void Read(std::ifstream& is, RGBColor& color);
		static void Read(std::ifstream& is, Points& pts);
		static void Read(std::ifstream& is, Attributes& attrs)
		{
			int nLen = 0;
			is >> nLen;
			if (nLen > 0)
			{
				for (int i = 0; i < nLen; ++i)
				{
					std::string key, val;
					Read(is, key);
					Read(is, val);
					attrs[key] = val;
				}
			}
		}
		template<class T>
		static void Read(std::ifstream& is, std::vector<T>& values)
		{
			int nLen = 0;
			is >> nLen;
			if (nLen > 0)
			{
				for (int i = 0; i < nLen; ++i)
				{
					T t;
					t.serialize(is);
					values.push_back(t);
				}
			}
		}

		static void Write(std::ofstream& os, std::string value)
		{
			os << value.length() << value.c_str();
		}
		static void Write(std::ofstream& os, RGBColor& color);
		static void Write(std::ofstream& os, Points& pts);
		static void Write(std::ofstream& os, Attributes& attrs)
		{
			os << (int)attrs.size();
			for (Attributes::iterator it = attrs.begin(); it != attrs.end(); ++it)
			{
				Write(os, it->first);
				Write(os, it->second);
			}
		}
		template<class T>
		static void Write(std::ofstream&os, std::vector<T>& values)
		{
			os << (int)values.size();
			for (std::vector<T>::iterator it = values.begin(); it != values.end(); ++it)
			{
				it->serialize(os);
			}
		}
	};

	struct ObjectMeta {
		std::string	         id;		// unique object identifier
		std::string           label; // object text label
		std::string           type; // object class 
		bool			 bAlerted;	// object alert tag
		CvRect			 box;
		CvScalar	     color; // color used to draw object tracking / bounding box

		int memsize()
		{
			return MetaDataHelper::MemSize(id) 
				+ MetaDataHelper::MemSize(label)
				+ MetaDataHelper::MemSize(type)
				+ 1 
				+ sizeof(CvRect)
				+ sizeof(CvScalar);
		}

		byte* FromMemory(byte* pBase)
		{
			byte* pNext = MetaDataHelper::ReadString(pBase, id);
			pNext = MetaDataHelper::ReadString(pNext, label);
			pNext = MetaDataHelper::ReadString(pNext, type);
			//MetaDataHelper::ReadBytes<bool, 1>(pNext, bAlerted);
			bAlerted = *pNext == 1;++pNext;
			pNext = MetaDataHelper::ReadBytes<int, 4>(pNext, box.x);
			pNext = MetaDataHelper::ReadBytes<int, 4>(pNext, box.y);
			pNext = MetaDataHelper::ReadBytes<int, 4>(pNext, box.width);
			pNext = MetaDataHelper::ReadBytes<int, 4>(pNext, box.height);
			pNext = MetaDataHelper::ReadBytes<CvScalar, sizeof(CvScalar)>(pNext, color);
			return pNext;
		}

		void serialize(std::ifstream& is)
		{
			MetaDataHelper::Read(is, id);
			MetaDataHelper::Read(is, label);
			MetaDataHelper::Read(is, type);
			is >> bAlerted;
			is >> box.x >> box.y >> box.width >> box.height;
			for (int i = 0; i < 4; ++i)
				is >> color.val[i];
		}

		void serialize(std::ofstream& os)
		{
			MetaDataHelper::Write(os, id);
			MetaDataHelper::Write(os, label);
			MetaDataHelper::Write(os, type);
			os << bAlerted;
			os << box.x << box.y << box.width << box.height;
			for (int i = 0; i < 4; ++i)
				os << color.val[i];
		}
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

	struct Attribute {
		std::string name;
		std::string value;
	};

	struct TextMeta {
		int x, y;
		RGBColor color;
		int size; // size in height
		std::string text;
		int memsize()
		{
			return sizeof(x) + sizeof(y) + sizeof(RGBColor) + sizeof(size) + MetaDataHelper::MemSize(text);
		}
		void serialize(std::ifstream& is)
		{
			is >> x >> y;
			MetaDataHelper::Read(is, color);
			is >> size;
			MetaDataHelper::Read(is, text);
		}
		void serialize(std::ofstream& os)
		{
			os << x << y;
			MetaDataHelper::Write(os, color);
			os << size;
			MetaDataHelper::Write(os, text);
		}
	};

	struct DrawingStyle {
		RGBColor color;
		int thickness;
		bool bFill;
		RGBColor fill_color;
		int alpha;  // 0 to 100, the actual color = alpha*color+(1-alpha)*background_color
		bool bFlash;
		
		int memsize()
		{
			return sizeof(RGBColor) + sizeof(int) + 1 + sizeof(RGBColor) + sizeof(int) + 1;
		}
		void serialize(std::ifstream& is)
		{
			MetaDataHelper::Read(is, color);
			is >> thickness;
			is >> bFill;
			MetaDataHelper::Read(is, fill_color);
			is >> alpha;
			is >> bFlash;
		}
		void serialize(std::ofstream& os)
		{
			MetaDataHelper::Write(os, color);
			os << thickness;
			os << bFill;
			MetaDataHelper::Write(os, fill_color);
			os << alpha;
			os << bFlash;
		}

	} ;

	struct PolyLine {
		RGBColor color;
		int thickness;
		int end_style; // 0 no style; 1: arrow solid, 2: arrow line
		int arrow_length;
		int arrow_width;
		Points lines;

		void serialize(std::ifstream& is)
		{
			MetaDataHelper::Read(is, color);
			is >> thickness;
			is >> end_style;
			is >> arrow_length;
			is >> arrow_width;
			MetaDataHelper::Read(is, lines);
		}
		void serialize(std::ofstream& os)
		{
			MetaDataHelper::Write(os, color);
			os << thickness;
			os << end_style;
			os << arrow_length;
			os << arrow_width;
			MetaDataHelper::Write(os, lines);
		}
	};


	struct PolygonM {
		DrawingStyle style;
		Points points;
		void serialize(std::ifstream& is)
		{
			style.serialize(is);
			MetaDataHelper::Read(is, points);
		}
		void serialize(std::ofstream& os)
		{
			style.serialize(os);
			MetaDataHelper::Write(os, points);
		}
	};

	struct ObjectType {  
		DrawingStyle style;
		// object: -1: no display, 0: line_segment, 1: rectangle, 2: ellipse
		int type; 
		int x0, y0, x1,y1;
		int x2,y2, x3, y3;  // for use with ellipse only, 4 points bounds the ellipse
		void serialize(std::ifstream& is)
		{
			style.serialize(is);
			is >> type;
			is >> x0 >> y0 >> x1 >> y1;
			is >> x2 >> y2 >> x3 >> y3;
		}
		void serialize(std::ofstream& os)
		{
			style.serialize(os);
			os << type;
			os << x0 << y0 << x1 << y1;
			os << x2 << y2 << x3 << y3;
		}
	};

	struct ObjectLoc {
		int x,y,w,h;
	};

	struct DisplayObjectMeta {
		std::string id;
		ObjectType obj;  // 
		PolyLine track;  // track of the objecct

		void serialize(std::ifstream& is)
		{
			MetaDataHelper::Read(is, id);
			obj.serialize(is);
			track.serialize(is);
		}
		void serialize(std::ofstream& os)
		{
			MetaDataHelper::Write(os, id);
			obj.serialize(os);
			track.serialize(os);
		}
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

		void serialize(std::ifstream& is) //byte* pBase)
		{
			is >> image_width;
			is >> image_height;
			MetaDataHelper::Read<DisplayObjectMeta>(is, disp_obj_list);
			MetaDataHelper::Read<PolyLine>(is, line_list);
			MetaDataHelper::Read<TextMeta>(is, text_list);
			MetaDataHelper::Read<PolygonM>(is, polygon_list);
			MetaDataHelper::Read<ObjectType>(is, gui_object_list);
		}
		void serialize(std::ofstream& os)
		{
			os << image_width;
			os << image_height;
			MetaDataHelper::Write<DisplayObjectMeta>(os, disp_obj_list);
			MetaDataHelper::Write<PolyLine>(os, line_list);
			MetaDataHelper::Write<TextMeta>(os, text_list);
			MetaDataHelper::Write<PolygonM>(os, polygon_list);
			MetaDataHelper::Write<ObjectType>(os, gui_object_list);
		}

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

		void serialize(std::ifstream& is)
		{
			displayData.serialize(is);
			MetaDataHelper::Read(is, attributes);
		}
		void serialize(std::ofstream& os)
		{
			displayData.serialize(os);
			MetaDataHelper::Write(os, attributes);
		}

		void clear()
		{
			displayData.clear();
			attributes.clear();
		}
	};

	typedef std::vector <FrameMetaData > FrameMetaDataList;   

	void MetaDataHelper::Read(std::ifstream& is, RGBColor& color)
	{
		is >> color.r >> color.g >> color.b;
	}
	void MetaDataHelper::Write(std::ofstream& os, RGBColor& color)
	{
		os << color.r << color.g << color.b;
	}
	void MetaDataHelper::Read(std::ifstream& is, Points& pts)
	{
		int nLen = 0;
		is >> nLen;
		if (nLen > 0)
		{
			for (int i = 0; i < nLen; ++i)
			{
				CvPoint pt;
				is >> pt.x >> pt.y;
				pts.push_back(pt);
			}
		}
	}
	void MetaDataHelper::Write(std::ofstream& os, Points& pts)
	{
		os << (int)pts.size();
		if (pts.size() > 0)
		{
			for (Points::iterator it = pts.begin(); it != pts.end(); ++it)
			{
				os << it->x << it->y;
			}
		}
	}

};

#define ATTRIBUTE_REGION "regions"


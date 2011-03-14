#pragma once

#include <vector>
#include <string>
#include <map>
#include <cv.h>
#include <fstream>

using std::string;
using std::vector;

#define INT_SIZE	4
#define BOOL_SIZE	1

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
			memset(&value, 0, sizeof(TByte));
			memcpy(&value, pBase, ByteCount);

			return pBase+ByteCount;
		}

		static byte* ReadBool(byte* pBase, bool& value)
		{
			value = *pBase == 1;

			return pBase+1;
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

		static byte* ReadPoints(byte* pBase, Points& pts)
		{
			int nLen = 0;
			byte* pNext = ReadBytes<int, 4>(pBase, nLen);
			if (nLen > 0)
			{
				for (int i = 0; i < nLen; ++i)
				{
					CvPoint pt;
					pNext = ReadBytes<int, 4>(pNext, pt.x);
					pNext = ReadBytes<int, 4>(pNext, pt.y);

					pts.push_back(pt);
				}
			}
			return pNext;
		}

		template<class T>
		static byte* Read(byte* pBase, std::vector<T>& values)
		{
			int nLen = 0;
			byte* pNext = ReadBytes<int, 4>(pBase, nLen);
			if (nLen > 0)
			{
				for (int i = 0; i < nLen; ++i)
				{
					T t;
					pNext = t.FromMemory(pBase);
					values.push_back(t);
				}
			}

			return pNext;
		}
		template<class T>
		static byte* Write(byte* pBase, std::vector<T>& values)
		{
			byte* pNext = WriteBytes<int, 4>(pBase, (int)values.size());
			for (std::vector<T>::iterator it = values.begin(); it != values.end(); ++it)
			{
				pNext = it->ToMemory(pNext);
			}

			return pNext;
		}
		static byte* WritePoints(byte* pBase, Points& pts)
		{
			byte* pNext = WriteBytes<int, 4>(pBase, (int)pts.size());
			if (pts.size() > 0)
			{
				for (Points::iterator it = pts.begin(); it != pts.end(); ++it)
				{
					pNext = WriteBytes<int, 4>(pNext, it->x);
					pNext = WriteBytes<int, 4>(pNext, it->y);
				}
			}
			return pNext;
		}
		template<class TByte, int ByteCount>
		static byte* WriteBytes(byte* pBase, TByte value)
		{
			memcpy(pBase, &value, ByteCount);
			return pBase+ByteCount;
		}

		static byte* WriteString(byte* pBase, std::string value)
		{
			byte* pNext = WriteBytes<int, 4>(pBase, value.length());
			memcpy(pNext, value.c_str(), value.length());
			return pNext+value.length();
		}
		static byte* WriteBool(byte* pBase, bool value)
		{
			*pBase = value ? 1 : 0;

			return pBase + 1;
		}

		static int MemSize(std::string str)
		{
			return 4 + str.length();
		}
		static int MemSize(Points& pts)
		{
			return 4 + pts.size() * 8;
		}
		template<class T>
		static int MemSize(std::vector<T>& values)
		{
			int nSize = 4;
			for (std::vector<T>::iterator it = values.begin(); it != values.end(); ++it)
			{
				nSize += it->memsize();
			}

			return nSize;
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
				+ BOOL_SIZE 
				+ INT_SIZE * 4
				+ sizeof(CvScalar);
		}

		byte* FromMemory(byte* pBase)
		{
			byte* pNext = MetaDataHelper::ReadString(pBase, id);
			pNext = MetaDataHelper::ReadString(pNext, label);
			pNext = MetaDataHelper::ReadString(pNext, type);
			pNext = MetaDataHelper::ReadBool(pNext, bAlerted);
			pNext = MetaDataHelper::ReadBytes<int, 4>(pNext, box.x);
			pNext = MetaDataHelper::ReadBytes<int, 4>(pNext, box.y);
			pNext = MetaDataHelper::ReadBytes<int, 4>(pNext, box.width);
			pNext = MetaDataHelper::ReadBytes<int, 4>(pNext, box.height);
			pNext = MetaDataHelper::ReadBytes<CvScalar, sizeof(CvScalar)>(pNext, color);
			return pNext;
		}

		byte* ToMemory(byte* pBase)
		{
			byte* pNext = MetaDataHelper::WriteString(pBase, id);
			pNext = MetaDataHelper::WriteString(pNext, label);
			pNext = MetaDataHelper::WriteString(pNext, type);
			pNext = MetaDataHelper::WriteBool(pNext, bAlerted);
			pNext = MetaDataHelper::WriteBytes<int, 4>(pNext, box.x);
			pNext = MetaDataHelper::WriteBytes<int, 4>(pNext, box.y);
			pNext = MetaDataHelper::WriteBytes<int, 4>(pNext, box.width);
			pNext = MetaDataHelper::WriteBytes<int, 4>(pNext, box.height);
			pNext = MetaDataHelper::WriteBytes<CvScalar, sizeof(CvScalar)>(pNext, color);

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
			return INT_SIZE + INT_SIZE + sizeof(RGBColor) + INT_SIZE + MetaDataHelper::MemSize(text);
		}

		byte* FromMemory(byte* pBase)
		{
			byte* pNext = MetaDataHelper::ReadBytes<int, 4>(pBase, x);
			pNext = MetaDataHelper::ReadBytes<int, 4>(pNext, y);
			pNext = MetaDataHelper::ReadBytes<RGBColor, sizeof(RGBColor)>(pNext, color);
			pNext = MetaDataHelper::ReadBytes<int, 4>(pNext, size);
			pNext = MetaDataHelper::ReadString(pNext, text);
			return pNext;
		}

		byte* ToMemory(byte* pBase)
		{
			byte* pNext = MetaDataHelper::WriteBytes<int, 4>(pBase, x);
			pNext = MetaDataHelper::WriteBytes<int, 4>(pNext, y);
			pNext = MetaDataHelper::WriteBytes<RGBColor, sizeof(RGBColor)>(pNext, color);
			pNext = MetaDataHelper::WriteBytes<int, 4>(pNext, size);
			pNext = MetaDataHelper::WriteString(pNext, text);
			return pNext;
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
			return sizeof(RGBColor) + INT_SIZE + BOOL_SIZE + sizeof(RGBColor) + INT_SIZE + BOOL_SIZE;
		}
		byte* FromMemory(byte* pBase)
		{
			byte* pNext = MetaDataHelper::ReadBytes<RGBColor, sizeof(RGBColor)>(pBase, color);
			pNext = MetaDataHelper::ReadBytes<int, 4>(pNext, thickness);
			pNext = MetaDataHelper::ReadBool(pNext, bFill);
			pNext = MetaDataHelper::ReadBytes<RGBColor, sizeof(RGBColor)>(pNext, fill_color);
			pNext = MetaDataHelper::ReadBytes<int, 4>(pNext, alpha);
			pNext = MetaDataHelper::ReadBool(pNext, bFlash);
			return pNext;
		}

		byte* ToMemory(byte* pBase)
		{
			byte* pNext = MetaDataHelper::WriteBytes<RGBColor, sizeof(RGBColor)>(pBase, color);
			pNext = MetaDataHelper::WriteBytes<int, 4>(pNext, thickness);
			pNext = MetaDataHelper::WriteBool(pNext, bFill);
			pNext = MetaDataHelper::WriteBytes<RGBColor, sizeof(RGBColor)>(pNext, fill_color);
			pNext = MetaDataHelper::WriteBytes<int, 4>(pNext, alpha);
			pNext = MetaDataHelper::WriteBool(pNext, bFlash);
			return pNext;
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
		int memsize()
		{
			return sizeof(RGBColor) + 
				   INT_SIZE +
				   INT_SIZE +
				   INT_SIZE +
				   INT_SIZE +
				   MetaDataHelper::MemSize(lines);
		}
		byte* FromMemory(byte* pBase)
		{
			byte* pNext = MetaDataHelper::ReadBytes<RGBColor, sizeof(RGBColor)>(pBase, color);
			pNext = MetaDataHelper::ReadBytes<int, 4>(pNext, thickness);
			pNext = MetaDataHelper::ReadBytes<int, 4>(pNext, end_style);
			pNext = MetaDataHelper::ReadBytes<int, 4>(pNext, arrow_length);
			pNext = MetaDataHelper::ReadBytes<int, 4>(pNext, arrow_width);
			pNext = MetaDataHelper::ReadPoints(pNext, lines);
			return pNext;
		}

		byte* ToMemory(byte* pBase)
		{
			byte* pNext = MetaDataHelper::WriteBytes<RGBColor, sizeof(RGBColor)>(pBase, color);
			pNext = MetaDataHelper::WriteBytes<int, 4>(pNext, thickness);
			pNext = MetaDataHelper::WriteBytes<int, 4>(pNext, end_style);
			pNext = MetaDataHelper::WriteBytes<int, 4>(pNext, arrow_length);
			pNext = MetaDataHelper::WriteBytes<int, 4>(pNext, arrow_width);
			pNext = MetaDataHelper::WritePoints(pNext, lines);
			return pNext;
		}
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
		int memsize()
		{
			return style.memsize() + MetaDataHelper::MemSize(points);
		}
		byte* FromMemory(byte* pBase)
		{
			byte* pNext = style.FromMemory(pBase);
			pNext = MetaDataHelper::ReadPoints(pNext, points);

			return pNext;
		}
		byte* ToMemory(byte* pBase)
		{
			byte* pNext = style.ToMemory(pBase);
			pNext = MetaDataHelper::WritePoints(pNext, points);

			return pNext;
		}
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

		int memsize()
		{
			return style.memsize() + INT_SIZE +
				INT_SIZE + INT_SIZE + INT_SIZE + INT_SIZE +
				INT_SIZE + INT_SIZE + INT_SIZE + INT_SIZE;
		}
		byte* FromMemory(byte* pBase)
		{
			byte* pNext = style.FromMemory(pBase);
			pNext = MetaDataHelper::ReadBytes<int, 4>(pNext, type);
			pNext = MetaDataHelper::ReadBytes<int, 4>(pNext, x0);
			pNext = MetaDataHelper::ReadBytes<int, 4>(pNext, y0);
			pNext = MetaDataHelper::ReadBytes<int, 4>(pNext, x1);
			pNext = MetaDataHelper::ReadBytes<int, 4>(pNext, y1);
			pNext = MetaDataHelper::ReadBytes<int, 4>(pNext, x2);
			pNext = MetaDataHelper::ReadBytes<int, 4>(pNext, y2);
			pNext = MetaDataHelper::ReadBytes<int, 4>(pNext, x3);
			pNext = MetaDataHelper::ReadBytes<int, 4>(pNext, y3);

			return pNext;
		}
		byte* ToMemory(byte* pBase)
		{
			byte* pNext = style.ToMemory(pBase);
			pNext = MetaDataHelper::WriteBytes<int, 4>(pNext, type);
			pNext = MetaDataHelper::WriteBytes<int, 4>(pNext, x0);
			pNext = MetaDataHelper::WriteBytes<int, 4>(pNext, y0);
			pNext = MetaDataHelper::WriteBytes<int, 4>(pNext, x1);
			pNext = MetaDataHelper::WriteBytes<int, 4>(pNext, y1);
			pNext = MetaDataHelper::WriteBytes<int, 4>(pNext, x2);
			pNext = MetaDataHelper::WriteBytes<int, 4>(pNext, y2);
			pNext = MetaDataHelper::WriteBytes<int, 4>(pNext, x3);
			pNext = MetaDataHelper::WriteBytes<int, 4>(pNext, y3);

			return pNext;
		}

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

		int memsize()
		{
			return MetaDataHelper::MemSize(id) +
					obj.memsize() +
					track.memsize();
		}
		byte* FromMemory(byte* pBase)
		{
			byte* pNext = MetaDataHelper::ReadString(pBase, id);
			pNext = obj.FromMemory(pNext);
			pNext = track.FromMemory(pNext);

			return pNext;
		}
		byte* ToMemory(byte* pBase)
		{
			byte* pNext = MetaDataHelper::WriteString(pBase, id);
			pNext = obj.ToMemory(pNext);
			pNext = track.ToMemory(pNext);

			return pNext;
		}
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

		int memsize()
		{
			
			return  INT_SIZE +
					INT_SIZE +
					MetaDataHelper::MemSize<DisplayObjectMeta>(disp_obj_list) +
					MetaDataHelper::MemSize<PolyLine>(line_list) +
					MetaDataHelper::MemSize<TextMeta>(text_list) +
					MetaDataHelper::MemSize<PolygonM>(polygon_list) +
					MetaDataHelper::MemSize<ObjectType>(gui_object_list);
		}

		byte* FromMemory(byte* pBase)
		{
			byte* pNext = MetaDataHelper::ReadBytes<int, 4>(pBase, image_width);
			pNext = MetaDataHelper::ReadBytes<int, 4>(pNext, image_height);
			pNext = MetaDataHelper::Read<DisplayObjectMeta>(pNext, disp_obj_list);
			pNext = MetaDataHelper::Read<PolyLine>(pNext, line_list);
			pNext = MetaDataHelper::Read<TextMeta>(pNext, text_list);
			pNext = MetaDataHelper::Read<PolygonM>(pNext, polygon_list);
			pNext = MetaDataHelper::Read<ObjectType>(pNext, gui_object_list);

			return pNext;
		}
		byte* ToMemory(byte* pBase)
		{
			byte* pNext = MetaDataHelper::WriteBytes<int, 4>(pBase, image_width);
			pNext = MetaDataHelper::WriteBytes<int, 4>(pNext, image_height);
			pNext = MetaDataHelper::Write<DisplayObjectMeta>(pNext, disp_obj_list);
			pNext = MetaDataHelper::Write<PolyLine>(pNext, line_list);
			pNext = MetaDataHelper::Write<TextMeta>(pNext, text_list);
			pNext = MetaDataHelper::Write<PolygonM>(pNext, polygon_list);
			pNext = MetaDataHelper::Write<ObjectType>(pNext, gui_object_list);

			return pNext;
		}
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

		int memsize()
		{
			int size = displayData.memsize();
			size += 4;

			for (Attributes::iterator it = attributes.begin(); it != attributes.end(); ++it)
			{
				size += MetaDataHelper::MemSize(it->first);
				size += MetaDataHelper::MemSize(it->second);
			}
			
			return size;
		}

		byte* FromMemory(byte* pBase)
		{
			byte* pNext = displayData.FromMemory(pBase);
			int nSize = 0;
			pNext = MetaDataHelper::ReadBytes<int, 4>(pNext, nSize);
			if (nSize > 0)
			{
				for (int i = 0; i <nSize; ++i)
				{
					std::string key, val;
					pNext = MetaDataHelper::ReadString(pNext, key);
					pNext = MetaDataHelper::ReadString(pNext, val);

					attributes[key] = val;
				}
			}
			return pNext;
		}
		byte* ToMemory(byte* pBase)
		{
			byte* pNext = displayData.ToMemory(pBase);
			pNext = MetaDataHelper::WriteBytes<int, 4>(pNext, (int)attributes.size());
			for(Attributes::iterator it = attributes.begin(); it != attributes.end(); ++it)
			{
				pNext = MetaDataHelper::WriteString(pNext, it->first);
				pNext = MetaDataHelper::WriteString(pNext, it->second);
			}

			return pNext;
		}
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


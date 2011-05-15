// YuvRgbConverter.h: interface for the CYuvRgbConverter class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_YUVRGBCONVERTER_H__349EDDAE_F788_4238_A27C_3CDE8798F2BB__INCLUDED_)
#define AFX_YUVRGBCONVERTER_H__349EDDAE_F788_4238_A27C_3CDE8798F2BB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//extern "C" void YUV420ToRGB32(  BYTE *dst, int dstride, BYTE *y,  BYTE *u , BYTE *v , int ystride, int uvstride,int width, int height); 
extern "C" void YUV420ToRGB24(  BYTE *dst, int dstride, BYTE *y,  BYTE *u , BYTE *v , int ystride, int uvstride,int width, int height); 
//extern "C" void RGB32ToYV12(BYTE * const y_out,BYTE * const u_out,	BYTE * const v_out, const BYTE * const src,
//					  						const UINT width,const UINT height,const UINT stride);

extern "C" void yv12_to_rgb32_mmx(BYTE *dst,
								  int dst_stride,
								  BYTE *y_src,
								  BYTE *u_src,
								  BYTE *v_src, 
								  int y_stride, int uv_stride,
								  int width, int height); 

extern "C" void _RGB32ToYV12(BYTE * const y_out,
							 BYTE * const u_out,
							 BYTE * const v_out,
							 const BYTE * const src,
							 const unsigned int width,
							 const unsigned int height,
							 const unsigned int stride);


class CYuvRgbConverter  
{
public:
	CYuvRgbConverter();
	virtual ~CYuvRgbConverter();

	static void yuv420toyuv422(BYTE* lpSrcY, int SrcPitch,	BYTE* lpSrcU,BYTE* lpSrcV, 
		int stride_uv, BYTE* lpDst, int SrcWidth, int SrcHeight,unsigned int DstPitch);

	static void yv12_to_rgb32_mmx(BYTE *dst,
		int dst_stride,
		BYTE *y_src,
		BYTE *u_src,
		BYTE *v_src, 
		int y_stride, int uv_stride,
		int width, int height); 

	static void _RGB32ToYV12(BYTE * const y_out,
							 BYTE * const u_out,
							 BYTE * const v_out,
							 const BYTE * const src,
							 const unsigned int width,
							 const unsigned int height,
							 const unsigned int stride);

};

#endif // !defined(AFX_YUVRGBCONVERTER_H__349EDDAE_F788_4238_A27C_3CDE8798F2BB__INCLUDED_)

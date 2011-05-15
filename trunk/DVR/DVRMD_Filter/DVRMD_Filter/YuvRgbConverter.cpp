// YuvRgbConverter.cpp: implementation of the CYuvRgbConverter class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "YuvRgbConverter.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CYuvRgbConverter::CYuvRgbConverter()
{

}

CYuvRgbConverter::~CYuvRgbConverter()
{

}

//高速MMX转换YUV函数
//这个地方的YUV422指UYVY422
void CYuvRgbConverter::yuv420toyuv422(BYTE* lpSrcY, 
									  int SrcPitch,
									  BYTE* lpSrcU,
									  BYTE* lpSrcV, 
									  int stride_uv, 
									  BYTE* lpDst, 
									  int SrcWidth, 
									  int SrcHeight,
									  unsigned int DstPitch
									 )
{

	int SrcStride = SrcPitch + SrcPitch - SrcWidth;	
	int SrcStrideU = (SrcPitch - SrcWidth)>>1;
	int DstStride =(DstPitch - SrcWidth)<<1;

//	TRACE("\nSrcStride = %d  SrcStrideU = %d DestStride = %d DstPitch = %d",SrcStride,SrcStrideU,DstStride,DstPitch);

	__asm
	{
		push ebx
			
			mov edi , [lpDst]
			mov esi , [lpSrcY]
			mov eax , [lpSrcU]
			mov ebx , [lpSrcV]
			mov ecx , [SrcHeight]
			mov edx , [SrcWidth]
cyc: 
		movq mm2 , qword ptr [eax] //u
			movq mm3 , qword ptr [ebx] //v
			
			movq mm0 , qword ptr [esi] //y1
			movq mm1 , qword ptr [esi+8] //y2
			
			movq mm4 , mm2
			punpcklbw mm2 , mm3 // uv1
			punpckhbw mm4 , mm3 // uv2
		
			movq mm6 , mm2
			movq mm7 , mm4

			movq mm3 , mm2
			movq mm5 , mm4

			punpcklbw mm2 , mm0 // uyvy1
			punpckhbw mm3 , mm0 // uyvy2
			punpcklbw mm4 , mm1 // uyvy3
			punpckhbw mm5 , mm1 // uyvy4
			
			movq qword ptr [edi] , mm2
			movq qword ptr [edi+8] , mm3
			movq qword ptr [edi+16] , mm4
			movq qword ptr [edi+24] , mm5
			
			add esi , [SrcPitch]
			add edi , [DstPitch]
			
			movq mm0 , qword ptr [esi] //y1
			movq mm1 , qword ptr [esi+8] //y2

			movq mm2, mm6 
			movq mm4, mm7 

			movq mm3 , mm2
			movq mm5 , mm4

			punpcklbw mm2 , mm0 // uyvy1
			punpckhbw mm3 , mm0 // uyvy2
			punpcklbw mm4 , mm1 // uyvy3
			punpckhbw mm5 , mm1 // uyvy4
			
			movq qword ptr [edi] , mm2
			movq qword ptr [edi+8] , mm3
			movq qword ptr [edi+16] , mm4
			movq qword ptr [edi+24] , mm5

			sub esi , [SrcPitch]
			sub edi , [DstPitch]
			
			add eax , 8
			add ebx , 8
			add esi , 16
			add edi , 32
			
			sub edx,16			
			ja cyc
			
			mov edx,[SrcWidth]
			
			add esi , [SrcStride]
			add eax , [SrcStrideU]
			add ebx , [SrcStrideU]
			add edi , [DstStride]
			
			sub ecx,2
			ja cyc
			emms
			
			pop ebx
	}
}

void CYuvRgbConverter::yv12_to_rgb32_mmx(BYTE *dst,
  int dst_stride,
  BYTE *y_src,
  BYTE *u_src,
  BYTE *v_src, 
  int y_stride, int uv_stride,
  int width, int height)
{
	::yv12_to_rgb32_mmx( dst, dst_stride, y_src, u_src, v_src, y_stride, uv_stride, width, height );
}

void CYuvRgbConverter::_RGB32ToYV12(BYTE * const y_out,
  BYTE * const u_out,
  BYTE * const v_out,
  const BYTE * const src,
  const unsigned int width,
  const unsigned int height,
  const unsigned int stride)
{
	::_RGB32ToYV12(y_out, u_out, v_out, src, width, height, stride);
}

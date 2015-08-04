// Copyright 2014 PDFium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

// Original code copyright 2014 Foxit Software Inc. http://www.foxitsoftware.com

#ifndef _BC_WRITER_H_
#define _BC_WRITER_H_
class CBC_Writer;
class CBC_Writer {
 public:
  CBC_Writer();
  virtual ~CBC_Writer();
  virtual uint8_t* Encode(const CFX_ByteString& contents,
                          BCFORMAT format,
                          int32_t& outWidth,
                          int32_t& outHeight,
                          int32_t& e) = 0;
  virtual uint8_t* Encode(const CFX_ByteString& contents,
                          BCFORMAT format,
                          int32_t& outWidth,
                          int32_t& outHeight,
                          int32_t hints,
                          int32_t& e) = 0;
  virtual FX_BOOL SetCharEncoding(int32_t encoding);
  virtual FX_BOOL SetModuleHeight(int32_t moduleHeight);
  virtual FX_BOOL SetModuleWidth(int32_t moduleWidth);
  virtual FX_BOOL SetHeight(int32_t height);
  virtual FX_BOOL SetWidth(int32_t width);
  virtual void SetBackgroundColor(FX_ARGB backgroundColor);
  virtual void SetBarcodeColor(FX_ARGB foregroundColor);

 protected:
  CFX_DIBitmap* CreateDIBitmap(int32_t width, int32_t height);
  int32_t m_CharEncoding;
  int32_t m_ModuleHeight;
  int32_t m_ModuleWidth;
  int32_t m_Height;
  int32_t m_Width;
  FXDIB_Format m_colorSpace;
  FX_ARGB m_barColor;
  FX_ARGB m_backgroundColor;
};
#endif

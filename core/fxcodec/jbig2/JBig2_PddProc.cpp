// Copyright 2015 PDFium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

// Original code copyright 2014 Foxit Software Inc. http://www.foxitsoftware.com

#include "core/fxcodec/jbig2/JBig2_PddProc.h"

#include <memory>

#include "core/fxcodec/jbig2/JBig2_GrdProc.h"
#include "core/fxcodec/jbig2/JBig2_Image.h"
#include "core/fxcodec/jbig2/JBig2_PatternDict.h"
#include "third_party/base/ptr_util.h"

std::unique_ptr<CJBig2_PatternDict> CJBig2_PDDProc::DecodeArith(
    CJBig2_ArithDecoder* pArithDecoder,
    JBig2ArithCtx* gbContext,
    PauseIndicatorIface* pPause) {
  uint32_t GRAY;
  std::unique_ptr<CJBig2_Image> BHDC;
  auto pDict = pdfium::MakeUnique<CJBig2_PatternDict>(GRAYMAX + 1);

  auto pGRD = pdfium::MakeUnique<CJBig2_GRDProc>();
  pGRD->MMR = HDMMR;
  pGRD->GBW = (GRAYMAX + 1) * HDPW;
  pGRD->GBH = HDPH;
  pGRD->GBTEMPLATE = HDTEMPLATE;
  pGRD->TPGDON = 0;
  pGRD->USESKIP = 0;
  pGRD->GBAT[0] = -(int32_t)HDPW;
  pGRD->GBAT[1] = 0;
  if (pGRD->GBTEMPLATE == 0) {
    pGRD->GBAT[2] = -3;
    pGRD->GBAT[3] = -1;
    pGRD->GBAT[4] = 2;
    pGRD->GBAT[5] = -2;
    pGRD->GBAT[6] = -2;
    pGRD->GBAT[7] = -2;
  }
  CJBig2_GRDProc::ProgressiveArithDecodeState state;
  state.pImage = &BHDC;
  state.pArithDecoder = pArithDecoder;
  state.gbContext = gbContext;
  state.pPause = nullptr;

  FXCODEC_STATUS status = pGRD->StartDecodeArith(&state);
  state.pPause = pPause;
  while (status == FXCODEC_STATUS_DECODE_TOBECONTINUE)
    status = pGRD->ContinueDecode(&state);
  if (!BHDC)
    return nullptr;

  GRAY = 0;
  while (GRAY <= GRAYMAX) {
    pDict->HDPATS[GRAY] = BHDC->subImage(HDPW * GRAY, 0, HDPW, HDPH);
    GRAY = GRAY + 1;
  }
  return pDict;
}

std::unique_ptr<CJBig2_PatternDict> CJBig2_PDDProc::DecodeMMR(
    CJBig2_BitStream* pStream) {
  uint32_t GRAY;
  std::unique_ptr<CJBig2_Image> BHDC;
  auto pDict = pdfium::MakeUnique<CJBig2_PatternDict>(GRAYMAX + 1);

  auto pGRD = pdfium::MakeUnique<CJBig2_GRDProc>();
  pGRD->MMR = HDMMR;
  pGRD->GBW = (GRAYMAX + 1) * HDPW;
  pGRD->GBH = HDPH;
  pGRD->StartDecodeMMR(&BHDC, pStream);
  if (!BHDC)
    return nullptr;

  GRAY = 0;
  while (GRAY <= GRAYMAX) {
    pDict->HDPATS[GRAY] = BHDC->subImage(HDPW * GRAY, 0, HDPW, HDPH);
    GRAY = GRAY + 1;
  }
  return pDict;
}

// Copyright 2017 PDFium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

// Original code copyright 2014 Foxit Software Inc. http://www.foxitsoftware.com

#include "xfa/fxfa/parser/cxfa_update.h"

#include "fxjs/xfa/cjx_update.h"
#include "third_party/base/ptr_util.h"

namespace {

const CXFA_Node::AttributeData kUpdateAttributeData[] = {
    {XFA_Attribute::Id, XFA_AttributeType::CData, nullptr},
    {XFA_Attribute::Name, XFA_AttributeType::CData, nullptr},
    {XFA_Attribute::Use, XFA_AttributeType::CData, nullptr},
    {XFA_Attribute::Usehref, XFA_AttributeType::CData, nullptr},
    {XFA_Attribute::Unknown, XFA_AttributeType::Integer, nullptr}};

constexpr wchar_t kUpdateName[] = L"update";

}  // namespace

CXFA_Update::CXFA_Update(CXFA_Document* doc, XFA_PacketType packet)
    : CXFA_Node(doc,
                packet,
                XFA_XDPPACKET_SourceSet,
                XFA_ObjectType::TextNode,
                XFA_Element::Update,
                nullptr,
                kUpdateAttributeData,
                kUpdateName,
                pdfium::MakeUnique<CJX_Update>(this)) {}

CXFA_Update::~CXFA_Update() {}

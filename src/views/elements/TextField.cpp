#include "TextField.h"

TextField::TextField() {
  changed = false;
  umlautoffsetfactor = 0.2;
  umlautoffset = 0;
  textContent = "";

  setFontSize(15);
  setSize(20, 10);
}

TextField::~TextField() {
}

void TextField::setup() {
}

void TextField::update() {
  if (changed) {
    renderText();
  }
}

void TextField::_draw() {
  font->draw(textContent, 0, 0);
  return;

  if (!textImage.isAllocated()) return;
  
  // TODO: find a solution here... sometimes text-alpha is not properly blended
  ofSetColor(getCombinedAlpha(), getCombinedAlpha(), getCombinedAlpha(), getCombinedAlpha());
  glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA); // To avoid ugly dark eges in alpha blending
  // glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  // glBlendFunc(GL_SOURCE1_ALPHA, GL_ONE_MINUS_SRC_ALPHA); // To avoid ugly dark eges in alpha blending
  textImage.draw(0, -umlautoffset);
}

void TextField::updateFontDescription() {
  if (fontFile.empty() || !fontSize) return;
  font = ofxSmartFont::add(fontFile, fontSize);
}

void TextField::setText(string _text) {
  if (_text == textContent)
    return;
  textContent = _text;
  changed = true;
}

void TextField::setFontFile(string _fontFile) {
  if (_fontFile == fontFile)
    return;
  fontFile = _fontFile;
  updateFontDescription();
}

void TextField::setFontSize(float _fontSize) {
  if (_fontSize == fontSize)
    return;
  fontSize = _fontSize;

  umlautoffset = fontSize * umlautoffsetfactor;
  updateFontDescription();
}

void TextField::setSize(float _width, float _height) {
  BasicScreenObject::setSize(_width, _height);
  changed = true;
}

ofPoint TextField::getTextBounds() {
  auto rect = font->rect(textContent, getX(), getY());
  return ofVec2f(rect.width, rect.height);

  if (changed) {
    renderText();
  }
  return bounds;
}

string TextField::getText() {
  return textContent;
}

void TextField::renderText() {
  // Note: this is mostly unncessary now as ofxParagraph has its own internal render()

//  string pre = "";
//  string post = "";
//
//  if (letterSpacing != 0) {
//    pre = "<span letter_spacing=\"" + ofToString(letterSpacing) + "\" >";
//    post = "</span>";
//  }

//  layout->context->clear();
//  layout->setFontDescription(*fd, antialiasType);
//  layout->setTextColor(col+or.r / 255.0f, color.g / 255.0f, color.b / 255.0f, 1);
//  layout->setSpacing(lineSpacing);
//  layout->setIndent(indent);
//  layout->setMarkup(pre + textContent + post);
//  layout->setTabs(tabs);
//  layout->setPangoAlign(textAlign);
//  layout->show();
//  bounds = layout->getPixelSize();
  bounds = getTextBounds();
  changed = false;

  if (bounds.y != height) {
    setSize(width, bounds.y);
  }

//  textImage.setFromPixels(layout->context->getSurface()->getPixels(), width, height + umlautoffset, OF_IMAGE_COLOR_ALPHA, true);

  if (!changed)
    ofNotifyEvent(textRenderedEvent, myEventArgs, this);
}

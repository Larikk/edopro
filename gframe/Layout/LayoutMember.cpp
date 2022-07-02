#include "LayoutMember.h"
#include "ILayout.h"

namespace irr {
namespace gui {

LayoutMember* createLayoutMember(IGUIElement* element, bool isLayout) {
	return new LayoutMember(element, isLayout);
}

LayoutMember::LayoutMember(IGUIElement* element, bool isLayout) {
    this->element = element;
	this->isLayout = isLayout;
}

LayoutMember::~LayoutMember() {
    delete this->element;
}

void LayoutMember::setRelativePosition(const irr::core::recti& bounds) {
	if (this->isLayout) {
		ILayout* e = (ILayout*) this->element;
		e->setRelativePosition(bounds);
	} else {
		this->element->setRelativePosition(bounds);
	}
}

IGUIElement* LayoutMember::getGUIElement() {
	return this->element;
}

s32 LayoutMember::getFixedWidth() {
	return this->fixedWidth;
}

s32 LayoutMember::getFixedHeigth() {
	return this->fixedHeight;
}

s32 LayoutMember::getMinWidth() {
	return this->minWidth;
}

s32 LayoutMember::getMinHeigth() {
	return this->minHeight;
}

s32 LayoutMember::getMaxWidth() {
	return this->maxWidth;
}

s32 LayoutMember::getMaxHeigth() {
	return this->maxHeigth;
}

float LayoutMember::getPreferredRelativeWidth() {
	return this->preferredRelativeWidth;
}

float LayoutMember::getPreferredRelativeHeight() {
	return this->preferredRelativeHeight;
}

bool LayoutMember::getScaling() {
	return this->isScaling;
}

LayoutMember* LayoutMember::withFixedWidth(s32 w) {
	this->fixedWidth = w;
	return this;
}

LayoutMember* LayoutMember::withFixedHeight(s32 h) {
	this->fixedHeight = h;
	return this;
}

LayoutMember* LayoutMember::withMinWidth(s32 w) {
	this->minWidth = w;
	return this;
}

LayoutMember* LayoutMember::withMinHeight(s32 h) {
	this->minHeight = h;
	return this;
}

LayoutMember* LayoutMember::withMaxWidth(s32 w) {
	this->maxWidth = w;
	return this;
}

LayoutMember* LayoutMember::withMaxHeight(s32 h) {
	this->maxHeigth = h;
	return this;
}

LayoutMember* LayoutMember::withPreferredRelativeWidth(float w) {
	this->preferredRelativeWidth = w;
	return this;
}

LayoutMember* LayoutMember::withPreferredRelativeHeight(float h) {
	this->preferredRelativeHeight = h;
	return this;
}

}
}

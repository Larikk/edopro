#include "ILayout.h"
#include <stdexcept>

namespace irr {
namespace gui {


ILayout::ILayout(IGUIEnvironment* environment, IGUIElement* parent, s32 id) :
	CGUICustomText(L"", false, environment, parent, id, irr::core::recti(0, 0, 0, 0), false) {};

ILayout::~ILayout() {
	for (LayoutMember* member : this->layoutMembers) {
		CGUICustomText::removeChild(member->getGUIElement());
		delete member;
	}
}

void ILayout::addChild(IGUIElement* child) {
	this->addChildToEnd(child);
}

void ILayout::addChildToEnd(IGUIElement* child) {
	throw new std::runtime_error("Adding a child to a layout must be done via addLayoutMember().");
}

void ILayout::addLayoutMember(LayoutMember* member) {
	CGUICustomText::addChild(member->getGUIElement());
	this->layoutMembers.push_back(member);
}

void ILayout::setRelativePosition(const core::recti& r) {
	CGUICustomText::setRelativePosition(r);
}


}
}

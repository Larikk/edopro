#include "HorizontalLayout.h"

namespace irr {
namespace gui {

HorizontalLayout::HorizontalLayout(IGUIEnvironment* environment, IGUIElement* parent, s32 id) :
	IDirectionalLayout(environment, parent, id) {}

HorizontalLayout::~HorizontalLayout() {}

s32 HorizontalLayout::getParallelPadding() {
	return this->hPadding;
}

s32 HorizontalLayout::getOrthogonalPadding() {
	return this->vPadding;
}

s32 HorizontalLayout::fetchMembersFixedLength(LayoutMember* member) {
	return member->getFixedWidth();
}

s32 HorizontalLayout::fetchMembersMinLength(LayoutMember* member) {
	return member->getMinWidth();
}

s32 HorizontalLayout::fetchMembersMaxLength(LayoutMember* member) {
	return member->getMaxWidth();
}

float HorizontalLayout::fetchMembersPreferredRelativeLength(LayoutMember* member) {
	return member->getPreferredRelativeWidth();
}

s32 HorizontalLayout::fetchBoundsLength(const irr::core::recti& bounds) {
	return bounds.getWidth();
}

s32 HorizontalLayout::fetchOrthogonalBoundsLength(const irr::core::recti& bounds) {
	return bounds.getHeight();
}

irr::core::recti HorizontalLayout::createBoundsForMember(s32 a1, s32 a2) {
	s32 y1 = this->vPadding;
	s32 y2 = this->getRelativePosition().getHeight() - y1;
	return irr::core::recti(a1, y1, a2, y2);
}

}
}

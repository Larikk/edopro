#include "VerticalLayout.h"

namespace irr {
namespace gui {

VerticalLayout::VerticalLayout(IGUIEnvironment* environment, IGUIElement* parent, s32 id) :
	IDirectionalLayout(environment, parent, id) {}

VerticalLayout::~VerticalLayout() {}

s32 VerticalLayout::getParallelPadding() {
	return this->vPadding;
}

s32 VerticalLayout::getOrthogonalPadding() {
	return this->hPadding;
}

s32 VerticalLayout::fetchMembersFixedLength(LayoutMember* member) {
	return member->getFixedHeigth();
}

s32 VerticalLayout::fetchMembersMinLength(LayoutMember* member) {
	return member->getMinHeigth();
}

s32 VerticalLayout::fetchMembersMaxLength(LayoutMember* member) {
	return member->getMaxHeigth();
}

float VerticalLayout::fetchMembersPreferredRelativeLength(LayoutMember* member) {
	return member->getPreferredRelativeHeight();
}

s32 VerticalLayout::fetchBoundsLength(const irr::core::recti& bounds) {
	return bounds.getHeight();
}

s32 VerticalLayout::fetchOrthogonalBoundsLength(const irr::core::recti& bounds) {
	return bounds.getWidth();
}

irr::core::recti VerticalLayout::createBoundsForMember(s32 a1, s32 a2) {
	s32 x1 = this->hPadding;
	s32 x2 = this->getRelativePosition().getWidth() - x1;
	return irr::core::recti(x1, a1, x2, a2);
}

}
}

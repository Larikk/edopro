#ifndef VERTICAL_LAYOUT_H
#define VERTICAL_LAYOUT_H

#include "IDirectionalLayout.h"

namespace irr {
namespace gui {

class VerticalLayout : public IDirectionalLayout {
public:
	VerticalLayout(IGUIEnvironment* environment, IGUIElement* parent = NULL, s32 id = -1);
	~VerticalLayout();

	s32 getParallelPadding();
	s32 getOrthogonalPadding();
	s32 fetchMembersFixedLength(LayoutMember* member);
	s32 fetchMembersMinLength(LayoutMember* member);
	s32 fetchMembersMaxLength(LayoutMember* member);
	float fetchMembersPreferredRelativeLength(LayoutMember* member);
	s32 fetchBoundsLength(const irr::core::recti& bounds);
	s32 fetchOrthogonalBoundsLength(const irr::core::recti& bounds);
	irr::core::recti createBoundsForMember(s32 a1, s32 a2);
};
}
}

#endif //VERTICAL_LAYOUT_H

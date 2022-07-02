#ifndef HORIZONTAL_LAYOUT_H
#define HORIZONTAL_LAYOUT_H

#include "IDirectionalLayout.h"

namespace irr {
namespace gui {

class HorizontalLayout : public IDirectionalLayout {
public:
	HorizontalLayout(IGUIEnvironment* environment, IGUIElement* parent = NULL, s32 id = -1);
	~HorizontalLayout();

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

#endif //HORIZONTAL_LAYOUT_H

#ifndef I_DIRECTIONAL_LAYOUT_H
#define I_DIRECTIONAL_LAYOUT_H

#include "ILayout.h"

namespace irr {
namespace gui {

enum JustifyContentMode {
	JustifyContentAtStart,
	JustifyContentAtEnd,
	JustifyContentAtCenter,
	JustifyContentApart,
};

struct LayoutMemberLength {
	LayoutMember* member;
	s32 l;
};

class IDirectionalLayout : public ILayout {
public:
	IDirectionalLayout(IGUIEnvironment* environment, IGUIElement* parent = NULL, s32 id = -1);
	~IDirectionalLayout();

    void setRelativePosition(const core::recti& r);

	void setJustifyContentMode(JustifyContentMode mode);
	void setPadding(s32 padding);
	void setHPadding(s32 padding);
	void setVpadding(s32 padding);
	void setSpacing(s32 spacing);

protected:
	JustifyContentMode justifyContentMode = JustifyContentAtStart;
	s32 hPadding = 10;
	s32 vPadding = 10;
	s32 spacing = 10;

	virtual s32 getParallelPadding() = 0;
	virtual s32 getOrthogonalPadding() = 0;
	virtual s32 fetchMembersFixedLength(LayoutMember* member) = 0;
	virtual s32 fetchMembersMinLength(LayoutMember* member) = 0;
	virtual s32 fetchMembersMaxLength(LayoutMember* member) = 0;
	virtual float fetchMembersPreferredRelativeLength(LayoutMember* member) = 0;
	virtual s32 fetchBoundsLength(const irr::core::recti& bounds) = 0;
	virtual s32 fetchOrthogonalBoundsLength(const irr::core::recti& bounds) = 0;
	virtual irr::core::recti createBoundsForMember(s32 a1, s32 a2) = 0;

private:
	s32 determineMemberLength(LayoutMember* member, s32 totalAvailableLength);
	std::vector<LayoutMemberLength> calculateMemberLengths();

	void layoutMembersSequentially(const s32 start, const s32 spacing, const std::vector<LayoutMemberLength> lengths);
	void layoutMembersAtStart(const std::vector<LayoutMemberLength> lengths);
	void layoutMembersAtEnd(const std::vector<LayoutMemberLength> lengths);
	void layoutMembersCentering(const std::vector<LayoutMemberLength> lengths);
	void layoutMembersApart(const std::vector<LayoutMemberLength> lengths);
};
}
}

#endif //I_DIRECTIONAL_LAYOUT_H

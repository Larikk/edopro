#include "IDirectionalLayout.h"

#include <stdexcept>

namespace irr {
namespace gui {


IDirectionalLayout::IDirectionalLayout(IGUIEnvironment* environment, IGUIElement* parent, s32 id) :
	ILayout(environment, parent, id) {};

IDirectionalLayout::~IDirectionalLayout() {};

s32 IDirectionalLayout::determineMemberLength(LayoutMember* member, s32 totalAvailableLength) {
	s32 fixedLength = this->fetchMembersFixedLength(member);
	if (fixedLength >= 0) {
		return fixedLength;
	}

	float preferredRelativeLength = this->fetchMembersPreferredRelativeLength(member);
	if (preferredRelativeLength < 0) {
		// An equal part of the leftover length will be assigned in a second pass
		return -1;
	}

	s32 length = (float) totalAvailableLength * preferredRelativeLength;

	s32 minLength = this->fetchMembersMinLength(member);
	if (minLength >= 0) {
		length = std::max(length, this->fetchMembersMinLength(member));
	}

	s32 maxLength = this->fetchMembersMaxLength(member);
	if (maxLength >= 0) {
		length = std::min(length, this->fetchMembersMaxLength(member));
	}

	return length;
}

std::vector<LayoutMemberLength> IDirectionalLayout::calculateMemberLengths() {
	irr::core::recti layoutBounds = this->getRelativePosition();
	std::vector<LayoutMember*> layoutMembers = this->layoutMembers;
	int n = layoutMembers.size();

	s32 totalAvailableLength =
		this->fetchBoundsLength(layoutBounds) // total length of the layout
		- 2 * this->getParallelPadding(); // subtract padding relevant for length calculation

	if (this->justifyContentMode != JustifyContentApart) {
		totalAvailableLength -= (n-1) * this->spacing; // subtract empty space between element
	}

	std::vector<LayoutMemberLength> lengths = {};

	// Members with a negative preferred length will be assigned an equal part of the leftover length later
	s32 numberOfLeftoverConsumer = 0;
	s32 leftoverLength = totalAvailableLength;

	for (LayoutMember* member : layoutMembers) {
		LayoutMemberLength length;
		length.member = member;
		length.l = this->determineMemberLength(member, totalAvailableLength);
		lengths.push_back(length);

		if (length.l < 0) {
			numberOfLeftoverConsumer++;
		} else {
			leftoverLength -= length.l;
		}
	}

	// Second pass to distribute any leftover length
	if (numberOfLeftoverConsumer > 0) {
		s32 equalShareOfLeftoverLength = leftoverLength / numberOfLeftoverConsumer;
		for (LayoutMemberLength& length : lengths) {
			length.l = equalShareOfLeftoverLength;
		}
	}

	return lengths;
}

void IDirectionalLayout::layoutMembersSequentially(const s32 start, const s32 spacing, const std::vector<LayoutMemberLength> lengths) {
	s32 cursor = start;

	for (LayoutMemberLength length : lengths) {
		LayoutMember* member = length.member;

		irr::core::recti bounds = this->createBoundsForMember(cursor, cursor+length.l);
		member->setRelativePosition(bounds);

		cursor = cursor + length.l + spacing;
	}
}

void IDirectionalLayout::layoutMembersAtStart(const std::vector<LayoutMemberLength> lengths) {
	s32 start = this->getParallelPadding();
	this->layoutMembersSequentially(start, this->spacing, lengths);
}

void IDirectionalLayout::layoutMembersAtEnd(const std::vector<LayoutMemberLength> lengths) {
	irr::core::recti layoutBounds = this->getRelativePosition();
	s32 layoutLength = this->fetchBoundsLength(layoutBounds);

	s32 totalMemberLength = 0; // does not include spacing between members
	for (LayoutMemberLength length : lengths) {
		totalMemberLength += length.l;
	}

	s32 totalSpacingLength = (lengths.size() - 1) * this->spacing;

	s32 start = layoutLength
		- this->getParallelPadding()
		- totalSpacingLength
		- totalMemberLength;

	this->layoutMembersSequentially(start, this->spacing, lengths);
}

void IDirectionalLayout::layoutMembersCentering(const std::vector<LayoutMemberLength> lengths) {
	irr::core::recti layoutBounds = this->getRelativePosition();
	s32 layoutLength = this->fetchBoundsLength(layoutBounds);

	s32 totalMemberLength = 0; // does not include spacing between members
	for (LayoutMemberLength length : lengths) {
		totalMemberLength += length.l;
	}

	s32 totalSpacingLength = (lengths.size() - 1) * this->spacing;

	s32 start = (layoutLength - this->getParallelPadding()) / 2.0
		- (totalSpacingLength / 2.0)
		- (totalMemberLength / 2.0);

	this->layoutMembersSequentially(start, this->spacing, lengths);
}

void IDirectionalLayout::layoutMembersApart(const std::vector<LayoutMemberLength> lengths) {
	s32 start = this->getParallelPadding();

	irr::core::recti layoutBounds = this->getRelativePosition();
	s32 layoutLength = this->fetchBoundsLength(layoutBounds);

	s32 totalMemberLength = 0; // does not include spacing between members
	for (LayoutMemberLength length : lengths) {
		totalMemberLength += length.l;
	}

	s32 totalSpacing = layoutLength - totalMemberLength - 2 * this->getParallelPadding();
	s32 spacing = totalSpacing / (lengths.size() - 1);

	this->layoutMembersSequentially(start, spacing, lengths);
}

void IDirectionalLayout::setRelativePosition(const core::recti& r) {
    ILayout::setRelativePosition(r);

	if (this->layoutMembers.size() == 0) {
		return;
	}

	std::vector<LayoutMemberLength> lengths = calculateMemberLengths();

	switch (this->justifyContentMode) {
	case JustifyContentAtStart:
		this->layoutMembersAtStart(lengths);
		break;
	case JustifyContentAtCenter:
		this->layoutMembersCentering(lengths);
		break;
	case JustifyContentAtEnd:
		this->layoutMembersAtEnd(lengths);
		break;
	case JustifyContentApart:
		this->layoutMembersApart(lengths);
		break;
	default:
		throw new std::runtime_error("Invalid or missing JustifyContentMode for a layout.");
	}
}

void IDirectionalLayout::setJustifyContentMode(JustifyContentMode mode) {
	this->justifyContentMode = mode;
}


}
}

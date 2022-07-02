#ifndef I_LAYOUT_H
#define I_LAYOUT_H

#include <vector>
#include "LayoutMember.h"
#include "../CGUICustomText/CGUICustomText.h"

namespace irr {
namespace gui {


class ILayout : public CGUICustomText {
public:
	ILayout(IGUIEnvironment* environment, IGUIElement* parent = NULL, s32 id = -1);
	~ILayout();

	// Adds a GUI element to the layout
	virtual void addLayoutMember(LayoutMember* member);

    // Must set the position of the Layout and update the positions of its content
    virtual void setRelativePosition(const core::recti& r);

	// Throws exception. Child elements need to be added via addLayoutMember()
	virtual void addChild(IGUIElement* child);

	// Throws exception. Child elements need to be added via addLayoutMember()
	virtual void addChildToEnd(IGUIElement* child);

protected:
	std::vector<LayoutMember*> layoutMembers;
	s32 vPadding;
	s32 hPadding;

};

}
}

#endif // I_LAYOUT_H

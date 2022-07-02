#ifndef LAYOUT_MEMBER_H
#define LAYOUT_MEMBER_H

#include "rect.h"
#include <IGUIElement.h>

namespace irr {
namespace gui {

class LayoutMember {
    public:
		LayoutMember(IGUIElement* element, bool isLayout);
        ~LayoutMember();
        void setRelativePosition(const irr::core::recti& bounds);

		IGUIElement* getGUIElement();
		s32 getFixedWidth();
		s32 getFixedHeigth();
		s32 getMinWidth();
		s32 getMinHeigth();
		s32 getMaxWidth();
		s32 getMaxHeigth();
		float getPreferredRelativeWidth();
		float getPreferredRelativeHeight();
		bool getScaling();

		LayoutMember* withFixedWidth(s32 w);
		LayoutMember* withFixedHeight(s32 h);
		LayoutMember* withMinWidth(s32 w);
		LayoutMember* withMinHeight(s32 h);
		LayoutMember* withMaxWidth(s32 w);
		LayoutMember* withMaxHeight(s32 h);
		LayoutMember* withPreferredRelativeWidth(float w);
		LayoutMember* withPreferredRelativeHeight(float h);
		LayoutMember* WithScaling();

	private:
        IGUIElement* element;
		bool isLayout = false;
		s32 fixedWidth = -1;
		s32 fixedHeight = -1;
		s32 minWidth = -1;
		s32 minHeight = -1;
		s32 maxWidth = -1;
		s32 maxHeigth = -1;
		float preferredRelativeWidth = -1;
		float preferredRelativeHeight = -1;
		bool isScaling = false;
};

LayoutMember* createLayoutMember(IGUIElement* element, bool isLayout=false);

}
}

#endif //LAYOUT_MEMBER_H

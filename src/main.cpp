#include <Geode/Geode.hpp>
#include <Geode/modify/EditorUI.hpp>

using namespace geode::prelude;

// betteredit style HolyUB, acaruso is fuming (sorry)
struct FakeSetGroupIDLayer final {
    char m_alloc[sizeof(SetGroupIDLayer)];
    SetGroupIDLayer* operator->() {
        return reinterpret_cast<SetGroupIDLayer*>(&m_alloc);
    }
};

class $modify(MyEditorUI, EditorUI) {

	struct Fields{
		CCMenuItemSpriteExtra* m_editExtrasBtn;
	};

	bool init(LevelEditorLayer* editorLayer) {

		if (!EditorUI::init(editorLayer)) {
			return false;
		}

		if(auto editorButtonsMenu = getChildByID("editor-buttons-menu")) {
			CCSprite* spr = CCSprite::create("edit_extras.png"_spr);
			m_fields->m_editExtrasBtn = CCMenuItemSpriteExtra::create(spr, this, menu_selector(MyEditorUI::onExtras));
			m_fields->m_editExtrasBtn->setContentSize({40, 40});
			m_fields->m_editExtrasBtn->setOpacity(175);
			m_fields->m_editExtrasBtn->setColor({166, 166, 166});
			m_fields->m_editExtrasBtn->m_animationEnabled = false;
			editorButtonsMenu->addChild(m_fields->m_editExtrasBtn);
			editorButtonsMenu->updateLayout();
		}

		return true;
	}

	void showUI(bool show){
		EditorUI::showUI(show);
		if (m_fields->m_editExtrasBtn) {
			m_fields->m_editExtrasBtn->setVisible(show);
		}
	}

    void updateButtons() {
		EditorUI::updateButtons();

		if (m_fields->m_editExtrasBtn) {
			if (m_selectedObject || m_selectedObjects->count() > 0) {
				m_fields->m_editExtrasBtn->setOpacity(255);
				m_fields->m_editExtrasBtn->setColor({255, 255, 255});
				m_fields->m_editExtrasBtn->m_animationEnabled = true;
			}
			else {
				m_fields->m_editExtrasBtn->setOpacity(175);
				m_fields->m_editExtrasBtn->setColor({166, 166, 166});
				m_fields->m_editExtrasBtn->m_animationEnabled = false;
			}
		}
	}


	void onExtras(CCObject* obj) {
		if (m_selectedObject || m_selectedObjects->count() > 0) {
			auto sgidl = FakeSetGroupIDLayer();
			sgidl->m_targetObject = m_selectedObject;
			sgidl->m_targetObjects = m_selectedObjects;
			sgidl->onExtra(obj);
		}
	}
};
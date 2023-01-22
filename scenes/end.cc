#include "end.h"
#include "../manager.h"



End::End(gf::Vector2i size,Manager& link)
: Scene(link.getRenderer().getSize())
, m_managerLink(link)
, m_spaceAction("Press_space")
, m_font("data/arial.ttf")
, m_menuButton("Menu", m_font, 20.0)
, m_restartButton("Restart", m_font, 20.0)
{
    setClearColor(gf::Color::Gray(0.3f));

    m_spaceAction.addKeycodeKeyControl(gf::Keycode::Space);
	addAction(m_spaceAction);

    //Restart button
    setButton(this->m_menuButton);
    setButton(this->m_restartButton);

}

void End::setButton(gf::TextButtonWidget &button){
    button.setDefaultTextColor(gf::Color::Black);
    button.setDefaultBackgroundColor(gf::Color::White);
    button.setSelectedTextColor(gf::Color::Black);
    button.setSelectedBackgroundColor(gf::Color::Gray(0.7f));
    button.setBackgroundOutlineThickness(2);
    button.setRadius(12.0);
    button.setAnchor(gf::Anchor::TopLeft);
    button.setAlignment(gf::Alignment::Center);
    this->m_widgets.addWidget(button);

}



void End::doHandleActions(gf::Window & window){
	if(m_spaceAction.isActive()){
		m_managerLink.replaceScene(m_managerLink.rulesScene);
	}
}



void End::doProcessEvent(gf::Event& event) {
    gf::MouseButtonEvent &mouseEvent = event.mouseButton;
    switch (event.type) {
        case gf::EventType::MouseButtonPressed:
            if(this->m_menuButton.contains(mouseEvent.coords)){
                    this->m_menuButton.setSelected();
            }else if(this->m_restartButton.contains(mouseEvent.coords)){
                    this->m_restartButton.setSelected();
            }
            break;
        case gf::EventType::MouseButtonReleased:
            this->m_menuButton.setState(gf::WidgetState::Default);
            this->m_restartButton.setState(gf::WidgetState::Default);

            if(this->m_menuButton.contains(mouseEvent.coords)){
                m_managerLink.replaceScene(m_managerLink.titleScene);
            }else if(this->m_restartButton.contains(mouseEvent.coords)){
                m_managerLink.replaceScene(m_managerLink.gameScene);
            }
            break;
        default:
            break;
    }
}

void End::doRender (gf::RenderTarget &target, const gf::RenderStates &states){

    target.setView(getHudView());
    gf::Coordinates coords(target);

    const float characterSize = coords.getRelativeSize(gf::Vector2f(0.05f, 0.05f)).x;
    const float paddingSize = coords.getRelativeSize({0.01f, 0.f}).x;
    const float paragraphWidth = coords.getRelativeSize(gf::Vector2f(0.3f, 0.2f) - 0.05f).x;

    m_restartButton.setCharacterSize(characterSize);
    m_restartButton.setAnchor(gf::Anchor::TopLeft);
    m_restartButton.setPosition(coords.getRelativePoint({0.2f, 0.6f}));
    m_restartButton.setParagraphWidth(paragraphWidth);
    m_restartButton.setPadding(paddingSize);

    m_menuButton.setCharacterSize(characterSize);
    m_menuButton.setAnchor(gf::Anchor::TopRight);
    m_menuButton.setPosition(coords.getRelativePoint({0.8f, 0.6f}));
    m_menuButton.setParagraphWidth(paragraphWidth);
    m_menuButton.setPadding(paddingSize);
    

    m_widgets.render(target);
}
#include "rules.h"
#include "../manager.h"



Rules::Rules(gf::Vector2i size,Manager& link) 
: Scene(link.getRenderer().getSize())
, m_managerLink(link)
, m_returnButton("Return", m_managerLink.resources.getFont("font/arial.ttf"), 20.0)
{
	setClearColor(gf::Color::Gray(0.1f));


    //Title
	this->m_title = gf::Text("Rules", m_managerLink.resources.getFont("font/arial.ttf")); 
    this->m_title.setColor(gf::Color::White);


    //Button
    this->m_returnButton.setDefaultTextColor(gf::Color::Black);
    this->m_returnButton.setDefaultBackgroundColor(gf::Color::White);
    this->m_returnButton.setSelectedTextColor(gf::Color::Black);
    this->m_returnButton.setSelectedBackgroundColor(gf::Color::Gray(0.7f));
    this->m_returnButton.setBackgroundOutlineThickness(2);
    this->m_returnButton.setRadius(12.0);
    this->m_returnButton.setAnchor(gf::Anchor::TopLeft);
    this->m_returnButton.setAlignment(gf::Alignment::Center);
    m_widgets.addWidget(this->m_returnButton);

    //Rules
    std::ifstream rulesFile ("data/TheLegendOfChrisMinnahl/game_rules.txt");
    std::string rules;

    if (rulesFile.is_open()) {
        while (rulesFile) {
        std::string line;
            std::getline (rulesFile, line);
            rules+=line+"\n";
        }
    }else {
        std::cout << "Couldn't open file\n";
    }

    this->m_rules.setString(rules);
    this->m_rules.setFont(m_managerLink.resources.getFont("font/arial.ttf"));
    this->m_rules.setColor(gf::Color::White);
    this->m_rules.setAlignment(gf::Alignment::Left);
}

void Rules::renderTitle(gf::RenderTarget &target){
    gf::Coordinates coords(target);
    this->m_title.setCharacterSize(coords.getRelativeSize(gf::Vector2f(0.07f, 0.07f)).x);
    this->m_title.setPosition(coords.getRelativePoint({ 0.5f, 0.1f }));
    this->m_title.setAnchor(gf::Anchor::TopCenter);

    target.draw(this->m_title);
}

void Rules::renderButton(gf::RenderTarget &target){
    gf::Coordinates coords(target);
    this->m_returnButton.setCharacterSize(coords.getRelativeSize(gf::Vector2f(0.03f, 0.03f)).x);
    this->m_returnButton.setPosition(coords.getRelativePoint({0.8f, 0.05f}));
    this->m_returnButton.setParagraphWidth(coords.getRelativeSize(gf::Vector2f(0.2f, 0.1f) - 0.05f).x);
    this->m_returnButton.setPadding(coords.getRelativeSize({0.01f, 0.f}).x);

    target.draw(this->m_returnButton);
}

void Rules::renderRules(gf::RenderTarget &target){
    gf::Coordinates coords(target);
    this->m_rules.setCharacterSize(coords.getRelativeSize(gf::Vector2f(0.03f, 0.03f)).x);
    this->m_rules.setPosition(coords.getRelativePoint({ 0.5f, 0.4f }));
    this->m_rules.setParagraphWidth(coords.getRelativeSize(gf::Vector2f(0.9f, 0.9f) - 0.05f).x);
    this->m_rules.setAnchor(gf::Anchor::TopCenter);

    target.draw(this->m_rules);
}

void Rules::doProcessEvent(gf::Event& event) {
    gf::MouseButtonEvent &mouseEvent = event.mouseButton;
    switch (event.type) {
        case gf::EventType::MouseButtonPressed:
            if(this->m_returnButton.contains(mouseEvent.coords)){
                    this->m_returnButton.setSelected();
            }
            break;
        case gf::EventType::MouseButtonReleased:
            this->m_returnButton.setState(gf::WidgetState::Default );

            if(this->m_returnButton.contains(mouseEvent.coords)){
                m_managerLink.replaceScene(m_managerLink.titleScene);
            }
            break;
        default:
            break;
    }
}

void Rules::doRender (gf::RenderTarget &target, const gf::RenderStates &states){
    target.setView(getHudView());
    renderTitle(target);
    renderButton(target);
    renderRules(target);
}

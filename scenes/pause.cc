#include "pause.h"
#include <iostream>

#include "../manager.h"

Pause::Pause(gf::Vector2i size,Manager& link) :
	Scene(link.getRenderer().getSize()), managerLink(link), font("data/arial.ttf"), buttonRestart("Restart", font), buttonResume("Resume", font), buttonQuit("Quit", font){
	setClearColor(gf::Color::Gray(0.1f));
	
	//Title
	this->titleMenu = gf::Text("Pause", font); 
    this->titleMenu.setColor(gf::Color::White);

	
    //Button
	setButton(this->buttonRestart);
    setButton(this->buttonResume);
    setButton(this->buttonQuit);
	
	
}

void Pause::setButton(gf::TextButtonWidget &button){
    button.setDefaultTextColor(gf::Color::Black);
    button.setDefaultBackgroundColor(gf::Color::White);
    button.setSelectedTextColor(gf::Color::Black);
    button.setSelectedBackgroundColor(gf::Color::Gray(0.7f));
    button.setBackgroundOutlineThickness(2);
    button.setRadius(12.0);
    button.setAnchor(gf::Anchor::TopLeft);
    button.setAlignment(gf::Alignment::Center);
    this->buttons.addWidget(button);

}

void Pause::renderTitle(gf::RenderTarget &target){
	gf::Coordinates coords(target);
	this->titleMenu.setCharacterSize(coords.getRelativeSize(gf::Vector2f(0.06f, 0.06f)).x);
	this->titleMenu.setPosition(coords.getRelativePoint({ 0.5f, 0.26f }));
	this->titleMenu.setAnchor(gf::Anchor::TopCenter);
	
	target.draw(this->titleMenu);

}

void Pause::renderButtons(gf::RenderTarget &target){
    gf::Coordinates coords(target);

    constexpr float characterSize = 0.03f;
    constexpr float spaceBetweenButton = 0.06f;
    const float paddingSize = coords.getRelativeSize({0.02f, 0.f}).x;
    
	this->buttonRestart.setCharacterSize(coords.getRelativeSize(gf::Vector2f(0.03f, 0.03f)).x);
    this->buttonRestart.setPosition(coords.getRelativePoint({0.5f, 0.4f}));
    this->buttonRestart.setAnchor(gf::Anchor::TopCenter);
    this->buttonRestart.setParagraphWidth(coords.getRelativeSize(gf::Vector2f(0.2f, 0.1f) - 0.05f).x);
    this->buttonRestart.setPadding(paddingSize);

    this->buttonResume.setCharacterSize(coords.getRelativeSize(gf::Vector2f(0.03f, 0.03f)).x);
    this->buttonResume.setPosition(coords.getRelativePoint({0.5f, 0.4f + characterSize + spaceBetweenButton}));
    this->buttonResume.setAnchor(gf::Anchor::TopCenter);
    this->buttonResume.setParagraphWidth(coords.getRelativeSize(gf::Vector2f(0.2f, 0.1f) - 0.05f).x);
    this->buttonResume.setPadding(paddingSize);

   this->buttonQuit.setCharacterSize(coords.getRelativeSize(gf::Vector2f(0.03f, 0.03f)).x);
   this->buttonQuit.setPosition(coords.getRelativePoint({0.5f, 0.4f + (characterSize + spaceBetweenButton) * 2}));
   this->buttonQuit.setAnchor(gf::Anchor::TopCenter);
   this->buttonQuit.setParagraphWidth(coords.getRelativeSize(gf::Vector2f(0.2f, 0.1f) - 0.05f).x);
   this->buttonQuit.setPadding(paddingSize);

	target.draw(this->buttonRestart);
    target.draw(this->buttonResume);
    target.draw(this->buttonQuit);
}

void Pause::doProcessEvent(gf::Event& event) {
    gf::MouseButtonEvent &mouseEvent = event.mouseButton;
    switch (event.type) {
        case gf::EventType::MouseButtonPressed:
            if(this->buttonRestart.contains(mouseEvent.coords)){
                this->buttonRestart.setSelected();
            }else if(this->buttonResume.contains(mouseEvent.coords)){
                this->buttonResume.setSelected();
            }else if(this->buttonQuit.contains(mouseEvent.coords)){
                this->buttonQuit.setSelected();
            }
            break;
        case gf::EventType::MouseButtonReleased:
            this->buttonRestart.setState(gf::WidgetState::Default );
            this->buttonResume.setState(gf::WidgetState::Default );
            this->buttonQuit.setState(gf::WidgetState::Default );

            if(this->buttonRestart.contains(mouseEvent.coords)){
                managerLink.gameScene.reset();
                managerLink.replaceScene(managerLink.gameScene);
            }else if(this->buttonResume.contains(mouseEvent.coords)){
               
                managerLink.popScene();
                managerLink.gameScene.resume();
            }else if(this->buttonQuit.contains(mouseEvent.coords)){
                managerLink.getWindow().close();
            }
            break;
        default:
            break;
    }
}

void Pause::doRender (gf::RenderTarget &target, const gf::RenderStates &states){
    target.setView(getHudView());
    renderTitle(target);
    renderButtons(target);
}
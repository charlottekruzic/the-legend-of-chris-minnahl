#include "title.h"
#include <iostream>
#include <gf/Log.h>

#include "../manager.h"

Title::Title(gf::Vector2i size,Manager& link) :
	Scene(size), managerLink(link), buttonStart("Start", font), buttonRules("Rules", font), buttonQuit("Quit", font){
	setClearColor(gf::Color::Azure);
	
	

	

	auto setupButton = [&] (gf::TextButtonWidget& button, auto callback) {
        button.setDefaultTextColor(gf::Color::Black);
        button.setDefaultBackgroundColor(gf::Color::Gray(0.7f));
        button.setSelectedTextColor(gf::Color::Black);
        button.setSelectedBackgroundColor(gf::Color::Green);
        button.setDisabledTextColor(gf::Color::Black);
        button.setDisabledBackgroundColor(gf::Color::Red);
        button.setAnchor(gf::Anchor::TopLeft);
        button.setAlignment(gf::Alignment::Center);
        button.setCallback(callback);
        buttons.addWidget(button);
    };

    setupButton(buttonStart, [&] () {
        gf::Log::debug("Start pressed!\n");
        managerLink.replaceScene(managerLink.gameScene);
    });
	setupButton(buttonRules, [&] () {
        gf::Log::debug("Rules pressed!\n");
        managerLink.replaceScene(managerLink.rulesScene);
    });
	setupButton(buttonQuit, [&] () {
        gf::Log::debug("Quit pressed!\n");
        managerLink.popAllScenes();
    });

	
	
	
}



void Title::doRender (gf::RenderTarget &target, const gf::RenderStates &states){
	gf::Coordinates coords(target);
	float backgroundHeight = coords.getRelativeSize(gf::vec(0.0f, 1.0f)).height;
	
	unsigned titleCharacterSize = coords.getRelativeCharacterSize(0.1f);
	
	gf::Text titleMenu("The Legend Of Chris Minnahl", font, titleCharacterSize);
	titleMenu.setCharacterSize(50);
	titleMenu.setPosition(coords.getRelativePoint({ 0.5f, 0.1f }));
	titleMenu.setAnchor(gf::Anchor::TopCenter);
	titleMenu.setColor(gf::Color::Cyan);
	
	target.draw(titleMenu);

	 constexpr float characterSize = 0.075f;
    constexpr float spaceBetweenButton = 0.045f;
    constexpr gf::Vector2f backgroundSize(0.5f, 0.3f);
	const float paragraphWidth = coords.getRelativeSize(backgroundSize - 0.05f).x;
    const float paddingSize = coords.getRelativeSize({0.01f, 0.f}).x;
    const unsigned resumeCharacterSize = coords.getRelativeCharacterSize(characterSize);

	buttonStart.setCharacterSize(resumeCharacterSize);
    buttonStart.setPosition(coords.getRelativePoint({0.275f, 0.425f}));
    buttonStart.setParagraphWidth(paragraphWidth);
    buttonStart.setPadding(paddingSize);

    buttonRules.setCharacterSize(resumeCharacterSize);
    buttonRules.setPosition(coords.getRelativePoint({0.275f, 0.425f + characterSize + spaceBetweenButton}));
    buttonRules.setParagraphWidth(paragraphWidth);
    buttonRules.setPadding(paddingSize);

    buttonQuit.setCharacterSize(resumeCharacterSize);
    buttonQuit.setPosition(coords.getRelativePoint({0.275f, 0.425f + (characterSize + spaceBetweenButton) * 2}));
    buttonQuit.setParagraphWidth(paragraphWidth);
    buttonQuit.setPadding(paddingSize);

	buttons.render(target);
}

void Title::doShow() {
    buttons.clear();

    buttonStart.setDefault();
    buttons.addWidget(buttonStart);

    buttonRules.setDefault();
    buttons.addWidget(buttonRules);

    buttonQuit.setDefault();
    buttons.addWidget(buttonQuit);

    buttons.selectNextWidget();
  }
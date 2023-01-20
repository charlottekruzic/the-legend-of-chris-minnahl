#include "rules.h"
#include "../manager.h"



Rules::Rules(gf::Vector2i size,Manager& link) : Scene(size),spaceAction("Press_space"),managerLink(link){
	setClearColor(gf::Color::Orange);
	
	spaceAction.addKeycodeKeyControl(gf::Keycode::Space);
	addAction(spaceAction);

	this->titleRules = gf::Text("The game's rules", font); 
    this->titleRules.setCharacterSize(50);
	gf::Coordinates coordinates_title(WINDOW_SIZE);
	gf::Vector2f center = coordinates_title.getCenter();
	this->titleRules.setPosition(coordinates_title.getAbsolutePoint(center/2, gf::Anchor::TopLeft));
    this->titleRules.setColor(gf::Color::White);

	
	this->returnButton.setAnchor(gf::Anchor::TopRight);
    this->returnButton.setPosition({WINDOW_SIZE[0]-30 ,30.0});
    this->returnButton.setBackgroundOutlineThickness(2);
    this->returnButton.setDefaultBackgroundColor(gf::Color::White);
    this->returnButton.setPadding(10.0);
    this->returnButton.setRadius(12.0);


    std::ifstream rulesFile ("local/game_rules.txt");
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

    this->gameRules.setString(rules);
    this->gameRules.setFont(font);
    this->gameRules.setParagraphWidth(WINDOW_SIZE[0]-WINDOW_SIZE[0]/8);
    this->gameRules.setAlignment(gf::Alignment::Left);
    this->gameRules.setCharacterSize(20);
    this->gameRules.setAnchor(gf::Anchor::Center);
    this->gameRules.setPosition({WINDOW_SIZE[0]/2,WINDOW_SIZE[1]/2});
    this->gameRules.setColor(gf::Color::White);


	//gf::Text text("test config", managerLink.resources.getFont("arial.ttf"));

}

void Rules::doHandleActions(gf::Window & window){
	if(spaceAction.isActive()){
		managerLink.replaceScene(managerLink.titleScene);
	}
}
void Rules::doUpdate (gf::Time time){

}

void Rules::doRender (gf::RenderTarget &target, const gf::RenderStates &states){
	target.draw(this->titleRules);
	target.draw(this->returnButton);
	target.draw(this->gameRules);
}

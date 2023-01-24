#include "map.h"
#include "../manager.h"


Map::Map(gf::Vector2i size,Manager& link)
: Scene(link.getRenderer().getSize())
, m_managerLink(link)
, m_mAction("Close map")
{

    setClearColor(gf::Color::Gray(0.3f));

    m_mAction.addKeycodeKeyControl(gf::Keycode::L);  //remettre M
    m_mAction.setInstantaneous();
	addAction(m_mAction);
}


void Map::doHandleActions(gf::Window & window){
	if(m_mAction.isActive()){
        m_managerLink.popScene();
        m_managerLink.replaceScene(m_managerLink.gameScene);
	}
}
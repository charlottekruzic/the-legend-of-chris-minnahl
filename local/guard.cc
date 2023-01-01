#include "guard.h"

Guard::Guard():velocity(0,0),shape(GUARD_SIZE){
    speed = 200;
    route_index = 0;
    position = {0,0};
    velocity.y = speed;
    rect = gf::RectI().fromPositionSize(position,GUARD_SIZE);  
    color = gf::Color::Red;
   	shape.setColor(color);
    shape.setAnchor(gf::Anchor::TopLeft);
    shape.setPosition(position);
}

void Guard::setRoute(std::vector<RouteAction> new_route){
	route = new_route;
	route_index = 0;
	
}


void Guard::nextAction(){
	route_index ++;
   	if(route_index > route.size()){
   		route_index = 0;
   	}
    RouteAction *currentAction = &route[route_index];

   	switch(currentAction->type){
   		case actionType::WAIT:
			currentAction->cumulated_time = 0;
   			break;
   	
   	   	case actionType::GO:
			currentAction->cumulated_time = 0;
   			break;
   		default:
   			break;
   	}
}

void Guard::update(float dt){
    RouteAction currentAction = route[route_index];

    switch(currentAction.type){
    	case actionType::WAIT:
    		break;
    	case actionType::GO:
    		break;
    	default:
    		break;
    }
    currentAction.cumulated_time += dt;
    if (currentAction.cumulated_time > currentAction.time){
		nextAction();
    }
    


	//unchanged
    position += velocity  * dt;
   	rect = rect.fromPositionSize(position,GUARD_SIZE);
    shape.setPosition(position);

}

void Guard::render(gf::RenderTarget& target){
    target.draw(shape);
};


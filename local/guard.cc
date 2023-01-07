#include "guard.h"
#include "wall.h"
#include <iostream>
#include <cmath>
bool is_between(float number, float lower,float upper){
	return ((unsigned)(number-lower) <= (upper-lower));
       
}


struct RouteAction* generateRouteAction(actionType type,float time,gf::Vector2i position){
	struct RouteAction* newRoute = new struct RouteAction;
	newRoute->type = type;
	newRoute->time = time;
	newRoute->grid_position = position;
	return newRoute;
}

Guard::Guard(gf::Vector2i grid_pos):velocity(0,0),shape(GUARD_SIZE),detectorShape(DETECTOR_SIZE){
    speed = 200;
    position = grid_pos * WALL_SIZE;
    last_position = position;
    velocity = {0,0};
    rect = gf::RectI().fromPositionSize(position,GUARD_SIZE);  
    color = gf::Color::Red;
   	shape.setColor(color);
    shape.setAnchor(gf::Anchor::TopLeft);
    shape.setPosition(position);
    detectorShape.setColor(gf::Color::Yellow);
    detectorShape.setAnchor(gf::Anchor::Center);
   	detectorShape.setPosition(position);    		

}


void Guard::setRoute(std::vector<RouteAction *> new_route){
	route = new_route;
	route_index = -1;
	nextAction();//initialize first action

	
}


void Guard::nextAction(){
	route_index ++;
   	if(route_index >= route.size()){
   		route_index = 0;
   	}


    currentAction = route[route_index];
   	currentAction->cumulated_time = 0;

    std::cout << "Route index : "<< route_index <<"\n";
	std::cout << "New action ! "<< (currentAction->type == actionType::GO ?  "GO" : "WAIT") <<"\n";
	std::cout << "time : " << currentAction->time << "\n";
	
   	switch(currentAction->type){
   		case actionType::WAIT:
   			shape.setColor(gf::Color::Azure);
   			break;
   	   	case actionType::GO:
   	   	   	shape.setColor(gf::Color::Red);
   	   	   	last_position = position;

   			break;
   		default:
   			break;
   	}

}


void Guard::update(float dt){
	velocity = {0,0};
	gf::Vector2f target;
	float time_proportion,deltaX,deltaY,upper,lower;
	bool h_move;
    switch(currentAction->type){
    	case actionType::WAIT:

    		break;
    	case actionType::GO:
    		time_proportion = currentAction->cumulated_time / currentAction->time;
    		deltaX = (currentAction->grid_position.x * WALL_SIZE.x) - last_position.x;
    		deltaY = (currentAction->grid_position.y * WALL_SIZE.y) - last_position.y;

			target = {
				round(last_position.x + deltaX * time_proportion ),
				round(last_position.y + deltaY * time_proportion ),

			};
			lower = std::min(last_position.x,currentAction->grid_position.x * WALL_SIZE.x);	
			upper = std::max(last_position.x,currentAction->grid_position.x * WALL_SIZE.x);	

    		if ( is_between(target.x,lower,upper)){
    		 	position.x =target.x;
			}else{
    			position.x =  (currentAction->grid_position.x * WALL_SIZE.x);
    		}
    		
    		position.y = last_position.y + deltaY * time_proportion;

			lower = std::min(last_position.y,currentAction->grid_position.y * WALL_SIZE.y);	
			upper = std::max(last_position.y,currentAction->grid_position.y * WALL_SIZE.y);	

    		if ( is_between(target.y,lower,upper)){
    		 	position.y =target.y;
			}else{
    			position.y =  (currentAction->grid_position.y * WALL_SIZE.y);
    		}
    		

			detectorShape.setPosition(position);

			std::cout << "X : " << deltaX << ", Y : " << deltaY << "\n";			
			
			if (deltaX > 0 ){
				//going right
				detectorShape.setScale({1.3,0.7});
				detectorShape.setAnchor(gf::Anchor::CenterLeft);
				detectorShape.move({GUARD_SIZE.x,0});
			}
			if (deltaX < 0){
				//going left
				//detectorShape.setScale({2,0.5});
				detectorShape.setAnchor(gf::Anchor::CenterRight);

			}
			if(deltaY > 0){
				//going down
				//detectorShape.setScale({0.5,2});
				detectorShape.setAnchor(gf::Anchor::TopCenter);
				detectorShape.move({0,GUARD_SIZE.y});

			}
			if(deltaY < 0){
				//going up
				//detectorShape.setScale({0.5,2});
				detectorShape.setAnchor(gf::Anchor::BottomCenter);

				
			}
    		

    		break;
    	default:
    		break;
    }



	currentAction->cumulated_time += dt;

	//unchanged
   	rect = rect.fromPositionSize(position,GUARD_SIZE);
    shape.setPosition(position);
    
    if (currentAction->cumulated_time >= currentAction->time){
		nextAction();
    }
}

void Guard::render(gf::RenderTarget& target){
    target.draw(shape);
    target.draw(detectorShape);
};


#include "item.h"

Item::Item(char display) :Subject{display} {}
 
SubscriptionType Item::subType(){
	return SubscriptionType::PlayerToItem;
} 

Item::~Item() {}


#include "ECommerce.h"
#include "Menu.h"

ECommerce::ECommerce(){
    this->order.CreateDataVec();
    this->order.SortDataVec();
    this->order.OrderViewSelect();

    handleMenuSelection(this->basket);
}

ECommerce::~ECommerce(){
    this->order.SaveDataVec();
}
#include "ECommerce.h"
#include "Menu.h"

ECommerce::ECommerce(){
    this->adminControlls.order.CreateDataVec();
    this->adminControlls.order.SortDataVec();
    this->adminControlls.order.OrderViewSelect();

    handleMenuSelection(this->basket);
}

ECommerce::~ECommerce(){
    this->adminControlls.order.SaveDataVec();
}
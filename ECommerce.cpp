#include "ECommerce.h"

ECommerce::ECommerce(){
    this->order.CreateDataVec();
    this->order.SortDataVec();
    this->order.OrderViewSelect();
}

ECommerce::~ECommerce(){
    this->order.SaveDataVec();
}
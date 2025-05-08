#pragma once
#include <string>
#include <vector>

#include "Display.h"

using namespace std;
class Order : public Display {
    public:
    
            struct orderInformation{
            int items_bought; 
            string date;
            string time;
            int date_time;
            int card_identifier;
            string card_expiry;
            string item;
            int quantity;
            float unit_cost;
            float item_payment;
            float total_payment;
        };

    private:


    

        string file_name = "orders.txt";
        vector<orderInformation> order_vec;

    public:
        //Order(); //don't need constructor, handled by other classes
        void CreateDataVec();
        void SortDataVec();
        void OrderViewSelect();
        void TransactionHistoryView();
        void FinancialHistoryView();
        void PrintVec(); //debug
        void SaveDataVec();
        vector<orderInformation> GetOrderVec();
        void AddToOrderVec(orderInformation order);
        //~Order();
};
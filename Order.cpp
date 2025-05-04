#include "Order.h"
#include "ECommerce.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>


using namespace std;


/*
Order::Order(){
    Order::CreateDataVec();
}

Order::~Order(){
    Order::SaveDataVec();
}
*/


void Order::CreateDataVec(){
    ifstream ordersFile(this->file_name);
    string fileLine;

    string temp_file_seg;
    char delimiter = ',';
    int line_iterator = 0;

    int countOfCommas = 0;
    int numberOfItemsBought = 1;
    orderInformation orderStruct;
    int num_of_orders = 0;



    while(getline (ordersFile, fileLine)){
        //take each line, delimit by ',', count occurrences of this character
        //use to determine how many items bought, hard coded number sadly but constant
        //put information (and convert types where appropriate) into struct
        //put struct into vector or list, test which is better

        //this is messy, and that makes me sad
        // TW: nested loops
        countOfCommas = 0;
        for(int i=0; i<fileLine.size(); i++){
            if(fileLine[i] == ','){
                countOfCommas++;
            }
        }

        //default count is 6 for a 1 item purchase, increasing items by 1 increases commas by 3
        //use this to find item count
        numberOfItemsBought = ((countOfCommas - 3) / 3);


        //now need to take this and create that many instances of orderStruct and append to the vector
        for (int i=0;i<numberOfItemsBought;i++){
            //split the current line by ',', append necessary information
            //first items starts at pos 4,5,6 and then 3 extra so on and so forth with 1 extra at the end
            stringstream ss(fileLine);
            

            orderStruct.items_bought = numberOfItemsBought;
            orderStruct.date = fileLine.substr(0,10); //pos, length
            orderStruct.time = fileLine.substr(11,8);

            //turn the date and time strings into single integer for sorting and manipulation
            //this is long but simple
            orderStruct.date_time = (stoi(orderStruct.time.substr(6,2))) + ((stoi(orderStruct.time.substr(3,2)))*100) + ((stoi(orderStruct.time.substr(0,2)))*10000) + ((stoi(orderStruct.date.substr(8,2)))*1000000) + ((stoi(orderStruct.date.substr(5,2)))*100000000) + ((stoi(orderStruct.date.substr(0,4)))*1000000000000);
            orderStruct.card_identifier = stoi(fileLine.substr(35,4));
            orderStruct.card_expiry = fileLine.substr(40,5);



            //this loop will only deal with changing item purchases and therefore is done last
            line_iterator = 0;
            while (getline(ss, temp_file_seg, delimiter)){
                //stuff like the following puts tears in my eyes
                if(line_iterator == (i*3+3)){
                    orderStruct.item = temp_file_seg;
                } else if(line_iterator == (i*3+4)){
                    orderStruct.quantity = stoi(temp_file_seg);
                } else if(line_iterator == (i*3+5)){
                    orderStruct.unit_cost = stof(temp_file_seg);
                } else if(line_iterator == (numberOfItemsBought*3+3)){
                    orderStruct.total_payment = stof(temp_file_seg);
                }
                line_iterator++;
            }

            //finish off the struct
            orderStruct.item_payment = orderStruct.quantity * orderStruct.unit_cost;

            this->order_vec.push_back(orderStruct);

        }

        num_of_orders++;
    }

    ordersFile.close();
}



void Order::PrintVec(){
    this->ClearScreen();

    for(int i=0; i < this->order_vec.size(); i++){
        cout << this->order_vec[i].item << "," << this->order_vec[i].items_bought << endl;
    }
}

//important to note that these should actually be sorted already, but this is a 'just in case' function
void Order::SortDataVec(){
    //need a way to choose what to sort it by
    //I love sorting methods
    //I will use bubble sort because it is simple and has a fun name :D
    int size_of_vec = this->order_vec.size();
    
    for(int i=0; i<size_of_vec-1; i++){
        for(int ii=0; ii<size_of_vec - i - 1; ii++){

            if(this->order_vec[ii].date_time > this->order_vec[ii + 1].date_time){
                swap(this->order_vec[ii].date_time, this->order_vec[ii+1].date_time);            
            }
        }
    }
}


void Order::OrderViewSelect(){
    bool stay_on_screen = true;
    while (stay_on_screen){
        Display::RefreshScreen();
        int choice = 0;
        cout << "Would you like to view the Transaction History (1), Financial History (2), or go back (3)?" << endl;
        cin >> choice;
        while(choice != 1 and choice !=2 and choice !=3){
            cout << "Invalid option, please try again..." << endl;
            cin >> choice;
        }

        switch (choice){
            case 1:
                Order::TransactionHistoryView();
                break;
            case 2:
                Order::FinancialHistoryView();
                break;
            case 3:
                stay_on_screen = false;
                break;
        }
    }
}

void Order::TransactionHistoryView(){
    //called in case orders have been added and state messed up
    Order::SortDataVec();

    Display::RefreshScreen();
    //display DATE TIME ITEM QUANTITY COST
    for (int i=0; i<this->order_vec.size();i++){
        cout << this->order_vec[i].date << " at " << this->order_vec[i].time << ": " << this->order_vec[i].quantity << "x " << this->order_vec[i].item << " PROFIT: £" << this->order_vec[i].item_payment << endl;
    }
    //hold program here
    Display::PauseProgram();
}

vector<Order::orderInformation> Order::GetOrderVec(){
    return this->order_vec;
}

void Order::FinancialHistoryView(){
    //need to sum daily intake
    //if only this wasn't OOP, this could have been a function
    struct date_money_pair {
        string date;
        float money;
        int scaled_point = 0;
    };

    vector<date_money_pair> fhistory_vec;
    date_money_pair curr_datemoney;
    string prev_date = this->order_vec[0].date;



    date_money_pair max_money;
    max_money.money = 0;

    Order::SortDataVec();

    for (int i=0; i<this->order_vec.size();i++){
        //if date is the same, sum money
        if(this->order_vec[i].date == prev_date){
            curr_datemoney.money += this->order_vec[i].item_payment;
        } else {
            curr_datemoney.date = prev_date; //update the date
            fhistory_vec.push_back(curr_datemoney); //append to vector
            prev_date = this->order_vec[i].date; //update the date

            if(max_money.money < curr_datemoney.money){
                max_money = curr_datemoney; //update maximum (for graph purposes)
            }

            curr_datemoney.money = this->order_vec[i].item_payment; //reset and add the first bit of money
        }
    }
    //add last struct
    curr_datemoney.date = prev_date;
    fhistory_vec.push_back(curr_datemoney);

    //make max_money represent 100 on a scale, find the points of everything else;
    for(int i=0; i<fhistory_vec.size();i++){
        fhistory_vec[i].scaled_point = (int)((100/max_money.money)*fhistory_vec[i].money);
        if (fhistory_vec[i].scaled_point < 1){
            fhistory_vec[i].scaled_point = 1;
        } else if(fhistory_vec[i].scaled_point > 100){
            fhistory_vec[i].scaled_point = 100;
        }
    }

    
    Display::RefreshScreen();
    for (int i=0; i<fhistory_vec.size();i++){
        cout << fhistory_vec[i].date << ": ";
        for (int ii=0; ii<fhistory_vec[i].scaled_point; ii++){
            cout << "*";
        }
        cout << endl;
    }
    
    for (int i=0; i<112; i++){
        cout << "-";
    }
    cout << "£" <<  max_money.money << endl;

    Display::PauseProgram();
}



void Order::SaveDataVec(){
    ofstream orderFile("orders.txt");

    for(int i=0; i<this->order_vec.size(); i++){
        orderFile << this->order_vec[i].date << " " << this->order_vec[i].time << ",XXXX-XXXX-XXXX-" << this->order_vec[i].card_identifier << "," << this->order_vec[i].card_expiry << ",";
        //condensed format
        int item_bundle_count = this->order_vec[i].items_bought;
        for (int ii=0; ii<item_bundle_count;ii++){
            orderFile << this->order_vec[i].item << "," << this->order_vec[i].quantity << "," << this->order_vec[i].unit_cost << ",";
            i++; //horrors
        }

        i--; //more horrors
        orderFile << this->order_vec[i].total_payment << "\n";
    }

    orderFile.close();
}
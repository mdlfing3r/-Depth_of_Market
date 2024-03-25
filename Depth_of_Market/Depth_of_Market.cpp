


#include <iostream>
#include <memory>
#include <map>
#include <vector>
#include <set>


//Придумать или выбрать способ сортровки заказов в стакане на основании цены, чтобы для вывода топ 10 лучших, выводить this->Orders(0..9)
//Может для офера стоит использовать структуру ?
enum status_t {
    success = 0,
    invalidUUID,
    invalidCost,
    invalidQuantity,
    prev_is_equal
};

enum operation_t {
    sell = 0,
    buy
};

constexpr auto err = -1;
constexpr auto TopAmountNum = 10;


class DOF {

    DOF() = default;

    ~DOF() = default;

public:
    typedef int16_t offerID_t;
    typedef float quantity_t;
    typedef float cost_t; //Стоимость минимально оперируемой единицы
    typedef std::array<int, 10> topOrders_t;
    typedef std::pair<quantity_t, cost_t> offer_t;


    struct transaction_t {
        float cost; //Стоимость минимально оперируемой единицы
        offerID_t UUID;
        float quantity;
    };

    offerID_t createOrder(offer_t offerParams, operation_t operationType);
    status_t editOrder(transaction_t transaction, operation_t operationType);
    std::multiset<transaction_t> ShowTopOrders(operation_t operationType);
    void deleteOrder(offerID_t order, operation_t operationType);
    void updateTopOrder(operation_t operationType);


private:
    offerID_t createSellOrder(offer_t offerParams);
    offerID_t createBuyOrder(offer_t offerParams);
    static offerID_t sellUUID;
    static offerID_t buyUUID;
    std::multiset<transaction_t> sellOrders;
    std::multiset<transaction_t> buyOrders;

};






DOF::offerID_t DOF::createSellOrder(offer_t offerParams)
{
    sellUUID++;
    sellOrders.insert({ offerParams.first, sellUUID, offerParams.second});
    return offerID_t();
}

DOF::offerID_t DOF::createBuyOrder(offer_t offerParams)
{
    buyUUID++;
    buyOrders.insert({ offerParams.first, sellUUID, offerParams.second});
    return offerID_t();
}

DOF::offerID_t DOF::createOrder(offer_t offerParams, operation_t operationType)
{
    if(!offerParams.first || !offerParams.second) return 0;
 

    switch (operationType) {
        case operation_t::sell:
            return createSellOrder(offerParams);
            break;
        case operation_t::buy:
            return createBuyOrder(offerParams);
            break;
        default:
            return err;
            break;
    }

}

status_t DOF::editOrder(transaction_t transaction, operation_t operationType)
{
    status_t retval;
    std::multiset<transaction_t>::iterator itr_Order;


    if (!transaction.cost) return status_t::invalidCost;
    if (!transaction.quantity) return status_t::invalidQuantity;

    switch (operationType) {
            case operation_t::sell: {
                itr_Order = sellOrders.find(transaction);
                if (itr_Order == sellOrders.end()) return status_t::invalidUUID;
                if (itr_Order->cost == transaction.cost || itr_Order->quantity == transaction.quantity)  return status_t::prev_is_equal;
                sellOrders.erase(itr_Order);
                sellOrders.emplace(transaction);
            }
            break;

            case operation_t::buy: {
                itr_Order = buyOrders.find(transaction);
                if (itr_Order == buyOrders.end()) return status_t::invalidUUID;
                if (itr_Order->cost == transaction.cost || itr_Order->quantity == transaction.quantity)  return status_t::prev_is_equal;
                buyOrders.erase(itr_Order);
                buyOrders.emplace(transaction);
            }
            break;
    }

    return status_t::success;
}

void DOF::updateTopOrder(operation_t operationType) {


    switch (operationType) {
        case operation_t::sell:
            for (auto it = sellOrders.begin(); it != sellOrders.end(); it++) sellOrders.insert(*it);
            break;

        case operation_t::buy:
            for (auto it = buyOrders.begin(); it != buyOrders.end(); it++) buyOrders.insert(*it);
            break;

    }


}

std::multiset<DOF::transaction_t> DOF::ShowTopOrders(operation_t operationType)
{

    std::multiset<transaction_t> retContainer;

    switch (operationType) {
        case operation_t::sell:
            for (auto it = sellOrders.begin(); it != sellOrders.end(); it++){
                retContainer.insert(*it);
                if (retContainer.size() == TopAmountNum) break;
            }
            break;

        case operation_t::buy:
            for (auto it = buyOrders.begin(); it != buyOrders.end(); it++) {
                retContainer.insert(*it);
                if (retContainer.size() == TopAmountNum) break;
            }
            break;  
    }

}

void DOF::deleteOrder(DOF::offerID_t offerID, operation_t operationType)
{
    std::multiset<transaction_t>::iterator itr_Order;


    switch (operationType) {
        case operation_t::sell:
            for (auto it = sellOrders.begin(); it != sellOrders.end(); it++) 
                if (it->UUID == offerID) {
                    sellOrders.erase(it);
                    break;
                }              
            break;

        case operation_t::buy:
            for (auto it = buyOrders.begin(); it != buyOrders.end(); it++)
                if (it->UUID == offerID) {
                    buyOrders.erase(it);
                    break;
                }
            break;

        default:
            break;
    }
}




